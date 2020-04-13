//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_DIV_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_DIV_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_>
  div_(EVE_SUPPORTS(neon128_),wide<T, N, neon64_> v0, wide<T, N, neon64_> const &v1) noexcept
  {
    return v0 /= v1;
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_>
  div_(EVE_SUPPORTS(neon128_), wide<T, N, neon128_> v0, wide<T, N, neon128_> const &v1) noexcept
  {
    return v0 /= v1;
  }
}

#endif
