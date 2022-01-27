//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>


namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> abs_(EVE_SUPPORTS(vmx_), wide<T, N> const& v) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N>>();

          if constexpr( cat && category::unsigned_) return v;
    else  if constexpr( cat && category::size64_  ) return map(eve::abs, v);
    else                                            return vec_abs(v.storage());
  }
}
