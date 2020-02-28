//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_FMS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_FMS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> fms_(EVE_SUPPORTS(neon128_),
                                           wide<T, N, neon64_> const &v0,
                                           wide<T, N, neon64_> const &v1,
                                           wide<T, N, neon64_> const &v2) noexcept
  {
    return fma(v0,v1,-v2);
  }

  template<typename D, typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> fms_(EVE_SUPPORTS(neon128_),
                                           D const &,
                                           wide<T, N, neon64_> const &v0,
                                           wide<T, N, neon64_> const &v1,
                                           wide<T, N, neon64_> const &v2) noexcept
  {
    return fma(v0,v1,-v2);
  }

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> fms_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon128_> const &v0,
                                            wide<T, N, neon128_> const &v1,
                                            wide<T, N, neon128_> const &v2) noexcept
  {
    return fma(v0,v1,-v2);
  }

  template<typename D, typename T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> fms_(EVE_SUPPORTS(neon128_),
                                            D const &,
                                            wide<T, N, neon128_> const &v0,
                                            wide<T, N, neon128_> const &v1,
                                            wide<T, N, neon128_> const &v2) noexcept
  {
    return fms(v0, v1, v2);
  }
}

#endif
