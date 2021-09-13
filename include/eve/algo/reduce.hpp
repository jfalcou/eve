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

#include <eve/constant/as_value.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/add.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/reduce.hpp>
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

    template <typename Rng, typename Op, typename Zero, typename U>
    EVE_FORCEINLINE U operator()(Rng&& rng, std::pair<Op, Zero> op_zero, U init) const
    {
      // FIX-#938: this should not be a common type actually, should just be U.
      using T = common_type_t<value_type_t<std::remove_cvref_t<Rng>>, U>;

      auto cvt_rng = eve::algo::convert(std::forward<Rng>(rng), as<T>{});
      auto processed = preprocess_range(TraitsSupport::get_traits(), cvt_rng);

      using I = decltype(processed.begin());

      if (processed.begin() == processed.end()) return init;

      using wide_t = typename I::wide_value_type;
      wide_t init_as_wide = eve::as_value(op_zero.second, as<wide_t>{});
      init_as_wide.set(0, init);

      delegate<Op, Zero, wide_t> d{op_zero.first, op_zero.second, init_as_wide};

      algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
      return eve::convert(d.finish(), eve::as<U>{});
    }

    template <typename Rng, typename U>
    EVE_FORCEINLINE U operator()(Rng&& rng, U init) const
    {
      return operator()(std::forward<Rng>(rng), std::pair{eve::add, eve::zero}, init);
    }
  };

  inline constexpr auto reduce = function_with_traits<reduce_>[default_simple_algo_traits];
}
