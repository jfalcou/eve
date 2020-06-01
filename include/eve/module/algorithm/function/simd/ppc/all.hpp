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

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(vmx_), logical<wide<T, N, ppc_>> const &v0) noexcept
  {
    auto m = v0.bits();

    if constexpr( N::value == 1 )
    {
      return static_cast<bool>(m[0]);
    }
    else if constexpr( N::value == expected_cardinal_v<T, ppc_> )
    {
      return vec_all_eq(m.storage(), True(as(v0)).storage());
    }
    else
    {
      using type = logical<wide<T, N, ppc_>>;

      auto mm = apply<N::value>([](auto... I) { return type {(I < N::value)...}; });
      m &= mm.bits();

      return vec_all_eq(m.storage(), mm.storage());
    }
  }
}

