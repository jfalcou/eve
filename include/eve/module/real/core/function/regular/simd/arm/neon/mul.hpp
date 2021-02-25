//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> mul_(EVE_SUPPORTS(neon128_)
                                      , wide<T, N, ABI> v0
                                      , wide<T, N, ABI> const &v1) noexcept
  {
    return v0 *= v1;
  }

  template<real_scalar_value T, typename N, arm_abi ABI, real_scalar_value U>
  EVE_FORCEINLINE wide<T, N, ABI> mul_(EVE_SUPPORTS(neon128_)
                                      , wide<T, N, ABI> v0
                                      , U const &v1) noexcept
  {
    return v0 *= v1;
  }

  template<real_scalar_value T, typename N, arm_abi ABI, real_scalar_value U>
  EVE_FORCEINLINE wide<T, N, ABI> mul_(EVE_SUPPORTS(neon128_)
                                      , U const & v0
                                      , wide<T, N, ABI> v1) noexcept
  {
    return v1 *= v0;
  }
}
