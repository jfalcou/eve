//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/algo/array_utils.hpp>
#include <eve/algo/converting_iterator.hpp>
#include <eve/algo/traits.hpp>

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
      return reduce_<algo::traits<Settings>>{default_to(tr, tr_)};
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

      EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore)
      {
        // TODO: I used to have small steps add to their own sums.
        //       We should do that too probably.
        sums[0] = op(sums[0], eve::load[ignore.else(zero)](it));
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

      auto finish() {
        auto sum = array_reduce(sums, op);
        return eve::spat(eve::reduce)(sum, op);
      }
    };

    template <typename Rng, typename Op, typename T, typename U>
    auto operator()(Rng&& rng, std::pair<Op, T> op_zero, U init)
    {
      auto processed = preprocess_range(tr_, std::forward<Rng>(rng));
      using _I = decltype(processed.begin());
      using res_t = std::common_type_t<typename I::value_type, U>;

      if (processed.begin() == processed.end()) return res_t{init};

      // We probably need to just have a traits for cardinal
      constexpr std::ptrdiff_t N = [] {
        if constexpr (sizeof(res_t) == sizeof(typename I::value_type)) return typename I::cardinal{}();
        else
        {
          return typename I::cardinal{}() * eve::expected_cardinal_v<U> /
                 eve::expected_cardinal_v<typename I::value_type>;
        }
      }();

      auto f = eve::algo::convert(processed.begin(), eve::as<res_t>{});
      auto l = eve::algo::convert(processed.end(),   eve::as<res_t>{});
      auto op = op_zero.first;
      using wide_t = typename decltype(f)::wide_value_type;
      wide_t zero(op_zero.second);
      wide_t init_as_wide{zero};
      init_as_wide.set(0, init);

      delegate<decltype(op), wide_t> d{op, zero, init_as_wide};

      algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
      return d.finish();
    }
  };
