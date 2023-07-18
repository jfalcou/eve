//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/algo/algo/for_each_iteration.hpp>
#include <eve/module/algo/algo/views/convert.hpp>
#include <eve/module/core.hpp>

namespace eve::algo
{

//================================================================================================
//! @addtogroup algos
//! return type from set_intersection
//================================================================================================
template<typename I1, typename I2, typename O> struct set_intersection_result
{
  I1 in1;
  I2 in2;
  O  out;
};

template<typename I1, typename I2, typename O>
set_intersection_result(I1, I2, O) -> set_intersection_result<I1, I2, O>;

namespace detail
{
  // FIX: 1629 - support common type and such
  template<typename Traits, typename... Rs>
  EVE_FORCEINLINE auto temporary_preprocess_ranges_hack(Traits tr, Rs&&...rs)
  {
    constexpr auto to_consider = kumi::cat(get_types_to_consider_for<Traits, Rs> {}...);
    auto           traits2     = default_to(tr, traits {consider_types_key = to_consider});
    return kumi::tuple {preprocess_range(traits2, rs)...};
  }

  template<typename TraitsSupport> struct set_intersection_r1_small_ : TraitsSupport
  {
    template<typename R1, typename R2, typename RO, typename Less, typename Equal> struct delegate
    {
      using I1 = unaligned_iterator_t<R1>;

      R1  & r1;
      R2  & r2;
      RO  & ro;
      Less  less;
      Equal equal;

      I1                       f1 {eve::unalign(r1.begin())};
      unaligned_iterator_t<RO> o {eve::unalign(ro.begin())};
      wide_value_type_t<I1>    v1 {eve::read(f1)}; // broadcast

      // only needed for result
      unaligned_iterator_t<R2> f2_res {eve::unalign(r2.begin()) + (r2.end() - r2.begin())};

      delegate(R1& r1_, R2& r2_, RO& ro_, Less less_, Equal equal_)
          : r1 {r1_}
          , r2 {r2_}
          , ro {ro_}
          , less {less_}
          , equal {equal_}
      {}

      template<typename I2, typename Ignore> EVE_FORCEINLINE bool step(I2 i, Ignore ignore, auto)
      {
        auto v2 = eve::load[ignore](i);
        while( true )
        {
          auto test = less(v2, v1);
          if( eve::all[ignore](test) ) { return false; }
          auto eq_test = equal(v1, v2);
          if( eve::any[ignore](eq_test) )
          {
            eve::write(eve::convert(eve::read(f1), eve::as<value_type_t<RO>> {}), o);
            if( ++o == ro.end() )
            {
              ++f1;
              f2_res = eve::unalign(i) + *eve::first_true[ignore](eq_test) + 1;
              return true;
            }
          }
          if( ++f1 == r1.end() ) return true;
          v1 = eve::read(f1);
        }
      }

      EVE_FORCEINLINE bool unrolled_step(auto arr)
      {
        return unroll_by_calling_single_step {}(arr, *this);
      }
    };

    template<relaxed_range R1, relaxed_range R2, relaxed_range RO, typename Less, typename Equal>
    EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2, RO&& ro, Less less, Equal equal) const
        -> set_intersection_result<unaligned_iterator_t<R1>,
                                   unaligned_iterator_t<R2>,
                                   unaligned_iterator_t<RO>>
    {
      if( ro.begin() == ro.end() ) { return {r1.begin(), r2.begin(), ro.begin()}; }
      if( r1.begin() == r1.end() || r2.begin() == r2.end() )
      {
        return {eve::unalign(r1.begin()) + (r1.end() - r1.begin()),
                eve::unalign(r2.begin()) + (r2.end() - r2.begin()),
                ro.begin()};
      }

      // No need to consider the type of RO because we only use it as a scalar.
      auto [processed_r1, processed_r2] =
          temporary_preprocess_ranges_hack(TraitsSupport::get_traits(), r1, r2);

      auto iteration =
          for_each_iteration(processed_r2.traits(), processed_r2.begin(), processed_r2.end());

      delegate<decltype(processed_r1), decltype(processed_r2), RO, Less, Equal> d {
          processed_r1, processed_r2, ro, less, equal};
      iteration(d);

      // reached the end
      if( d.f2_res == processed_r2.end() ) d.f1 = processed_r1.end();
      if( d.f1 == processed_r1.end() ) d.f2_res = processed_r2.end();

      return {unalign(r1.begin()) + (d.f1 - processed_r1.begin()),
              unalign(r2.begin()) + (d.f2_res - processed_r2.begin()),
              d.o};
    }
  };

