//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_BITWISE_CAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_BITWISE_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/function/simd/detail/bitwise_cast.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  //-----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE wide<Target, M, sse_> bitwise_cast_(EVE_SUPPORTS(sse2_),
                                                      wide<Source, N, sse_> const &v0,
                                                      as_<wide<Target, M, sse_>> const &) noexcept
  {
    // Idempotent call
    if constexpr(std::is_same_v<Source, Target>) return v0;
    // bitwise_cast from float
    else if constexpr(std::is_same_v<Source, float>)
    {
      if constexpr(std::is_same_v<Target, double>) return _mm_castps_pd(v0);
      else if constexpr(std::is_integral_v<Target>) return _mm_castps_si128(v0);
    }
    // bitwise_cast from double
    else if constexpr(std::is_same_v<Source, double>)
    {
      if constexpr(std::is_same_v<Target, float>) return _mm_castpd_ps(v0);
      else if constexpr(std::is_integral_v<Target>) return _mm_castpd_si128(v0);
    }
    // bitwise_cast from integer
    else if constexpr(std::is_integral_v<Source>)
    {
      if constexpr(std::is_same_v<Target, float>) return _mm_castsi128_ps(v0);
      else if constexpr(std::is_same_v<Target, double>) return _mm_castsi128_pd(v0);
      else if constexpr(std::is_integral_v<Target>) return v0.storage();
    }
  }

  // SSE2 supports logical bitwise casting
  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE logical<wide<Target, M, sse_>>
                  bitwise_cast_(EVE_SUPPORTS(sse2_),
                                wide<Source, N, sse_> const &              v0,
                                as_<logical<wide<Target, M, sse_>>> const &tgt) noexcept
  {
    return a2l_isocast_(v0, tgt);
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE wide<Target, M, sse_>
                  bitwise_cast_(EVE_SUPPORTS(sse2_),
                                logical<wide<Source, N, sse_>> const &v0,
                                as_<wide<Target, M, sse_>> const &    tgt) noexcept
  {
    return l2a_isocast_(v0, tgt);
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE logical<wide<Target, M, sse_>>
                  bitwise_cast_(EVE_SUPPORTS(sse2_),
                                logical<wide<Source, N, sse_>> const &     v0,
                                as_<logical<wide<Target, M, sse_>>> const &tgt) noexcept
  {
    return l2l_isocast_(v0, tgt);
  }


  //-----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE wide<Target, M, avx_> bitwise_cast_(EVE_SUPPORTS(avx_),
                                                      wide<Source, N, avx_> const &v0,
                                                      as_<wide<Target, M, avx_>> const &) noexcept
  {
    // Idempotent call
    if constexpr(std::is_same_v<Source, Target>) return v0;

    // bitwise_cast from float
    else if constexpr(std::is_same_v<Source, float>)
    {
      if constexpr(std::is_same_v<Target, double>) return _mm256_castps_pd(v0);
      else if constexpr(std::is_integral_v<Target>) return _mm256_castps_si256(v0);
    }
    // bitwise_cast from double
    else if constexpr(std::is_same_v<Source, double>)
    {
      if constexpr(std::is_same_v<Target, float>) return _mm256_castpd_ps(v0);
      else if constexpr(std::is_integral_v<Target>) return _mm256_castpd_si256(v0);
    }
    // bitwise_cast from integer
    if constexpr(std::is_integral_v<Source>)
    {
      if constexpr(std::is_same_v<Target, float>) return _mm256_castsi256_ps(v0);
      else if constexpr(std::is_same_v<Target, double>) return _mm256_castsi256_pd(v0);
      else if constexpr(std::is_integral_v<Target>) return v0.storage();
    }
  }

  // AVX supports logical bitwise casting
  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE logical<wide<Target, M, avx_>>
                  bitwise_cast_(EVE_SUPPORTS(avx_),
                                wide<Source, N, avx_> const &              v0,
                                as_<logical<wide<Target, M, avx_>>> const &tgt) noexcept
  {
    return a2l_isocast_(v0, tgt);
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE wide<Target, M, avx_>
                  bitwise_cast_(EVE_SUPPORTS(avx_),
                                logical<wide<Source, N, avx_>> const &v0,
                                as_<wide<Target, M, avx_>> const &    tgt) noexcept
  {
    return l2a_isocast_(v0, tgt);
  }

  template<typename Target, typename Source, typename N, typename M>
  EVE_FORCEINLINE logical<wide<Target, M, avx_>>
                  bitwise_cast_(EVE_SUPPORTS(avx_),
                                logical<wide<Source, N, avx_>> const &     v0,
                                as_<logical<wide<Target, M, avx_>>> const &tgt) noexcept
  {
    return l2l_isocast_(v0, tgt);
  }
  
}

#endif
