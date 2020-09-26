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
  EVE_FORCEINLINE wide<T, N, arm_64_>
                  mul_(EVE_SUPPORTS(neon128_), wide<T, N, arm_64_> v0, wide<T, N, arm_64_> const &v1) noexcept
  {
    return v0 *= v1;
  }

  template<real_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(neon128_), U const &v0, wide<T, N, arm_64_> v1)
  {
    return v1 *= v0;
  }

  template<real_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(neon128_), wide<T, N, arm_64_> v0, U const &v1) noexcept
  {
    return v0 *= v1;
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, arm_128_>
                  mul_(EVE_SUPPORTS(neon128_), wide<T, N, arm_128_> v0, wide<T, N, arm_128_> const &v1) noexcept
  {
    return v0 *= v1;
  }

  template<real_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(neon128_), U const &v0, wide<T, N, arm_128_> v1)
  {
    return v1 *= v0;
  }

  template<real_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(neon128_), wide<T, N, arm_128_> v0, U const &v1) noexcept
  {
    return v0 *= v1;
  }
}

