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
#include <eve/algo/common_forceinline_lambdas.hpp>
#include <eve/algo/for_each_iteration.hpp>
#include <eve/algo/preprocess_range.hpp>
#include <eve/algo/traits.hpp>

#include <eve/function/compress_store.hpp>

#include <array>

namespace eve::algo
{
  template <typename TraitsSupport>
  struct remove_if_ : TraitsSupport
  {
    template <typename UnalignedI, typename P>
    struct delegate
    {
      explicit delegate(UnalignedI out, P p) : out(out), p(p) {}

      EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto /*idx*/)
      {
        auto loaded = eve::load[ignore](it);
        auto mask   = !p(loaded);  // we decied that ! can be optimized well enough
        out = unsafe(compress_store[ignore])(loaded, mask, out);
        return false;
      }

      template <typename I, std::size_t size>
      EVE_FORCEINLINE bool unrolled_step(std::array<I, size> arr)
      {
        array_map(arr, call_single_step(this));
        return false;
      }

      UnalignedI out;
      P p;
    };

    template <relaxed_range Rng, typename P>
    EVE_FORCEINLINE auto operator()(Rng&& rng, P p) const
    {
      if (rng.begin() == rng.end()) return unalign(rng.begin());

      auto processed = preprocess_range(TraitsSupport::get_traits(), EVE_FWD(rng));

      auto iteration = algo::for_each_iteration(processed.traits(), processed.begin(), processed.end());
      auto out = iteration.base;
      delegate<unaligned_t<decltype(out)>, P> d{unalign(out), p};
      iteration(d);
      return unalign(rng.begin()) + (d.out - processed.begin());
    }
  };

  inline constexpr auto remove_if = function_with_traits<remove_if_>[no_traits];

  template <typename TraitsSupport>
  struct remove_ : TraitsSupport
  {
    template <relaxed_range Rng, typename T>
    EVE_FORCEINLINE auto operator()(Rng&& rng, T v) const
    {
      return remove_if[TraitsSupport::get_traits()](EVE_FWD(rng), equal_to{v});
    }
  };

  inline constexpr auto remove = function_with_traits<remove_>[no_traits];
}
