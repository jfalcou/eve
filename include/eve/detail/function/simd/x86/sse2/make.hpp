//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_X86_SSE2_MAKE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_X86_SSE2_MAKE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/compiler.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace eve { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // double cases 2 & 1
  template< typename... Vs
          , typename = std::enable_if_t<sizeof...(Vs) <= 2>
          >
  EVE_FORCEINLINE __m128d make( as_<double> const&, eve::sse_ const&, Vs... vs) noexcept
  {
    if constexpr(sizeof...(vs) == 2)
      return _mm_setr_pd(static_cast<double>(vs)...);
    if constexpr(sizeof...(vs) == 1)
      return _mm_set1_pd(static_cast<double>(vs)...);
  }

  // -----------------------------------------------------------------------------------------------
  // float cases 4, 2 & 1
  template< typename... Vs
          , typename = std::enable_if_t<sizeof...(Vs) <= 4>
          >
  EVE_FORCEINLINE __m128 make(as_<float> const&, eve::sse_ const&, Vs... vs) noexcept
  {
    if constexpr(sizeof...(vs) == 4)
      return _mm_setr_ps(static_cast<float>(vs)...);
    if constexpr(sizeof...(vs) == 2)
      return _mm_setr_ps(static_cast<float>(vs)...,0.f,0.f);
    if constexpr(sizeof...(vs) == 1)
      return _mm_set1_ps(static_cast<float>(vs)...);
  }

  // -----------------------------------------------------------------------------------------------
  // *int64 cases 2 & 1
  template<typename T, typename V0, typename V1>
  EVE_FORCEINLINE std::enable_if_t<(std::is_integral_v<T> && sizeof(T)==8),__m128i>
  make( as_<T> const&, eve::sse_ const&, V0 v0, V1 v1) noexcept
  {
    __m128i that;
    T* ptr = reinterpret_cast<detail::alias_t<T>*>( &that );
    ptr[0] = v0;
    ptr[1] = v1;
    detail::ignore(that);

    return that;
  }

  template<typename T, typename V0>
  EVE_FORCEINLINE std::enable_if_t<(std::is_integral_v<T> && sizeof(T)==8),__m128i>
  make( as_<T> const&, eve::sse_ const&, V0 v0) noexcept
  {
    __m128i that;
    T* ptr = reinterpret_cast<detail::alias_t<T>*>( &that );
    ptr[0] = v0;
    ptr[1] = v0;

    detail::ignore(that);

    return that;
  }

  // -----------------------------------------------------------------------------------------------
  // *int32 cases 4, 2 & 1
  template<typename T, typename... Vs>
  EVE_FORCEINLINE std::enable_if_t<std::is_integral_v<T> && (sizeof...(Vs) <= 4) && (sizeof(T)==4),__m128i>
  make( as_<T> const&, eve::sse_ const&, Vs... vs) noexcept
  {
    if constexpr(sizeof...(vs) == 4)
      return _mm_setr_epi32(static_cast<T>(vs)...);
    if constexpr(sizeof...(vs) == 2)
      return _mm_setr_epi32(static_cast<T>(vs)...,0,0);
    if constexpr(sizeof...(vs) == 1)
      return _mm_set1_epi32(static_cast<T>(vs)...);
  }

  // -----------------------------------------------------------------------------------------------
  // *int16 cases 8, 4, 2 & 1
  template<typename T, typename... Vs>
  EVE_FORCEINLINE std::enable_if_t<std::is_integral_v<T> && (sizeof...(Vs) <= 8) && (sizeof(T)==2),__m128i>
  make( as_<T> const&, eve::sse_ const&, Vs... vs) noexcept
  {
    if constexpr(sizeof...(vs) == 8)
      return _mm_setr_epi16(static_cast<T>(vs)...);
    if constexpr(sizeof...(vs) == 4)
      return _mm_setr_epi16(static_cast<T>(vs)...,0,0,0,0);
    if constexpr(sizeof...(vs) == 2)
      return _mm_setr_epi16(static_cast<T>(vs)...,0,0,0,0,0,0);
    if constexpr(sizeof...(vs) == 1)
      return _mm_set1_epi16(static_cast<T>(vs)...);
  }

  // -----------------------------------------------------------------------------------------------
  // *int8 cases 16, 8, 4, 2 & 1
  template<typename T, typename... Vs>
  EVE_FORCEINLINE std::enable_if_t<std::is_integral_v<T> && (sizeof...(Vs) <= 16) && (sizeof(T)==1),__m128i>
  make( as_<T> const&, eve::sse_ const&, Vs... vs) noexcept
  {
    if constexpr(sizeof...(vs) == 16)
      return _mm_setr_epi8(static_cast<T>(vs)...);
    if constexpr(sizeof...(vs) == 8)
      return _mm_setr_epi8(static_cast<T>(vs)...,0,0,0,0,0,0,0,0);
    if constexpr(sizeof...(vs) == 4)
      return _mm_setr_epi8(static_cast<T>(vs)...,0,0,0,0,0,0,0,0,0,0,0,0);
    if constexpr(sizeof...(vs) == 2)
      return _mm_setr_epi8(static_cast<T>(vs)...,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
    if constexpr(sizeof...(vs) == 1)
      return _mm_set1_epi8(static_cast<T>(vs)...);
  }

  //------------------------------------------------------------------------------------------------
  // logical cases
  template<typename T, typename... Vs>
  EVE_FORCEINLINE auto make( as_<logical<T>> const&, eve::sse_ const&, Vs... vs) noexcept
  {
    return make(as_<T>{},eve::sse_{},logical<T>(vs).mask()...);
  }
} }

#if defined(EVE_COMP_IS_GNUC)
#pragma GCC diagnostic pop
#endif

#endif
