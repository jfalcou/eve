//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_X86_AVX_MAKE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_X86_AVX_MAKE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/compiler.hpp>
#include <eve/as.hpp>

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // double cases 4 & 1
  template<typename... Vs>
  EVE_FORCEINLINE __m256d make( as_<double> const&, eve::avx_ const&, Vs... vs) noexcept
  {
    if constexpr(sizeof...(vs)==4)  return _mm256_setr_pd(vs...);
    if constexpr(sizeof...(vs)==1)  return _mm256_set1_pd(vs...);
  }

  // -----------------------------------------------------------------------------------------------
  // float cases 8 & 1
  template<typename... Vs>
  EVE_FORCEINLINE __m256 make( as_<float> const&, eve::avx_ const&, Vs... vs) noexcept
  {
    if constexpr(sizeof...(vs)==8)  return _mm256_setr_ps(vs...);
    if constexpr(sizeof...(vs)==1)  return _mm256_set1_ps(vs...);
  }

  // -----------------------------------------------------------------------------------------------
  // Integers case
  template<typename T,typename... Vs>
  EVE_FORCEINLINE auto  make(as_<T> const&, eve::avx_ const&, Vs... vs) noexcept
                        requires( __m256i, Integral<T>)
  {
    if constexpr(sizeof...(vs)==1)
    {
      if(sizeof(T)==8)  return _mm256_set1_epi64x(vs...);
      if(sizeof(T)==4)  return _mm256_set1_epi32(vs...);
      if(sizeof(T)==2)  return _mm256_set1_epi16(vs...);
      if(sizeof(T)==1)  return _mm256_set1_epi8(vs...);
    }

    if constexpr(sizeof...(vs) == 4   && sizeof(T)==8)  return _mm256_setr_epi64x(vs...);
    if constexpr(sizeof...(vs) == 8   && sizeof(T)==4)  return _mm256_setr_epi32(vs...);
    if constexpr(sizeof...(vs) == 16  && sizeof(T)==2)  return _mm256_setr_epi16(vs...);
    if constexpr(sizeof...(vs) == 32  && sizeof(T)==1)  return _mm256_setr_epi8(vs...);
  }

  //------------------------------------------------------------------------------------------------
  // logical cases
  template<typename T, typename... Vs>
  EVE_FORCEINLINE auto make( as_<logical<T>> const&, eve::avx_ const&, Vs... vs) noexcept
  {
    return make(as_<T>{},eve::avx_{},logical<T>(vs).mask()...);
  }
}

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic pop
#endif

#endif
