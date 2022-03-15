//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/algo/array_utils.hpp>
#include <eve/algo/common_forceinline_lambdas.hpp>
#include <eve/algo/concepts.hpp>
#include <eve/algo/for_each_iteration.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/traits.hpp>


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

        found = unalign(it) + *match;
        return true;
      }

      template <typename I, std::size_t size>
      EVE_FORCEINLINE bool unrolled_step(std::array<I, size> arr)
      {
        auto tests = array_map(arr, load_and_apply{p});

        auto overall = array_reduce(tests, eve::logical_or);
        if (!eve::any(overall)) return false;

        // TODO: this might not be ideal, see: #764
        std::optional<std::ptrdiff_t> match;
        std::size_t pos = find_branchless(tests, detail::find_branchless_lambda{&match});
        found = unalign(arr[0]) + (pos * iterator_cardinal_v<I>) + *match;

        return true;
      }

      UnalignedI found;
      P p;
    };

    template <relaxed_range Rng, typename P>
    EVE_FORCEINLINE auto operator()(Rng&& rng, P p) const
    {
      if (rng.begin() == rng.end()) return unalign(rng.begin());

      auto processed = preprocess_range(TraitsSupport::get_traits(), EVE_FWD(rng));

      auto l = unalign(processed.begin()) + (processed.end() - processed.begin());

      delegate<unaligned_t<decltype(processed.begin())>, P> d{l, p};
      algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
      return unalign(rng.begin()) + (d.found - processed.begin());
    }
  };

  inline constexpr auto find_if = function_with_traits<find_if_>[default_simple_algo_traits];

  template <typename TraitsSupport>
  struct find_ : TraitsSupport
  {
    template <relaxed_range Rng, typename T>
    EVE_FORCEINLINE auto operator()(Rng&& rng, T v) const
    {
      return find_if[TraitsSupport::get_traits()](EVE_FWD(rng), equal_to{v});
    }
  };

  inline constexpr auto find = function_with_traits<find_>[find_if.get_traits()];

  template <typename TraitsSupport>
  struct find_if_not_ : TraitsSupport
  {
    template <relaxed_range Rng, typename P>
    EVE_FORCEINLINE auto operator()(Rng&& rng, P p) const
    {
      return find_if[TraitsSupport::get_traits()](EVE_FWD(rng), not_p{p});
    }
  };

  inline constexpr auto find_if_not = function_with_traits<find_if_not_>[find_if.get_traits()];
}
