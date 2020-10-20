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

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, ppc_> ceil_(EVE_SUPPORTS(vmx_), wide<T, N, ppc_> const &v0) noexcept
  {
    if constexpr(floating_value<T>) return vec_ceil(v0.storage());
    else                            return v0;
  }
}

