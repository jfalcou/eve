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

#include <eve/function/any.hpp>
#include <eve/function/first_true.hpp>
#include <eve/function/logical_or.hpp>

#include <array>

namespace eve::algo
{
  template <instance_of<algo::traits> Traits>
  struct find_if_
  {
    Traits tr_;

    constexpr explicit find_if_(Traits tr) : tr_(tr) {}

    template <typename Settings>
    constexpr auto operator[](algo::traits<Settings> tr) const
    {
      return find_if_<algo::traits<Settings>>{default_to(tr, tr_)};
    }

    template <typename UnalignedI, typename P>
    struct delegate
    {
      explicit delegate(UnalignedI found, P p) : found(found), p(p) {}

      EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore)
      {
        eve::logical test = p(eve::load[ignore](it));
        std::optional match = eve::first_true[ignore](test);
        if (!match) return false;

        found = it.unaligned() + *match;
        return true;
      }

      template <typename I, std::size_t size>
      EVE_FORCEINLINE bool unrolled_step(std::array<I, size> arr)
      {
        auto tests = array_map(arr, [&](I it) { return p(eve::load(it)); });

        auto overall = array_reduce(tests, eve::logical_or);
        if (!eve::any(overall)) return false;

        // TODO: this might not be ideal, see: #764
        std::optional<std::ptrdiff_t> match;
        std::size_t pos = find_branchless(tests,
          [&](auto test) {
            auto _m = eve::first_true(test);
            if (_m) match = _m;
            return _m.has_value();
        });
        constexpr std::ptrdiff_t lanes = typename I::cardinal{}();
        found = arr[0].unaligned() + (pos * lanes) + *match;

        return true;
      }

      UnalignedI found;
      P p;
    };

    template <typename Rng, typename P>
    EVE_FORCEINLINE auto operator()(Rng&& rng, P p) const
    {
      auto processed = preprocess_range(tr_, std::forward<Rng>(rng));
      if (processed.begin() == processed.end())
      {
        return processed.to_output_iterator(processed.begin());
      }

      auto l = processed.begin().unaligned() + (processed.end() - processed.begin());

      delegate<decltype(processed.end()), P> d{l, p};
      algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
      return processed.to_output_iterator(d.found);
    }
  };
  inline constexpr find_if_ find_if{default_simple_algo_traits};
}
