//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>
#include <eve/function/fma.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_128_> fnma_(EVE_SUPPORTS(avx2_),
                                         wide<T, N, x86_128_> const &a,
                                         wide<T, N, x86_128_> const &b,
                                         wide<T, N, x86_128_> const &c) noexcept
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      if constexpr( supports_fma3 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm_fnmadd_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm_fnmadd_ps(a, b, c);
      }
      else
        return fma(-a, b, c);
    }
    else
      return fma(-a, b, c);
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_256_> fnma_(EVE_SUPPORTS(avx2_),
                                         wide<T, N, x86_256_> const &a,
                                         wide<T, N, x86_256_> const &b,
                                         wide<T, N, x86_256_> const &c) noexcept
  {
    if constexpr( std::is_floating_point_v<T> )
    {
      if constexpr( supports_fma4 )
      {
        if constexpr( std::is_same_v<T, double> )
          return _mm256_fnmadd_pd(a, b, c);
        else if constexpr( std::is_same_v<T, float> )
          return _mm256_fnmadd_ps(a, b, c);
      }
      else
        return fma(-a, b, c);
    }
    else
      return fma(-a, b, c);
  }
}
