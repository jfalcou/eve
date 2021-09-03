//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/array_utils.hpp>
#include <eve/algo/concepts.hpp>
#include <eve/algo/for_each_iteration.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/traits.hpp>
#include <eve/algo/unalign.hpp>

#include <eve/function/any.hpp>
#include <eve/function/first_true.hpp>
#include <eve/function/logical_or.hpp>

#include <array>

namespace eve::algo
{
  namespace detail
  {
    // needed to forceinline
    struct find_branchless_lambda
    {
      std::optional<std::ptrdiff_t> *match;

      EVE_FORCEINLINE bool operator()(auto test) const
      {
        auto _m = eve::first_true(test);
        if( _m ) *match = _m;
        return _m.has_value();
      }
    };
  }

  template <typename TraitsSupport>
  struct find_if_ : TraitsSupport
  {
    template <typename UnalignedI, typename P>
    struct delegate
    {
      explicit delegate(UnalignedI found, P p) : found(found), p(p) {}

      EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto /*idx*/)
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
          detail::find_branchless_lambda{&match});
        constexpr std::ptrdiff_t lanes = typename I::cardinal{}();
        found = arr[0].unaligned() + (pos * lanes) + *match;

        return true;
      }

      UnalignedI found;
      P p;
    };

    template <relaxed_range Rng, typename P>
    EVE_FORCEINLINE auto operator()(Rng&& rng, P p) const
    {
      if (rng.begin() == rng.end()) return unalign(rng.begin());

      auto processed = preprocess_range(TraitsSupport::get_traits(), std::forward<Rng>(rng));

      auto l = processed.begin().unaligned() + (processed.end() - processed.begin());

      delegate<unaligned_t<decltype(processed.begin())>, P> d{l, p};
      algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
      return unalign(rng.begin()) + (d.found - processed.begin());
    }
  };

  inline constexpr auto find_if = function_with_traits<find_if_>[default_simple_algo_traits];
}