  inline constexpr auto set_intersection_r1_small =
      function_with_traits<set_intersection_r1_small_>[default_simple_algo_traits];

  template<typename TraitsSupport> struct set_intersection_r2_small_ : TraitsSupport
  {
    template<typename R1, typename R2, typename RO, typename Less, typename Equal> struct delegate
    {
      using I2 = unaligned_iterator_t<R2>;

      R1  & r1;
      R2  & r2;
      RO  & ro;
      Less  less;
      Equal equal;

      I2                       f2 {eve::unalign(r2.begin())};
      unaligned_iterator_t<RO> o {eve::unalign(ro.begin())};
      wide_value_type_t<I2>    v2 {eve::read(f2)}; // broadcast

      // only needed for result
      unaligned_iterator_t<R1> f1_res {eve::unalign(r1.begin()) + (r1.end() - r1.begin())};

      delegate(R1& r1_, R2& r2_, RO& ro_, Less less_, Equal equal_)
          : r1 {r1_}
          , r2 {r2_}
          , ro {ro_}
          , less {less_}
          , equal {equal_}
      {}

      template<typename I1, typename Ignore> EVE_FORCEINLINE bool step(I1 i, Ignore ignore, auto)
      {
        auto v1 = eve::load[ignore](i);
        while( true )
        {
          auto test = less(v1, v2);
          if( eve::all[ignore](test) ) { return false; }
          if( auto found = eve::first_true[ignore](equal(v1, v2)) )
          {
            auto f1 = eve::unalign(i) + *found;
            eve::write(eve::convert(eve::read(f1), eve::as<value_type_t<RO>> {}), o);
            if( ++o == ro.end() )
            {
              f1_res = f1 + 1;
              ++f2;
              return true;
            }
          }
          if( ++f2 == r2.end() ) return true;
          v2 = eve::read(f2);
        }
      }

      EVE_FORCEINLINE bool unrolled_step(auto arr)
      {
        return unroll_by_calling_single_step {}(arr, *this);
      }
    };

    template<relaxed_range R1, relaxed_range R2, relaxed_range RO, typename Less, typename Equal>
    EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2, RO&& ro, Less less, Equal equal) const
        -> set_intersection_result<unaligned_iterator_t<R1>,
                                   unaligned_iterator_t<R2>,
                                   unaligned_iterator_t<RO>>
    {
      if( ro.begin() == ro.end() ) { return {r1.begin(), r2.begin(), ro.begin()}; }
      if( r1.begin() == r1.end() || r2.begin() == r2.end() )
      {
        return {eve::unalign(r1.begin()) + (r1.end() - r1.begin()),
                eve::unalign(r2.begin()) + (r2.end() - r2.begin()),
                ro.begin()};
      }

      // No need to consider the type of RO because we only use it as a scalar.
      auto [processed_r1, processed_r2] =
          temporary_preprocess_ranges_hack(TraitsSupport::get_traits(), r1, r2);

      auto iteration =
          for_each_iteration(processed_r1.traits(), processed_r1.begin(), processed_r1.end());

      delegate<decltype(processed_r1), decltype(processed_r2), RO, Less, Equal> d {
          processed_r1, processed_r2, ro, less, equal};
      iteration(d);

      // reached the end
      if( d.f1_res == processed_r1.end() ) d.f2 = processed_r2.end();
      if( d.f2 == processed_r2.end() ) d.f1_res = processed_r1.end();

      return {unalign(r1.begin()) + (d.f1_res - processed_r1.begin()),
              unalign(r2.begin()) + (d.f2 - processed_r2.begin()),
              d.o};
    }
  };

  inline constexpr auto set_intersection_r2_small =
      function_with_traits<set_intersection_r2_small_>[default_simple_algo_traits];

  template<typename TraitsSupport> struct set_intersection_basic_ : TraitsSupport
  {
    constexpr auto modified_traits() const
    {
      // force no aligning, drop unrolling
      return default_to(eve::algo::traits {no_aligning, unroll<1>}, TraitsSupport::get_traits());
    }

    template<relaxed_range R1, relaxed_range R2, relaxed_range RO, typename Less, typename Equal>
    EVE_FORCEINLINE auto main_part(R1& r1, R2& r2, RO& ro, Less less, Equal equal) const
        -> set_intersection_result<unaligned_iterator_t<R1>,
                                   unaligned_iterator_t<R2>,
                                   unaligned_iterator_t<RO>>
    {
      // force no aligning, drop unrolling
      auto [pr1, pr2, pro] = temporary_preprocess_ranges_hack(
          modified_traits(), r1, r2, views::convert(ro, eve::as<value_type_t<R1>> {}));

      auto f1 = eve::unalign(pr1.begin());
      auto f2 = eve::unalign(pr2.begin());
      auto o  = eve::unalign(pro.begin());

      constexpr std::ptrdiff_t card = iterator_cardinal_v<decltype(f1)>;

      while( (pr1.end() - f1) >= card && (pr2.end() - f2) >= card && (pro.end() - o) >= card )
      {
        auto v1 = eve::load(f1);
        auto v2 = eve::load(f2);

        auto matches = eve::has_equal_in(v1, v2, equal);
        o            = eve::unsafe(eve::compress_store)(v1, matches, o);

        // maybe benefictial to move up but we will hope for a compiler
        //
        // Why not broadcast?
        // On x86 at least load + broadcast can be performed on a load
        // unit and not touch port 5. Given how port 5 heavy the `has_equal_in`, this
        // seems beneficial.
        wide_value_type_t<decltype(f1)> v1_back {eve::read(f1 + (card - 1))};
        wide_value_type_t<decltype(f2)> v2_back {eve::read(f2 + (card - 1))};

        f1 += eve::first_true(less(v2_back, v1)).value_or(card);
        f2 += eve::first_true(less(v1_back, v2)).value_or(card);
      }

      return {eve::unalign(r1.begin()) + (f1 - pr1.begin()),
              eve::unalign(r2.begin()) + (f2 - pr2.begin()),
              eve::unalign(ro.begin()) + (o - pro.begin())};
    }

    template<relaxed_range R1, relaxed_range R2, relaxed_range RO, typename Less, typename Equal>
    EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2, RO&& ro, Less less, Equal equal) const
        -> set_intersection_result<unaligned_iterator_t<R1>,
                                   unaligned_iterator_t<R2>,
                                   unaligned_iterator_t<RO>>
    {
      auto [f1, f2, o] = main_part(r1, r2, ro, less, equal);

      auto r1_ = algo::as_range(f1, r1.end());
      auto r2_ = algo::as_range(f2, r2.end());
      auto ro_ = algo::as_range(o, ro.end());

      if( r1.end() - f1 <= r2.end() - f2 )
      {
        return set_intersection_r1_small[modified_traits()](r1_, r2_, ro_, less, equal);
      }
      else { return set_intersection_r2_small[modified_traits()](r1_, r2_, ro_, less, equal); }
    }
  };

  inline constexpr auto set_intersection_basic = function_with_traits<set_intersection_basic_>;
}

