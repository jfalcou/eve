//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/algo/algo/for_each_selected.hpp>
#include <eve/module/algo/algo/views/convert.hpp>
#include <eve/module/algo/algo/views/zip.hpp>
#include <eve/module/core.hpp>

#include <optional>

namespace eve::algo
{

template<typename TraitsSupport> struct search_ : TraitsSupport
{
  template<typename I1,   // haystack_iter
           typename I2,   // needle_f
           typename Equal // equal
           >
  struct needle_checker
  {
    std::ptrdiff_t needle_len;
    Equal          equal;

    wide_value_type_t<I2> first_wide;
    eve::keep_first       first_wide_ignore;

    std::ptrdiff_t  long_tail_offset;
    unaligned_t<I2> long_tail_start;
    std::ptrdiff_t  long_tail_n;

    template<typename S2>
    needle_checker(I2 f, S2 l, Equal _equal)
        : equal(_equal)
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
      auto test_first = equal(eve::load(haystack_i), first_wide);

      if( !eve::all[first_wide_ignore](test_first) ) return false;

      haystack_i += long_tail_offset;
      auto needle_i = long_tail_start;
      for( std::ptrdiff_t count = long_tail_n; count; --count )
      {
        auto test = equal(eve::load(haystack_i), eve::load(needle_i));
        if( !eve::all(test) ) return false;

        haystack_i += iterator_cardinal_v<I1>;
        needle_i += iterator_cardinal_v<I2>; // I1, I2 are interchangeable,
                                             // cardinals are the same
      }

      return true;
    }

    // tail handling for small needles, just looping through a register
    bool small_check(wide_value_type_t<I1> haystack) const
    {
      auto test = equal(haystack, first_wide);
      return eve::all[first_wide_ignore](test);
    }
  };

  template<typename I1, typename I2, typename Equal, typename Checker>
  EVE_FORCEINLINE auto main_part(auto            traits,
                                 I1              haystack_f,
                                 unaligned_t<I1> haystack_main_part_l,
                                 I2              needle_f,
                                 std::ptrdiff_t  needle_len,
                                 Equal           equal,
                                 Checker         check) const
  {
    eve::wide_value_type_t<I2> needle_front(eve::read(needle_f));
    eve::wide_value_type_t<I2> needle_back(eve::read(eve::unalign(needle_f) + (needle_len - 1)));

    unaligned_t<I1> hastack_back_f = eve::unalign(haystack_f) + (needle_len - 1);

    std::optional<unaligned_t<I1>> res;
    for_each_selected[drop_key(divisible_by_cardinal, traits)](
        views::zip(as_range(haystack_f, haystack_main_part_l), hastack_back_f),
        [&](auto haystack_front_back)
        {
          auto [haystack_front, haystack_back] = haystack_front_back;
          return equal(haystack_front, needle_front) && equal(haystack_back, needle_back);
        },
        [&](auto haystack_front_back_it)
        {
          auto [haystack_it, _] = haystack_front_back_it;

          if( check.main_check(haystack_it) )
          {
            res = haystack_it;
            return true;
          }
          return false;
        });
    return res;
  }

  template<typename UnalignedI1>
  EVE_FORCEINLINE std::optional<UnalignedI1> small_tail(UnalignedI1    small_tail_start,
                                                        auto           haystack_l,
                                                        std::ptrdiff_t needle_len,
                                                        auto           checker) const
  {
    // no small tail
    if( needle_len > eve::iterator_cardinal_v<UnalignedI1> ) return {};

    std::ptrdiff_t iterations = (haystack_l - small_tail_start) - needle_len + 1;

    auto haystack = eve::load[eve::keep_first(haystack_l - small_tail_start)](small_tail_start);

    for( std::ptrdiff_t i = 0; i != iterations; ++i )
    {
      if( checker.small_check(haystack) ) return small_tail_start + i;

      // TODO: use shuffle_v2 here.
      //
      // slide_left shifts in 0s.
      // If we were to use shuffle_v2 here, we'd could say `we_`
      // instead of 0s - which would be better.
      //
      // Unfortunately shuffle_v2 can't slide left yet
      haystack = eve::slide_left(haystack, eve::index<1>);
    }

    return {};
  }

  template<relaxed_range R1, relaxed_range R2, typename Equal>
  EVE_FORCEINLINE auto
  operator()(R1&& haystack, R2&& needle, Equal equal) const -> unaligned_iterator_t<R1>
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

    needle_checker<I1, I2, Equal> needle_checker(
        processed_needle.begin(), processed_needle.end(), equal);

    auto haystack_main_part_l = eve::unalign(haystack_f);

    if( haystack_len > iterator_cardinal_v<I1> )
    {
      haystack_main_part_l += haystack_len - std::max(needle_len, iterator_cardinal_v<I1>) + 1;

      if( auto res = main_part(processed_haystack.traits(),
                               haystack_f,
                               haystack_main_part_l,
                               processed_needle.begin(),
                               needle_len,
                               equal,
                               needle_checker) )
      {
        return eve::unalign(haystack.begin()) + (*res - haystack_f);
      }
    }

    if( auto res = small_tail(haystack_main_part_l, haystack_l, needle_len, needle_checker) )
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
inline constexpr auto search = function_with_traits<search_>;

}
