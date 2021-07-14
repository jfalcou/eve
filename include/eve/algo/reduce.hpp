//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/algo/array_utils.hpp>
#include <eve/algo/for_each_iteration.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/traits.hpp>

#include <eve/function/add.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/reduce.hpp>

#include <algorithm>
#include <utility>

namespace eve::algo
{
  template <instance_of<algo::traits> Traits>
  struct reduce_
  {
    Traits tr_;

    constexpr explicit reduce_(Traits tr) : tr_(tr) {}

    template <typename Settings>
    constexpr auto operator[](algo::traits<Settings> tr) const
    {
      auto sum = default_to(tr, tr_);
      return reduce_<decltype(sum)>{sum};
    }

    template <typename Op, typename Wide>
    struct delegate
    {
      Op op;
      Wide zero;

      std::array<Wide, get_unrolling<Traits>()> sums;

      delegate(Op op, Wide zero, Wide init) : op(op), zero(zero) {
        sums.fill(zero);
        sums[0] = op(sums[0], init);
      }

      EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto idx)
      {
        // TODO: FIX-#802 use a non-zero sum.
        sums[idx()] = op(sums[idx()], eve::load[ignore.else_(zero)](it));
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

    template <typename Rng, typename Op, typename T, typename U>
    EVE_FORCEINLINE U operator()(Rng&& rng, std::pair<Op, T> op_zero, U init) const
    {
      auto processed = preprocess_range(
        algo::default_to(tr_, eve::algo::traits(common_with_types<U>)),
        std::forward<Rng>(rng));

      using I = decltype(processed.begin());

      if (processed.begin() == processed.end()) return init;

      auto op = op_zero.first;
      using wide_t = typename I::wide_value_type;
      wide_t zero(op_zero.second);
      wide_t init_as_wide{zero};
      init_as_wide.set(0, init);

      delegate<decltype(op), wide_t> d{op, zero, init_as_wide};

      algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
      return eve::convert(d.finish(), eve::as<U>{});
    }

    template <typename Rng, typename U>
    EVE_FORCEINLINE U operator()(Rng&& rng, U init) const
    {
      return operator()(std::forward<Rng>(rng), std::pair{eve::add, 0}, init);
    }
  };

  inline constexpr reduce_ reduce{default_simple_algo_traits};
}
