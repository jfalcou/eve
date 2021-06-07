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
#include <eve/algo/one_range_algorithm_adapter.hpp>
#include <eve/algo/traits.hpp>

#include <eve/function/any.hpp>
#include <eve/function/first_true.hpp>
#include <eve/function/logical_or.hpp>

#include <array>

namespace eve::algo
{
  struct find_if_ : one_range_algorithm_adapter<find_if_>
  {
    static constexpr auto default_traits()
    {
      return default_simple_algo_traits;
    };

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

        // TODO: this is not the best solution, see: #764
        auto overall = array_reduce(tests, eve::logical_or);
        if (!eve::any(overall)) return false;

        std::size_t i = size - 1;
        std::optional<std::ptrdiff_t> match;
        std::size_t pos = i;

        array_reverse_it(tests, [&](auto test) mutable {
          auto local_match = eve::first_true(test);
          // should generate cmovs
          if (local_match)
          {
            pos = i;
            match = local_match;
          }
          --i;
        });

        const std::ptrdiff_t lanes = typename I::cardinal{}();
        found = arr[0].unaligned() + (pos * lanes) + *match;

        return true;
      }

      UnalignedI found;
      P p;
    };

    template <typename P>
    EVE_FORCEINLINE auto impl(auto processed, P p) const
    {
      if (processed.begin() == processed.end())
      {
        return processed.to_output_iterator(processed.begin());
      }

      auto l = processed.begin().unaligned() + (processed.end() - processed.begin());

      delegate d{l, p};
      algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
      return processed.to_output_iterator(d.found);
    }
  } inline constexpr find_if;
}
