//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/fma.hpp>

namespace eve::detail
{
template<real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                fma_(EVE_SUPPORTS(neon128_),
                     pedantic_type const&,
                     wide<T, N> const                &v0,
                     wide<T, N> const                &v1,
                     wide<T, N> const                &v2) noexcept requires arm_abi<abi_t<T, N>>
{
  return fma(v0, v1, v2);
}
}
