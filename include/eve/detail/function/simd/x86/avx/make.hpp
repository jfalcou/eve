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
#include <eve/detail/compiler.hpp>
#include <eve/as.hpp>

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace eve { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // double cases 4 & 1
  template<typename... Vs>
  EVE_FORCEINLINE __m256d make( as_<double> const&, eve::avx_ const&, Vs... vs) noexcept
  {
    if constexpr(sizeof...(vs)==4)
      return _mm256_setr_pd(vs...);
    if constexpr(sizeof...(vs)==1)
      return _mm256_set1_pd(vs...);
  }

  // -----------------------------------------------------------------------------------------------
  // *int64 cases 4 & 1
  template<typename T,typename... Vs>
  EVE_FORCEINLINE std::enable_if_t<(std::is_integral_v<T> && sizeof(T)==8),__m256i>
  make(as_<T> const&, eve::avx_ const&, Vs... vs) noexcept
  {
    if constexpr(sizeof...(vs)==4)
      return _mm256_setr_epi64x(vs...);
    if constexpr(sizeof...(vs)==1)
      return _mm256_set1_epi64x(vs...);
  }

  // -----------------------------------------------------------------------------------------------
  // float cases 8 & 1
  template<typename... Vs>
  EVE_FORCEINLINE __m256 make( as_<float> const&, eve::avx_ const&, Vs... vs) noexcept
  {
    if constexpr(sizeof...(vs)==8)
      return _mm256_setr_ps(vs...);
    if constexpr(sizeof...(vs)==1)
      return _mm256_set1_ps(vs...);
  }

  // -----------------------------------------------------------------------------------------------
  // *int32 cases 8 & 1
  template<typename T,typename... Vs>
  EVE_FORCEINLINE std::enable_if_t<(std::is_integral_v<T> && sizeof(T)==4),__m256i>
  make(as_<T> const&, eve::avx_ const&, Vs... vs) noexcept
  {
    if constexpr(sizeof...(vs)==8)
      return _mm256_setr_epi32(vs...);
    if constexpr(sizeof...(vs)==1)
      return _mm256_set1_epi32(vs...);
  }

  // -----------------------------------------------------------------------------------------------
  // *int16 cases 16 & 1
  template<typename T,typename... Vs>
  EVE_FORCEINLINE std::enable_if_t<(std::is_integral_v<T> && sizeof(T)==2),__m256i>
  make(as_<T> const&, eve::avx_ const&, Vs... vs) noexcept
  {
    if constexpr(sizeof...(vs)==16)
      return _mm256_setr_epi16(vs...);
    if constexpr(sizeof...(vs)==1)
      return _mm256_set1_epi16(vs...);
  }

  // -----------------------------------------------------------------------------------------------
  // *int8 cases 32 & 1
  template<typename T,typename... Vs>
  EVE_FORCEINLINE std::enable_if_t<(std::is_integral_v<T> && sizeof(T)==1),__m256i>
  make(as_<T> const&, eve::avx_ const&, Vs... vs) noexcept
  {
    if constexpr(sizeof...(vs)==32)
      return _mm256_setr_epi8(vs...);
    if constexpr(sizeof...(vs)==1)
      return _mm256_set1_epi8(vs...);
  }
} }

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic pop
#endif

#endif
