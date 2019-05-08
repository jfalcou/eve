//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // double cases 2 & 1
  template<typename... Vs>
  EVE_FORCEINLINE auto make(as_<double> const &,
                            eve::sse_ const &,
                            Vs... vs) noexcept requires(__m128d, If<(sizeof...(Vs) <= 2)>)
  {
    if constexpr(sizeof...(vs) == 2) return _mm_setr_pd(static_cast<double>(vs)...);
    if constexpr(sizeof...(vs) == 1) return _mm_set1_pd(static_cast<double>(vs)...);
  }

  // -----------------------------------------------------------------------------------------------
  // float cases 4, 2 & 1
  template<typename... Vs>
  EVE_FORCEINLINE auto make(as_<float> const &,
                            eve::sse_ const &,
                            Vs... vs) noexcept requires(__m128, If<(sizeof...(Vs) <= 4)>)
  {
    if constexpr(sizeof...(vs) == 4) return _mm_setr_ps(static_cast<float>(vs)...);
    if constexpr(sizeof...(vs) == 2) return _mm_setr_ps(static_cast<float>(vs)..., 0.f, 0.f);
    if constexpr(sizeof...(vs) == 1) return _mm_set1_ps(static_cast<float>(vs)...);
  }

  // -----------------------------------------------------------------------------------------------
  // integer cases
  template<typename T, typename... Vs>
  EVE_FORCEINLINE auto
  make(as_<T> const &, eve::sse_ const &, Vs... vs) noexcept requires(__m128i, Integral<T>)
  {
    if(sizeof(T) == 8)
    {
      __m128i that;
      T *     ptr = reinterpret_cast<detail::alias_t<T> *>(&that);
      T       d[] = {static_cast<T>(vs)...};
      ptr[ 0 ]    = d[ 0 ];
      ptr[ 1 ]    = d[ 1 ];
      detail::ignore(that);
      return that;
    }

    if constexpr(sizeof...(vs) == 4 && sizeof(T) == 4)
      return _mm_setr_epi32(static_cast<int>(vs)...);
    if constexpr(sizeof...(vs) == 2 && sizeof(T) == 4)
      return _mm_setr_epi32(static_cast<int>(vs)..., 0, 0);

    if constexpr(sizeof...(vs) == 8 && sizeof(T) == 2)
      return _mm_setr_epi16(static_cast<short>(vs)...);
    if constexpr(sizeof...(vs) == 4 && sizeof(T) == 2)
      return _mm_setr_epi16(static_cast<short>(vs)..., 0, 0, 0, 0);
    if constexpr(sizeof...(vs) == 2 && sizeof(T) == 2)
      return _mm_setr_epi16(static_cast<short>(vs)..., 0, 0, 0, 0, 0, 0);

    if constexpr(sizeof...(vs) == 16 && sizeof(T) == 1)
      return _mm_setr_epi8(static_cast<char>(vs)...);
    if constexpr(sizeof...(vs) == 8 && sizeof(T) == 1)
      return _mm_setr_epi8(static_cast<char>(vs)..., 0, 0, 0, 0, 0, 0, 0, 0);
    if constexpr(sizeof...(vs) == 4 && sizeof(T) == 1)
      return _mm_setr_epi8(static_cast<char>(vs)..., 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if constexpr(sizeof...(vs) == 2 && sizeof(T) == 1)
      return _mm_setr_epi8(static_cast<char>(vs)..., 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  }

  template<typename T, typename Vs>
  EVE_FORCEINLINE auto make(as_<T> const &, eve::sse_ const &, Vs vs) noexcept requires(__m128i,
                                                                                        Integral<T>)
  {
    if(sizeof(T) == 8)
    {
      __m128i that;
      T *     ptr = reinterpret_cast<detail::alias_t<T> *>(&that);
      ptr[ 0 ] = ptr[ 1 ] = static_cast<T>(vs);
      detail::ignore(that);
      return that;
    }
    if(sizeof(T) == 4) return _mm_set1_epi32(static_cast<int>(vs));
    if(sizeof(T) == 2) return _mm_set1_epi16(static_cast<short>(vs));
    if(sizeof(T) == 1) return _mm_set1_epi8(static_cast<char>(vs));
  }

  //------------------------------------------------------------------------------------------------
  // logical cases
  template<typename T, typename... Vs>
  EVE_FORCEINLINE auto make(as_<logical<T>> const &, eve::sse_ const &, Vs... vs) noexcept
  {
    return make(as_<T>{}, eve::sse_{}, logical<T>(vs).mask()...);
  }
}

#if defined(EVE_COMP_IS_GNUC)
#  pragma GCC diagnostic pop
#endif

#endif
