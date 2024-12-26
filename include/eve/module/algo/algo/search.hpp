//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/algo/algo/for_each_iteration_with_expensive_optional_part.hpp>
#include <eve/module/algo/algo/views/convert.hpp>
#include <eve/module/algo/algo/views/zip.hpp>
#include <eve/module/core.hpp>

#include <optional>

namespace eve::algo
{

namespace detail
{

  /*
   * This is a version of eve::algo::for_each_selected.
   * The problem with just using eve::algo::for_each_selected for search,
   * is that, when used with zip, the tail handling gets expensive.
   *
   * We want to trade off the tail handling for maybe more false positives.
   */
  struct for_each_possibly_matching_for_search_
  {
    template<
      typename HaystackI,
      typename NeedleWide,
      typename Equal,
      typename Verify> struct delegate
    {
      NeedleWide needle_front;
      NeedleWide needle_back;
      Equal      equal_fn;
      Verify&    verify;

      bool was_stopped = false;
      unaligned_t<HaystackI> pos = {};
      decltype(equal_fn(wide_value_type_t<HaystackI>{}, NeedleWide{})) precheck = {};

      template<typename I> EVE_FORCEINLINE auto make_verify_adapter(I haystack_it)
      {
        struct res_t
        {
          Verify&        verify;
          unaligned_t<I> base;

          EVE_FORCEINLINE bool operator()(std::ptrdiff_t i) { return verify(base + i); }
        };

        return res_t {verify, unalign(haystack_it)};
      }

      EVE_FORCEINLINE bool tail(auto zip_it, eve::relative_conditional_expr auto ignore)
      {
        pos = get<0>(zip_it);

        // not loading from `zip_it` here, becasue it's much more expensive for tails.
        auto         haystack_front = eve::load[ignore](pos);
        precheck     = equal_fn(haystack_front, needle_front);

        if (!eve::any[ignore](precheck)) {
          return false;
        }

        precheck = precheck && ignore.mask(as(precheck));

        return true;
      }

      EVE_FORCEINLINE bool main_part(auto zip_it)
      {
        auto [haystack_front, haystack_back] = eve::load(zip_it);

        pos = get<0>(zip_it);
        precheck = equal_fn(haystack_front, needle_front) && equal_fn(haystack_back, needle_back);
        return eve::any(precheck);
      }

      template<eve::relative_conditional_expr C>
      EVE_FORCEINLINE bool step(auto zip_it, C ignore)
      {
        if constexpr( C::is_complete && C::is_inverted ) { return main_part(zip_it); }
        else { return tail(zip_it, ignore); }
      }

      EVE_FORCEINLINE bool expensive_part()
      {
        was_stopped = eve::iterate_selected(precheck, make_verify_adapter(pos));
        return was_stopped;
      }
    };

