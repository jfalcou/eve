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
  template<typename... Vs>
  EVE_FORCEINLINE auto  make( as_<double> const&, eve::sse_ const&, Vs... vs) noexcept
                        requires( __m128d, If<(sizeof...(Vs) <= 2)> )
  {
    if constexpr(sizeof...(vs) == 2)  return _mm_setr_pd(static_cast<double>(vs)...);
    if constexpr(sizeof...(vs) == 1)  return _mm_set1_pd(static_cast<double>(vs)...);
  }

  // -----------------------------------------------------------------------------------------------
  // float cases 4, 2 & 1
  template<typename... Vs>
  EVE_FORCEINLINE auto  make(as_<float> const&, eve::sse_ const&, Vs... vs) noexcept
                        requires( __m128, If<(sizeof...(Vs) <= 4)> )
  {
    if constexpr(sizeof...(vs) == 4)  return _mm_setr_ps(static_cast<float>(vs)...);
    if constexpr(sizeof...(vs) == 2)  return _mm_setr_ps(static_cast<float>(vs)...,0.f,0.f);
    if constexpr(sizeof...(vs) == 1)  return _mm_set1_ps(static_cast<float>(vs)...);
  }

  // -----------------------------------------------------------------------------------------------
  // *int64 cases 2 & 1
  template<typename T, typename V0, typename V1>
  EVE_FORCEINLINE auto  make( as_<T> const&, eve::sse_ const&, V0 v0, V1 v1) noexcept
                        requires( __m128i, Integral<T>, If<(sizeof(T)==8)> )
  {
    __m128i that;
    T* ptr = reinterpret_cast<detail::alias_t<T>*>( &that );
    ptr[0] = v0;
    ptr[1] = v1;
    detail::ignore(that);

    return that;
  }

  template<typename T, typename V0>
  EVE_FORCEINLINE auto  make( as_<T> const&, eve::sse_ const&, V0 v0) noexcept
                        requires( __m128i, Integral<T>, If<(sizeof(T)==8)> )
  {
    __m128i that;
    T* ptr = reinterpret_cast<detail::alias_t<T>*>( &that );
    ptr[0] = v0;
    ptr[1] = v0;

    detail::ignore(that);

    return that;
  }

  template<typename T,typename... Vs>
  EVE_FORCEINLINE auto  make(as_<T> const&, eve::sse_ const&, Vs... vs) noexcept
                        requires( __m128i, Integral<T>, If<sizeof(T)!=8>)
  {
    if constexpr(sizeof...(vs)==1)
    {
      if(sizeof(T)==4)  return _mm_set1_epi32(vs...);
      if(sizeof(T)==2)  return _mm_set1_epi16(vs...);
      if(sizeof(T)==1)  return _mm_set1_epi8(vs...);
    }

    if constexpr(sizeof...(vs) == 4   && sizeof(T)==4)
      return _mm_setr_epi32(vs...);
    if constexpr(sizeof...(vs) == 2   && sizeof(T)==4)
      return _mm_setr_epi32(vs...,0,0);

    if constexpr(sizeof...(vs) == 8   && sizeof(T)==2)
      return _mm_setr_epi16(vs...);
    if constexpr(sizeof...(vs) == 4   && sizeof(T)==2)
      return _mm_setr_epi16(vs...,0,0,0,0);
    if constexpr(sizeof...(vs) == 2   && sizeof(T)==2)
      return _mm_setr_epi16(vs...,0,0,0,0,0,0);

    if constexpr(sizeof...(vs) == 16  && sizeof(T)==1)
      return _mm_setr_epi8(vs...);
    if constexpr(sizeof...(vs) ==  8  && sizeof(T)==1)
      return _mm_setr_epi8(vs...,0,0,0,0,0,0,0,0);
    if constexpr(sizeof...(vs) ==  4  && sizeof(T)==1)
      return _mm_setr_epi8(vs...,0,0,0,0,0,0,0,0,0,0,0,0);
    if constexpr(sizeof...(vs) ==  2  && sizeof(T)==1)
      return _mm_setr_epi8(vs...,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
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
