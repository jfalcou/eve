//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/fma.hpp>
#include <type_traits>

namespace eve::detail
{
  template<real_scalar_value T, typename N, x86_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> fms_( EVE_SUPPORTS(avx2_)
                                      , wide<T, N, ABI> const& a
                                      , wide<T, N, ABI> const& b
                                      , wide<T, N, ABI> const& c
                                      ) noexcept
  {
    if constexpr( std::is_integral_v<T> )
    {
      if constexpr( supports_xop )
      {
              if constexpr( sizeof(T) == 2 )  return _mm_msub_epi16(a, b, c);
        else  if constexpr( sizeof(T) == 4 )  return _mm_msub_epi32(a, b, c);
        else                                  return fms_(EVE_RETARGET(cpu_), a, b, c);
      }
      else                                    return fms_(EVE_RETARGET(cpu_), a, b, c);
    }
    else
    {
      constexpr auto cat = categorize<wide<T, N, ABI>>();

            if constexpr( cat == category::float64x8  )  return _mm512_fmsub_pd(a, b, c);
      else  if constexpr( cat == category::float32x16 )  return _mm512_fmsub_ps(a, b, c);
      else if constexpr( supports_fma3 )
      {
              if constexpr( cat == category::float64x4  ) return _mm256_fmsub_pd(a, b, c);
        else  if constexpr( cat == category::float64x2  ) return _mm_fmsub_pd(a, b, c);
        else  if constexpr( cat == category::float32x8  ) return _mm256_fmsub_ps(a, b, c);
        else  if constexpr( cat == category::float32x4  ) return _mm_fmsub_ps(a, b, c);
      }
      else if constexpr( supports_fma4 )
      {
              if constexpr( cat == category::float64x4  ) return _mm256_msub_pd(a, b, c);
        else  if constexpr( cat == category::float64x2  ) return _mm_msub_pd(a, b, c);
        else  if constexpr( cat == category::float32x8  ) return _mm256_msub_ps(a, b, c);
        else  if constexpr( cat == category::float32x4  ) return _mm_msub_ps(a, b, c);
      }
      else                                                return fma(a, b, -c);
    }
  }
}
