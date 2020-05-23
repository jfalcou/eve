//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_FMS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_FMS_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/forward.hpp>
#include <eve/function/minus.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> fms_(EVE_SUPPORTS(neon128_),
                                           wide<T, N, neon64_> const &v0,
                                           wide<T, N, neon64_> const &v1,
                                           wide<T, N, neon64_> const &v2) noexcept
  {
    return fma(v0, v1, -v2);
  }

  template<decorator D, real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> fms_(EVE_SUPPORTS(neon128_),
                                           D const &,
                                           wide<T, N, neon64_> const &v0,
                                           wide<T, N, neon64_> const &v1,
                                           wide<T, N, neon64_> const &v2) noexcept
  {
    return fma(v0, v1, -v2);
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> fms_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon128_> const &v0,
                                            wide<T, N, neon128_> const &v1,
                                            wide<T, N, neon128_> const &v2) noexcept
  {
    return fma(v0, v1, -v2);
  }

  template<decorator D, real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> fms_(EVE_SUPPORTS(neon128_),
                                            D const &,
                                            wide<T, N, neon128_> const &v0,
                                            wide<T, N, neon128_> const &v1,
                                            wide<T, N, neon128_> const &v2) noexcept
  {
    return fma(v0, v1, -v2);
  }
}

#endif