    template<typename HaystackI,
             typename HaystackS,
             typename NeedleWide,
             typename Equal,
             typename Verify>
    EVE_FORCEINLINE bool operator()(auto           traits,
                                    HaystackI      haystack_f,
                                    HaystackS      haystack_l,
                                    NeedleWide     needle_front,
                                    NeedleWide     needle_back,
                                    std::ptrdiff_t needle_len,
                                    Equal          equal_fn,
                                    Verify&        verify) const
    {
      auto haystack_front_back_range =
          views::zip(as_range(haystack_f, haystack_l), unalign(haystack_f) + (needle_len - 1));

      auto iteration = algo::for_each_iteration_with_expensive_optional_part(
          traits, haystack_front_back_range.begin(), haystack_front_back_range.end());
      delegate<HaystackI, NeedleWide, Equal, Verify> d {
        needle_front, needle_back, equal_fn, verify, {}, {},
        };
      iteration(d);
      return d.was_stopped;
    }
  } inline constexpr for_each_possibly_matching_for_search;

}

template<typename TraitsSupport> struct search_ : TraitsSupport
{
  template<typename I1,   // haystack_iter
           typename I2,   // needle_f
           typename Equal // equal
           >
  struct needle_checker
  {
    Equal equal_fn;

    wide_value_type_t<I2> first_wide;
    eve::keep_first       first_wide_ignore;

    std::ptrdiff_t  long_tail_offset;
    unaligned_t<I2> long_tail_start;
    std::ptrdiff_t  long_tail_n;

    template<typename S2>
    needle_checker(I2 f, S2 l, Equal _equal)
        : equal_fn(_equal)
        , first_wide_ignore(iterator_cardinal_v<I2>)
    {
      std::ptrdiff_t needle_len = l - f;

      // This code probably only makes sense after looking at the main check
      // function
      if( needle_len < iterator_cardinal_v<I2> )
      {
        first_wide_ignore = eve::keep_first(needle_len);
        first_wide        = eve::load[first_wide_ignore](f);
        long_tail_start   = eve::unalign(f); // is unused, doesn't matter.
        long_tail_offset  = 0;
        long_tail_n       = 0;
      }
      else
      {
        first_wide        = eve::load(f);
        first_wide_ignore = eve::keep_first(iterator_cardinal_v<I2>);

        // the unsigned cast removes some negative number checks.
        auto remainder   = ((std::size_t)needle_len) % iterator_cardinal_v<I2>;
        long_tail_offset = (remainder != 0) ? remainder : iterator_cardinal_v<I2>;

        long_tail_start = eve::unalign(f) + long_tail_offset;
        long_tail_n     = (std::size_t)(needle_len - long_tail_offset) / iterator_cardinal_v<I2>;
      }
    }

    // for checking when there is enough space in the haystack to load
    // a register.
    bool main_check(unaligned_t<I1> haystack_i) const
    {
      auto test_first = equal_fn(eve::load(haystack_i), first_wide);

      if( !eve::all[first_wide_ignore](test_first) ) return false;

      haystack_i += long_tail_offset;
      auto needle_i = long_tail_start;
      for( std::ptrdiff_t count = long_tail_n; count; --count )
      {
        auto test = equal_fn(eve::load(haystack_i), eve::load(needle_i));
        if( !eve::all(test) ) return false;

        haystack_i += iterator_cardinal_v<I1>;
        needle_i += iterator_cardinal_v<I2>; // I1, I2 are interchangeable,
                                             // cardinals are the same
      }

      return true;
    }

    bool small_check(wide_value_type_t<I1> haystack) const
    {
      auto test = equal_fn(haystack, first_wide);
      return eve::all[first_wide_ignore](test);
    }
  };

  template<typename I1, typename I2, typename Equal, typename Checker>
  EVE_FORCEINLINE auto main_part(auto            traits,
                                 I1              haystack_f,
                                 unaligned_t<I1> haystack_main_part_l,
                                 I2              needle_f,
                                 std::ptrdiff_t  needle_len,
                                 Equal           equal_fn,
                                 Checker         check) const
  {
    eve::wide_value_type_t<I2> needle_front(eve::read(needle_f));
    eve::wide_value_type_t<I2> needle_back(eve::read(eve::unalign(needle_f) + (needle_len - 1)));

    struct
    {
      std::optional<unaligned_t<I1>> res;
      Checker                        check;

      EVE_FORCEINLINE bool operator()(unaligned_t<I1> haystack_it)
      {
        if( check.main_check(haystack_it) )
        {
          res = haystack_it;
          return true;
        }
        return false;
      }
    } verify {{}, check};

    detail::for_each_possibly_matching_for_search(drop_key(divisible_by_cardinal, traits),
                                                  haystack_f,
                                                  haystack_main_part_l,
                                                  needle_front,
                                                  needle_back,
                                                  needle_len,
                                                  equal_fn,
                                                  verify);

    return verify.res;
  }

  template<typename UnalignedI1, typename I2, typename Checker>
  EVE_FORCEINLINE std::optional<UnalignedI1> small_tail(UnalignedI1    small_tail_start,
                                                        auto           haystack_l,
                                                        I2             needle_f,
                                                        auto           equal_fn,
                                                        std::ptrdiff_t needle_len,
                                                        Checker        checker) const
  {
    // no small tail
    if( needle_len > eve::iterator_cardinal_v<UnalignedI1> ) return {};

    eve::wide_value_type_t<UnalignedI1> haystack =
        eve::load[eve::keep_first(haystack_l - small_tail_start)](small_tail_start);
    eve::wide_value_type_t<I2> needle_front(eve::read(needle_f));

    struct verify_t
    {
      std::optional<UnalignedI1> res;
      UnalignedI1                small_tail_start;

      // store small haystack in the stack buffer.
      stack_buffer<wide<value_type_t<UnalignedI1>, fixed<2 * iterator_cardinal_v<UnalignedI1>>>>
          buf;

      Checker checker;

      EVE_FORCEINLINE
      verify_t(UnalignedI1                    _small_tail_start,
               wide_value_type_t<UnalignedI1> haystack,
               Checker                        _checker)
          : small_tail_start(_small_tail_start)
          , checker(_checker)
      {
        eve::store(haystack, buf.ptr());
      }

      EVE_FORCEINLINE bool operator()(std::ptrdiff_t i)
      {
        // We can't slide a register by a runtime value.
        // So we store the register on the stack buffer and load instead.
        auto to_load = eve::unalign(buf.ptr()) + i;
        if( checker.small_check(load(to_load, as<wide_value_type_t<UnalignedI1>> {})) )
        {
          res = small_tail_start + i;
          return true;
        }
        return false;
      }
    } verify {small_tail_start, haystack, checker};

    std::ptrdiff_t possible_starts = (haystack_l - small_tail_start) - needle_len + 1;

    iterate_selected[eve::keep_first(possible_starts)](equal_fn(haystack, needle_front), verify);

    return verify.res;
  }

  template<relaxed_range R1, relaxed_range R2, typename Equal>
  EVE_FORCEINLINE auto
  operator()(R1&& haystack, R2&& needle, Equal equal_fn) const -> unaligned_iterator_t<R1>
  {
    std::ptrdiff_t needle_len   = (needle.end() - needle.begin());
    std::ptrdiff_t haystack_len = (haystack.end() - haystack.begin());

    if( needle_len == 0 ) return unalign(haystack.begin());
    if( haystack_len < needle_len ) return unalign(haystack.begin()) + haystack_len;

    auto [processed_haystack, processed_needle] =
        temporary_preprocess_ranges_hack(TraitsSupport::get_traits(), haystack, needle);

    auto haystack_f = processed_haystack.begin();
    auto haystack_l = processed_haystack.end();

    using I1 = decltype(processed_haystack.begin());
    using I2 = decltype(processed_needle.begin());

    needle_checker<I1, I2, Equal> nc(
        processed_needle.begin(), processed_needle.end(), equal_fn);

    auto haystack_main_part_l = eve::unalign(haystack_f);

    if( haystack_len > iterator_cardinal_v<I1> )
    {
      haystack_main_part_l += haystack_len - std::max(needle_len, iterator_cardinal_v<I1>) + 1;

      if( auto res = main_part(processed_haystack.traits(),
                               haystack_f,
                               haystack_main_part_l,
                               processed_needle.begin(),
                               needle_len,
                               equal_fn,
                               nc) )
      {
        return eve::unalign(haystack.begin()) + (*res - haystack_f);
      }
    }

    if( auto res = small_tail(haystack_main_part_l,
                              haystack_l,
                              processed_needle.begin(),
                              equal_fn,
                              needle_len,
                              nc) )
    {
      return eve::unalign(haystack.begin()) + (*res - haystack_f);
    }

    return eve::unalign(haystack.begin()) + haystack_len;
  }

  template<relaxed_range R1, relaxed_range R2>
  EVE_FORCEINLINE auto operator()(R1&& haystack, R2&& needle) const -> unaligned_iterator_t<R1>
  {
    // we should implement `common_type` as a trait for algorithms
    // and not just zip
    using T = common_type_t<value_type_t<R1>, eve::value_type_t<R2>>;

    auto converted_res = operator()(views::convert(EVE_FWD(haystack), eve::as<T> {}),
                                    views::convert(EVE_FWD(needle), eve::as<T> {}),
                                    eve::is_equal);
    return views::convert(converted_res, eve::as<value_type_t<R1>> {});
  }
};

//=================================================================================================
//! @addtogroup algos
//! @{
//!  @var search
//!
//!  @brief SIMD version of std::search (subsequence in a sequence).
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/algo.hpp>
//!   @endcode
//!
//!   Some ideas taken from previous work:
//!    Wojciech Mula: http://0x80.pl/articles/simd-strfind.html
//!    Ash Vardanian:
//!      https://github.com/ashvardanian/StringZilla/blob/07e0a2a4ad8330c91a20fccb66022715b386e1b4/include/stringzilla/stringzilla.h#L3784
//!    strstr from glibc:
//!      https://codebrowser.dev/glibc/glibc/sysdeps/x86_64/multiarch/strstr-sse2-unaligned.S.html
//!
//!   @note: to look for one element use `eve::algo::find`. It is also slightly faster,
//!   so if one element case is common - you might consider an `if` on the `needle` len.
//!
//!   Tuning:
//!    * Aligning search for initial test. Passing `no_aligning` will remove this aligning.
//!    * Unrolling search for initial test. Unlikely to be beneficial, but it's there to try.
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve::algo
//!   {
//!       template<relaxed_range R1, relaxed_range R2, typename Equal>
//!       auto search(R1&& haystack, R2&& needle, Equal equal)  // (1)
//!         -> unaligned_iterator_t<R1>
//!
//!       template<relaxed_range R1, relaxed_range R2>
//!       auto search(R1&& haystack, R2&& needle)  // (2)
//!         -> unaligned_iterator_t<R1>
//!   }
//!   @endcode
//!
//!   (2) calls (1) with `eve::is_equal`. In order to mimic the behaviour of std::search,
//!   it will also cast the types, so that you can search unrelated types.
//!
//!   Version (1) won't do implicit types conversions for you, you can either handle them in
//!   the predicate or use `views::convert`.
//!
//!   **Parameters (1)**
//!
//!    * haystack - where we search the subsequence.
//!    * needle - the subsequence we are searching for.
//!    * equal - the predicate of the elements.
//!
//!   **Return value**
//!
//!   unaligned iterator pointing to where in haystack the sequence is.
//!   If the needle is empty == haystack.begin() is returned.
//!   If the needle isn't found == haystack.end().
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/search.cpp}
//================================================================================================
inline constexpr auto search = function_with_traits<search_>[eve::algo::unroll<4>];

}