template<typename TraitsSupport> struct set_intersection_ : TraitsSupport
{
  using traits_type                    = typename TraitsSupport::traits_type;
  static constexpr auto expect_smaller = get_expected_smaller_r<traits_type>();

  static_assert(expect_smaller.value_or(0) <= 1, "only two input ranges in the algorithm");

  /*
   * No zipped range becuase R1, R2 don't have to be the same length
   */
  template<relaxed_range R1, relaxed_range R2, relaxed_range RO, typename Less, typename Equal>
  EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2, RO&& ro, Less less, Equal equal) const
      -> set_intersection_result<unaligned_iterator_t<R1>,
                                 unaligned_iterator_t<R2>,
                                 unaligned_iterator_t<RO>>
  {
    if constexpr( expect_smaller == 0 )
    {
      return detail::set_intersection_r1_small[TraitsSupport::get_traits()](
          EVE_FWD(r1), EVE_FWD(r2), EVE_FWD(ro), less, equal);
    }
    else if constexpr( expect_smaller == 1 )
    {
      return detail::set_intersection_r2_small[TraitsSupport::get_traits()](
          EVE_FWD(r1), EVE_FWD(r2), EVE_FWD(ro), less, equal);
    }
    else
    {
      return detail::set_intersection_basic[TraitsSupport::get_traits()](
          EVE_FWD(r1), EVE_FWD(r2), EVE_FWD(ro), less, equal);
    }
  }

  template<relaxed_range R1, relaxed_range R2, relaxed_range RO>
  EVE_FORCEINLINE auto operator()(R1&& r1, R2&& r2, RO&& ro) const
      -> set_intersection_result<unaligned_iterator_t<R1>,
                                 unaligned_iterator_t<R2>,
                                 unaligned_iterator_t<RO>>
  {
    using T = common_type_t<value_type_t<R1>, eve::value_type_t<R2>>;

    // No need to convert to O, that can be converted on a write without any issues
    auto [f1, f2, o] = operator()(views::convert(EVE_FWD(r1), eve::as<T> {}),
                                  views::convert(EVE_FWD(r2), eve::as<T> {}),
                                  EVE_FWD(ro),
                                  eve::is_less,
                                  eve::is_equal);
    // this convert will unpack iterators if necessary
    return {views::convert(f1, eve::as<value_type_t<R1>> {}),
            views::convert(f2, eve::as<value_type_t<R2>> {}),
            o};
  }
};

