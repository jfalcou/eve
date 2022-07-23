//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/array_utils.hpp>
#include <eve/algo/for_each_iteration.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/traits.hpp>
#include <eve/algo/views/convert.hpp>
#include <eve/function/convert.hpp>
#include <eve/module/core.hpp>
#include <eve/traits.hpp>

#include <utility>

namespace eve::algo
{
template<typename TraitsSupport> struct transform_reduce_ : TraitsSupport
{
  using traits_type = typename TraitsSupport::traits_type;

  template<typename MapOp, typename AddOp, typename Zero, typename SumWide> struct delegate
  {
    MapOp map_op;
    AddOp add_op;
    Zero  zero;

    std::array<SumWide, get_unrolling<traits_type>()> sums;

    delegate(MapOp map_op, AddOp add_op, Zero zero, SumWide init)
        : map_op(map_op)
        , add_op(add_op)
        , zero(zero)
    {
      sums.fill(as_value(zero, as<SumWide> {}));
      sums[0] = add_op(sums[0], init);
    }

    EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto idx)
    {
      auto loaded = eve::load[ignore](it);
      auto mapped = map_op(loaded);
      auto cvt    = eve::convert(mapped, eve::as<element_type_t<SumWide>> {});
      sums[idx()] = add_op(sums[idx()], if_else(ignore, cvt, zero));
      return false;
    }

    template<typename I, std::size_t size>
    EVE_FORCEINLINE bool unrolled_step(std::array<I, size> arr)
    {
      eve::detail::for_<0, 1, size>([&](auto idx) { step(arr[idx()], ignore_none, idx); });
      return false;
    }

    EVE_FORCEINLINE auto finish()
    {
      auto sum = array_reduce(sums, add_op);
      return eve::reduce(sum, add_op);
    }
  };

  template<eve::algo::relaxed_range Rng, typename MapOp, typename AddOp, typename Zero, typename U>
  EVE_FORCEINLINE U
  operator()(Rng&& rng, MapOp map_op, std::pair<AddOp, Zero> add_zero, U init) const
  {
    algo::traits consider_sum_type {consider_types<U>};
    auto         processed =
        preprocess_range(algo::default_to(TraitsSupport::get_traits(), consider_sum_type), rng);

    if( processed.begin() == processed.end() ) return init;

    using I = decltype(processed.begin());

    using sum_wide_t        = wide<U, iterator_cardinal_t<I>>;
    sum_wide_t init_as_wide = eve::as_value(add_zero.second, as<sum_wide_t> {});
    init_as_wide.set(0, init);

    delegate<MapOp, AddOp, Zero, sum_wide_t> d {
        map_op, add_zero.first, add_zero.second, init_as_wide};

    algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
    return d.finish();
  }

  template<eve::algo::relaxed_range Rng, typename MapOp, typename U>
  EVE_FORCEINLINE U operator()(Rng&& rng, MapOp map_op, U init) const
  {
    return operator()(EVE_FWD(rng), map_op, std::pair {eve::add, eve::zero}, init);
  }
};

//================================================================================================
//! @addtogroup algos
//! @{
//!  @var transform_reduce
//!
//!  @brief SIMD version of std::transform_reduce for a single range
//!
//!  Configurable @callable performing a SIMD optimized version of the transform_reduce
//!  By default, the operation will be unrolled by a factor of 4, align memory accesses and
//!  perform conversions if needed.
//!
//!  Due to the nature of how SIMD algorithms work, the reduce operation has to be paired with its,
//!  neutral element. For example, for add you pass `{add, zero}` as zero is the identity for add.
//!  Instead of zero it can be beneficial to pass eve's constants like `eve::zero`, `eve::one`
//!  because sometimes the implementation can be improved
//!
//!  @note
//!         * The interface differs from the standard because we felt this better matches our use case:
//!           do unary transformation and then accumulate that.
//!         * Multiple range interface is omitted for simplicity. Use eve::zip to get that effect.
//!         * eve::transform_reduce requires less requirement on the operations than eve::views::map.
//!           In transform_reduce we don't need the map_op to be a template, for example.
//!         * Compilers can auto-vectorize reductions, especially with special options.
//!           Maybe you don't need a library implementation.
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
//!     template <eve::algo::relaxed_range Rng, typename MapOp, typename U>
//!     U transform_reduce(Rng&& rng, MapOp map_op, U init);                                    // 1
//!
//!     template< eve::algo::relaxed_range Rng, typename MapOp
//!             , typename AddOp, typename Zero, typename U
//!             >
//!     U transform_reduce(Rng&& rng, MapOp map_op, std::pair<AddOp, Zero> add_zero, U init);   // 2
//!   }
//!   @endcode
//!
//!   1. Applies `map_op` to each element in the range `rng` and reduces the results along with the
//!      initial value `init` using regular addition as the reduce operation.
//!
//!   2. Applies `map_op` to each element in the range `rng` and reduces the results along with the
//!      initial value `init` using the `add_zero` reduce operation and neutral element.
//!
//!   **Parameters**
//!
//!    * `rng`:       Relaxed input range to process
//!    * `init`:      Initial value. Also type of init matches the result type
//!    * `map_op`:    Transformation operation
//!    * `add_zero`:  Pair of reduction operation (commutative/associative) and an identity (zero)
//!                   for it. Default add_zero is `{eve::plus, eve::zero}`.
//!
//!   **Return value**
//!
//!   1. Sum of `init` and `map_op` applied on each element of `rng`.
//!   2. Generalized sum of `init` and `map_op` applied on each element of `rng` using `add_zero`.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/transform_reduce.cpp}
//!
//! @}
//================================================================================================
inline constexpr
auto transform_reduce = function_with_traits<transform_reduce_>[default_simple_algo_traits];
}
