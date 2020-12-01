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
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/numeric.hpp>

namespace eve::detail
{
  template<decorator D, real_scalar_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> fnma_(EVE_SUPPORTS(neon128_),
                                       numeric_type const &,
                                       wide<T, N, ABI> const &v0,
                                       wide<T, N, ABI> const &v1,
                                       wide<T, N, ABI> const &v2) noexcept
  {
    return fnma(v0, v1, v2);
  }
}