//================================================================================================
//! @addtogroup algos
//! @{
//!  @var set_intersection
//!
//!  @brief SIMD variation on std::set_intersection that HAS A SLIGHTLY DIFFERENT SEMANTICS.
//!
//!  The main idea for the algorithm comes from
//!    "Faster-Than-Native Alternatives for x86 VP2INTERSECT Instructions"
//!     by Guillermo Diez-Canas.
//!     Link: https://arxiv.org/abs/2112.06342
//!
//!
//!  Differences:
//!    * duplicate handling, `eve::algo::set_intersection` does not
//!      guarantee how many copies of a duplicated element will be in the output.
//!      Example: [a, a] intersect with [a, a, a] might produce [a], [a, a] and [a, a, a].
//!    * we require both "Less" and "Equal" predicates, unlike `std` getting equal from less
//!      will be expensive.
//!    * eve requires an output range instead of an output iterator.
//!      eve will do checks that there is enough output space and if there isn't, it will stop.
//!      If the algorithm stopped because of insufficient output space, the return value will
//!      contain  where it stopped - (in1, in2) will point past the last written duplicate.
//!      TODO(#1630): provide support for output overallocation.
//!
//!  Other:
//!    * Less and Equal have to be semantically compatible
//!    * Eve always writes from the first range in case of equivalent elements.
//!      If `eve::is_less/is_greater` and `eve::is_equal` are passed in, elements are considered to
//!      be equal and eve can write from either range.
//!
//!  Tuning:
//!    * Has `expect_smaller_range<0>`, `expect_smaller_range<1>` variations.
//!      These use combined simd/scalar approach. Since the problem is very data dependent,
//!      you want to measure for your usecase.
//!    * Version `expect_smaller_range<0>` can be slightly faster, `eve` can't always use that
//!      due to a stability requirement but you might want to swap your inputs.
//!    * The provided solution is minimal, eve won't search for beginning of intersection in
//!      any way. eve also won't do any dispatch based on size.
//!      If this is something that can be beneficial for your case - consider it.
//!    * Basic version does not support aligning/unrolling. `expect_smaller_range` do.
//!
//!  **Header**
//!
//!  @code
//!  #include <eve/module/algo.hpp>
//!  @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve::algo
//!   {
//!     template<relaxed_range R1, relaxed_range R2, relaxed_range RO, typename Less, typename
//!     Equal> auto set_intersection(R1&& r1, R2&& r2, RO&& ro, Less less, Equal equal)  // (1)
//!       -> set_intersection_result<unaligned_iterator_t<R1>,
//!                                  unaligned_iterator_t<R2>,
//!                                  unaligned_iterator_t<RO>>
//!
//!     template<relaxed_range R1, relaxed_range R2, relaxed_range RO>
//!     auto set_intersection(R1&& r1, R2&& r2, RO&& ro)                          // (2)
//!       -> set_intersection_result<unaligned_iterator_t<R1>,
//!                                  unaligned_iterator_t<R2>,
//!                                  unaligned_iterator_t<RO>>
//!   }
//!   @endcode
//!
//!   (2) calls (1) with `eve::is_less`, `eve::is_equal` and converting to common type.
//!
//!   **Parameters (1)**
//!    * r1, r2 - relaxed ranges to intersect
//!    * ro - output relaxed range
//!    * less - simd strict weak ordering for elements from r1 and r2
//!    * equal - simd predicate for equivalence, compatible with less.
//!
//!   **Return value**
//!
//!   set_intersection{ .in1, .in2, .out }.
//!   * if ro had enough space for all common elements - .in1 == r1.end(), .in2 == r2.end(),
//!     .out is an iterator in ro past the last written elements (same as std::set_intersection)
//!   * if we ran out of space in ro before finishing the algorithm, .in1 and .in2 will point
//!     to positions past the last common element. .out == ro.end()
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/set_intersection.cpp}
//! @}
//================================================================================================
inline constexpr auto set_intersection = function_with_traits<set_intersection_>;

}
