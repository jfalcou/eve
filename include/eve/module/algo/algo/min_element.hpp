//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/algo/algo/common_forceinline_lambdas.hpp>
#include <eve/module/algo/algo/find.hpp>
#include <eve/module/algo/algo/for_each_iteration_fixed_overflow.hpp>
#include <eve/module/algo/algo/min_value.hpp>

namespace eve::algo::detail
{

template<typename TraitsSupport> struct min_element_1_pass_ : TraitsSupport
{
  using traits_type = typename TraitsSupport::traits_type;

  template<typename I, typename Less> struct delegate
  {
    using index_t  = get_index_type_t<traits_type, I>;
    using wide_v   = eve::wide_value_type_t<I>;
    using wide_i   = eve::wide<index_t, eve::iterator_cardinal_t<I>>;
    using v_i      = kumi::tuple<value_type_t<I>, index_t>;
    using wide_v_i = eve::wide<v_i, eve::iterator_cardinal_t<I>>;

    // For now just have one loop_index.
    // In preliminary experiments compiler unrolled it OK, can be improved later.
    std::array<wide_v_i, get_unrolling<traits_type>()> best;
    wide_i                                             loop_index;

    I    base;
    I    prev_best;
    Less less;

    struct
    {
      Less less;

      EVE_FORCEINLINE wide_v_i operator()(wide_v_i x, wide_v_i y) const
      {
        wide_v_i r;
        get<0>(r) = eve::min(less)(get<0>(x), get<0>(y));
        get<1>(r) = eve::if_else(less(get<0>(y), get<0>(x)), get<1>(y), get<1>(x));
        return r;
      }

    } combine {less};

    void reset()
    {
      best.fill(wide_v_i {v_i {eve::read(prev_best), 0}});
      loop_index = [](int i, int) { return i; };
    }

    delegate(I b, I i, Less l) : base(b), prev_best(i), less(l) { reset(); }

    EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto idx)
    {
      wide_v   cur_values = eve::load[ignore.else_(get<0>(best[idx()]))](it);
      wide_v_i cur {cur_values, loop_index};

      best[idx()] = combine(best[idx()], cur);

      loop_index += loop_index.size();
      return false;
    }

    EVE_FORCEINLINE bool unrolled_step(auto arr)
    {
      return unroll_by_calling_single_step{}(arr, *this);
    }

    struct is_not_best_lambda
    {
      Less & less;
      wide_v best_one;

      EVE_FORCEINLINE wide_i operator()(wide_v_i x) const
      {
        auto is_not_best = less(best_one, get<0>(x));
        return eve::if_else(is_not_best, std::numeric_limits<index_t>::max(), get<1>(x));
      }
    };

    EVE_FORCEINLINE void update_res()
    {
      auto   values          = array_map(best, [](auto x) { return get<0>(x); });
      wide_v lane_best_value = array_reduce(values, eve::min(less));
      wide_v wide_prev_best(eve::read(prev_best));

      if( !eve::any(less(lane_best_value, wide_prev_best)) ) return;

      wide_v best_one = eve::splat(eve::reduce)(lane_best_value, eve::min(less));

      auto best_indexes = array_map(best, is_not_best_lambda {less, best_one});

      prev_best = base + eve::reduce(array_reduce(best_indexes, eve::min), eve::min);
    }

    EVE_FORCEINLINE void overflow(auto it)
    {
      update_res();
      base = it;
      reset();
    }
  };

  template<relaxed_range Rng, typename Less>
  EVE_FORCEINLINE auto operator()(Rng&& rng, Less less) const -> unaligned_iterator_t<Rng>
  {
    auto raw_processed = eve::algo::preprocess_range(TraitsSupport::get_traits(), rng);
    if( raw_processed.begin() == raw_processed.end() ) return rng.begin();

    using index_t  = get_index_type_t<traits_type, Rng>;
    auto processed = preprocess_range(
        default_to(TraitsSupport::get_traits(), algo::traits {consider_types<index_t>}), rng);

    // No code is executed here, won't do a FORCEINLINE
    auto iteration = [&]
    {
      if constexpr( sizeof(ptrdiff_t) <= sizeof(index_t) )
      {
        return for_each_iteration(processed.traits(), processed.begin(), processed.end());
      }
      else
      {
        eve::algo::traits overflow_traits {
            overflow<(std::ptrdiff_t)std::numeric_limits<index_t>::max() + 1>};
        return for_each_iteration_fixed_overflow(
            default_to(processed.traits(), overflow_traits), processed.begin(), processed.end());
      }
    }();

    using I = unaligned_t<decltype(processed.begin())>;
    delegate<I, Less> d {iteration.base, processed.begin(), less};
    iteration(d);
    d.update_res();

    return unalign(rng.begin()) + (d.prev_best - processed.begin());
  }
};

