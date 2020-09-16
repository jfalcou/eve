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
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> fnma_(EVE_SUPPORTS(neon128_),
                                            wide<T, N, neon64_> const &v0,
                                            wide<T, N, neon64_> const &v1,
                                            wide<T, N, neon64_> const &v2) noexcept
  {
    if constexpr( std::is_same_v<T, float> )
      return vfms_f32(v2, v1, v0);
#if defined(__aarch64__)
    else if constexpr( std::is_same_v<T, double> )
      return vfms_f64(v2, v1, v0);
#endif
    else
      return v2 - v0 * v1;
  }

  template<decorator D, real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon64_> fnma_(EVE_SUPPORTS(neon128_),
                                            D const &,
                                            wide<T, N, neon64_> const &v0,
                                            wide<T, N, neon64_> const &v1,
                                            wide<T, N, neon64_> const &v2) noexcept
  {
    return fnma(v0, v1, v2);
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> fnma_(EVE_SUPPORTS(neon128_),
                                             wide<T, N, neon128_> const &v0,
                                             wide<T, N, neon128_> const &v1,
                                             wide<T, N, neon128_> const &v2) noexcept
  {
    if constexpr( std::is_same_v<T, float> )
      return vfmsq_f32(v2, v1, v0);
#if defined(__aarch64__)
    if constexpr( std::is_same_v<T, double> )
      return vfmsq_f64(v2, v1, v0);
#endif
    else
      return v2 - v0 * v1;
  }

  template<decorator D, real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, neon128_> fnma_(EVE_SUPPORTS(neon128_),
                                             D const &,
                                             wide<T, N, neon128_> const &v0,
                                             wide<T, N, neon128_> const &v1,
                                             wide<T, N, neon128_> const &v2) noexcept
  {
    return fnma(v0, v1, v2);
  }
}

