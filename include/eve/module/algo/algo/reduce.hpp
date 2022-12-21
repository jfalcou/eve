//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/algo/algo/array_utils.hpp>
#include <eve/module/algo/algo/for_each_iteration.hpp>
#include <eve/module/algo/algo/preprocess_range.hpp>
#include <eve/module/algo/algo/views/convert.hpp>
#include <eve/module/algo/algo/traits.hpp>

#include <eve/traits.hpp>

#include <utility>

namespace eve::algo
{
  template <typename TraitsSupport>
  struct reduce_ : TraitsSupport
  {
    using traits_type = typename TraitsSupport::traits_type;

    template <typename Op, typename Zero, typename Wide>
    struct delegate
    {
      Op op;
      Zero zero;

      std::array<Wide, get_unrolling<traits_type>()> sums;

      delegate(Op op, Zero zero, Wide init) : op(op), zero(zero) {
        sums.fill(as_value(zero, as<Wide>{}));
        sums[0] = op(sums[0], init);
      }

      EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto idx)
      {
        auto ignore_else_0 = ignore.else_(as_value(zero, as<Wide>{}));
        sums[idx()] = op(sums[idx()], eve::load[ignore_else_0](it));
        return false;
      }

      template <typename I, std::size_t size>
      EVE_FORCEINLINE bool unrolled_step(std::array<I, size> arr)
      {
        sums =  array_map(sums, arr, [&](auto sum, auto i) {
          return op(sum, load(i));
        });
        return false;
      }

      EVE_FORCEINLINE auto finish() {
        auto sum = array_reduce(sums, op);
        return eve::reduce(sum, op);
      }
    };

    template <eve::algo::relaxed_range Rng, typename Op, typename Zero, typename U>
    EVE_FORCEINLINE U operator()(Rng&& rng, std::pair<Op, Zero> op_zero, U init) const
    {
      auto cvt_rng = views::convert(EVE_FWD(rng), as<U>{});
      auto processed = preprocess_range(TraitsSupport::get_traits(), cvt_rng);

      using I = decltype(processed.begin());

      if (processed.begin() == processed.end()) return init;

      using wide_t = wide_value_type_t<I>;
      wide_t init_as_wide = eve::as_value(op_zero.second, as<wide_t>{});
      init_as_wide.set(0, init);

      delegate<Op, Zero, wide_t> d{op_zero.first, op_zero.second, init_as_wide};

      algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
      return d.finish();
    }

    template <eve::algo::relaxed_range Rng, typename U>
    EVE_FORCEINLINE U operator()(Rng&& rng, U init) const
    {
      return operator()(EVE_FWD(rng), std::pair{eve::add, eve::zero}, init);
    }
  };


  //================================================================================================
  //! @addtogroup algos
  //! @{
  //!  @var reduce
  //!
  //!  @brief SIMD optimized version of std::reduce
  //!
  //!   Configurable @callable performing a SIMD optimized version of the reduce
  //!   By default, the operation will be unrolled by a factor of 4, align memory accesses and
  //!   perform conversions if needed.
  //!
  //!  Due to the nature of how SIMD algorithms work, the reduce operation has to be paired with its,
  //!  neutral element. For example, for add you pass `{add, zero}` as zero is the identity for add.
  //!  Instead of zero it can be beneficial to pass eve's constants like `eve::zero`, `eve::one`
  //!  because sometimes the implementation can be improved
  //!
  //!  @note
  //!         * The interface differs from the standard to be homogeneous with
  //!         eve::algo::transform_reduce.
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
  //!
  //!   @code
  //!   namespace eve::algo
  //!   {
  //!     template <eve::algo::relaxed_range Rng, typename U>
  //!     U reduce(Rng&& rng, U init);                              // 1
  //!
  //!     template <eve::algo::relaxed_range Rng, typename Op, typename Zero, typename U>
  //!     U reduce(Rng&& rng, std::pair<Op, Zero> op_zero, U init)  // 2
  //!   }
  //!   @endcode
  //!
  //!   1. Reduces the range `rng` along with the initial value `init` using regular addition.
  //!   2. Reduces the range `rng` along with the initial value `init` over `op_zero`.
  //!
  //!   **Parameters**
  //!
  //!    * `rng`:       Relaxed range  input range to process
  //!    * `init`:      Initial value. Also type of init matches the result type
  //!    * `op_zero`:   Pair of reduction operation (commutative/associative) and an identity (zero)
  //!                   for it. Default add_zero is `{eve::plus, eve::zero}`.
  //!
  //!   **Return value**
  //!
  //!   1. Sum of `init` and every elements of `rng`.
  //!   2. Generalized sum of `init` and every elements of `rng` using `op_zero`.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/algo/reduce.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto reduce = function_with_traits<reduce_>[default_simple_algo_traits];
}
