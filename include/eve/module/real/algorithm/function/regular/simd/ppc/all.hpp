//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/true.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(vmx_), logical<wide<T, N>> const &v0) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    auto m = v0.bits();

    if constexpr( N::value == 1 )
    {
      return static_cast<bool>(m.get(0));
    }
    else if constexpr( N::value == expected_cardinal_v<T, ppc_> )
    {
      return vec_all_eq(m.storage(), true_(eve::as(v0)).storage());
    }
    else
    {
      using type = logical<wide<T, N>>;

      auto mm = apply<N::value>([](auto... I) { return type {(I < N::value)...}; });
      m &= mm.bits();

      return vec_all_eq(m.storage(), mm.storage());
    }
  }
}
