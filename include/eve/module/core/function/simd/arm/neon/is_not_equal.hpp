//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_IS_NOT_EQUAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_IS_NOT_EQUAL_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/logical_not.hpp>

namespace eve::detail
{
  template<real_value T, typename N, arm_abi ABI>
  EVE_FORCEINLINE auto is_not_equal_(EVE_SUPPORTS(neon128_)
                                    , wide<T, N, ABI> const &v0
                                    , wide<T, N, ABI> const &v1) noexcept
  {
    return !(v0 == v1);
  }
}

#endif
