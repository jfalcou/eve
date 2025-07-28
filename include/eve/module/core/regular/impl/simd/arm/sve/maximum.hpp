//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/remove_garbage.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE auto maximum_(EVE_REQUIRES(sve_), O const& opts, wide<T, N> v) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    if constexpr (O::contains(splat2))
    {
      // Attempts to force the use of a broadcasting mov
      return wide<T, N>{ wide<T>{ maximum[opts.drop(splat2)].retarget(current_api, v) } };
    }
    else
    {
      // svmaxv is expensive on some architectures.
      // The scalar approach should be faster for <=2 lanes on Neoverse at least up to V3.
      if constexpr (match_option<condition_key, O, ignore_none_> && (N::value <= 2))
      {
        T r = v.get(0);

        for_<1, 1, N::value>([&](auto i)
        {
          r = eve::max(r, v.get(i));
        });

        return r;
      }
      else
      {
        auto m = expand_mask_no_garbage(opts[condition_key], as<logical<wide<T, N>>>{});
        return svmaxv(m, v);
      }
    }
  }
}
