//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> mul_(EVE_SUPPORTS(neon128_)
                                      , wide<T, N> v0
                                      , wide<T, N> const &v1) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    return v0 *= v1;
  }

  template<real_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<T, N> mul_(EVE_SUPPORTS(neon128_)
                                      , wide<T, N> v0
                                      , U const &v1) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    return v0 *= v1;
  }

  template<real_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<T, N> mul_(EVE_SUPPORTS(neon128_)
                                      , U const & v0
                                      , wide<T, N> v1) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    return v1 *= v0;
  }
}
