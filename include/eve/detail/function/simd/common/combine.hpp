//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/meta.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto
  combine(cpu_ const &, wide<T, N, ABI> const &l, wide<T, N, ABI> const &h) noexcept
  {
    using that_t = wide<T, typename N::combined_type>;

    if constexpr( is_emulated_v<ABI> )
    {
      return apply<N::value>([&](auto... I) { return that_t {l[I]..., h[I]...}; });
    }
    else if constexpr( is_aggregated_v<ABI> )
    {
      that_t that;

      that.storage().segments[0] = l;
      that.storage().segments[1] = h;

      return that;
    }
  }
}