inline constexpr auto min_element_1_pass = function_with_traits<min_element_1_pass_>;

template<typename TraitsSupport> struct min_element_2_pass_ : TraitsSupport
{
  template<relaxed_range Rng, typename Less>
  EVE_FORCEINLINE auto operator()(Rng&& rng, Less less) const -> unaligned_iterator_t<Rng>
  {
    if( rng.begin() == rng.end() ) return unalign(rng.begin());

    auto v = *min_value[TraitsSupport::get_traits()](EVE_FWD(rng), less);
    // We use user provided less to compare here (less(min, min) -> false
    // but less(min, anything_else) - true). Maybe we should use bit wise equality instead,
    // would also work if everything is well behaived.
    return eve::algo::find_if_not[TraitsSupport::get_traits()](EVE_FWD(rng), bind_first {less, v});
  }
};

inline constexpr auto min_element_2_pass =
    function_with_traits<min_element_2_pass_>[default_simple_algo_traits];

} // namespace eve::algo

namespace eve::algo
{
template<typename TraitsSupport> struct min_element_ : TraitsSupport
{
  template<relaxed_range Rng, typename Less>
  EVE_FORCEINLINE auto operator()(Rng&& rng, Less less) const -> unaligned_iterator_t<Rng>
  {
    auto processed = preprocess_range(TraitsSupport::get_traits(), rng);
    if constexpr( decltype(processed.traits())::contains(single_pass) )
    {
      return detail::min_element_1_pass[TraitsSupport::get_traits()](rng, less);
    }
    else { return detail::min_element_2_pass[TraitsSupport::get_traits()](rng, less); }
  }

  template<relaxed_range Rng>
  EVE_FORCEINLINE auto operator()(Rng&& rng) const -> unaligned_iterator_t<Rng>
  {
    return operator()(EVE_FWD(rng), eve::is_less);
  }
};

//================================================================================================
//! @addtogroup algos
//! @{
//!   @var min_element
//!
//!   @brief SIMD version of `std::min_element`
//!
//!   @note if you just need a value and not position, use `eve::algo::min_value`.
//!
//!   Can be one of two algorithms: one pass and two pass (default).
//!
//!   Two pass finds a value and then does a linear search for the value.
//!   This proves to be faster on smaller simpler arrays.
//!   By default unrolls by 4 and aligned all memory accesses.
//!
//!   The one pass version keeps track of index and is better suited for complicated predicates.
//!   You can opt in by using `single_pass` or `expensive_callable` traits.
//!   The `single_pass` opt-in will be aligning all data accesses
//~   (expensive_callable always disables this).
//!
//!   @note for equivalent elements we return the first amoung equal.
//!   @note we assume that `eve::is_less` defined for your type is total order.
//!        (this comes up when switching min with max)
//!
//!   **Alternative Header**
//!
//!   @code
//!   #include <eve/algo.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!   @code
//!   namespace eve::algo
//!   {
//!      template<relaxed_range Rng, typename Less>
//!      auto min_element(Rng&& rng, Less less) -> unaligned_iterator_t<Rng>;   // 1
//!
//!      template<relaxed_range Rng>
//!      auto min_element(Rng&& rng) -> unaligned_iterator_t<Rng>;            // 2
//!   }
//!   @endcode
//!
//!   1. Returns the position of a minimum value, according to less.
//!      If the range is empty - returns past the end.
//!
//!   2. Same as 1 but the `less` is `eve::is_less`
//!
//!   **Parameters**
//!
//!    * `rng`:  Relaxed input range to process
//!    * `less`: SIMD strict weak ordering.
//!
//!   **Return value**
//!
//!   iterator to min element (end if the range is empty).
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/min.cpp}
//!
//!   @see `min_value`
//!   @see `max_element`
//!
//! @}
//================================================================================================
inline constexpr auto min_element = function_with_traits<min_element_>;
}
