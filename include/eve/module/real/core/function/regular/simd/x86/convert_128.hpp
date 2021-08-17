//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/is_less.hpp>

#include <type_traits>

namespace eve::detail
{
  //================================================================================================
  // Forewords
  // Like its 256/512 bits brethren, this convert function is quite long and may looks repetitive
  // as it's a web of if constexpr based on IN and OUT properties.
  // Be aware that:
  //  - calls to the generic version takes care of larger inputs and unroll properly
  //  - if some unsigned cases are missing it's because we have no intrinsics.
  //  - some repetitive code has been factorized out in lambda based systems until we found out
  //    some compilers had sub-par inlining of lambdas. This is sad, I am sad, you are sad too.
  //================================================================================================

  //================================================================================================
  // 128 bits ==> 128 bits
  //================================================================================================
  template<real_scalar_value In, typename N, real_scalar_value Out>
  EVE_FORCEINLINE wide<Out, N>
  convert_(EVE_SUPPORTS(sse2_), wide<In, N> const &v0, as<Out> const &tgt) noexcept
    requires std::same_as<abi_t<In, N>, x86_128_>
  {
    //==============================================================================================
    // Idempotent call
    //==============================================================================================
    if constexpr( std::is_same_v<In, Out> )
    {
      return v0;
    }
    //==============================================================================================
    // Convert to double
    //==============================================================================================
    else if constexpr( std::is_same_v<Out, double> )
    {
           if constexpr( std::is_same_v<In, float> && (N::value <= 2))
      {
        return _mm_cvtps_pd(v0);
      }
      else if constexpr( std::is_same_v<In, std::int32_t> && (N::value <= 2))
      {
        return _mm_cvtepi32_pd(v0);
      }
      else
      {
        return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    //==============================================================================================
    // Convert to float
    //==============================================================================================
    else if constexpr( std::is_same_v<Out, float> )
    {
      if constexpr( std::is_same_v<In, double> && (N::value <= 2) )
      {
        return _mm_cvtpd_ps(v0);
      }
      else if constexpr( std::is_same_v<In, std::int32_t> && (N::value <= 4) )
      {
        return _mm_cvtepi32_ps(v0);
      }
      else
      {
        return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    //==============================================================================================
    // Convert to 32 bits integer
    //==============================================================================================
    else if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 4) )
    {
           if constexpr( std::is_same_v<In, float> )                     return _mm_cvttps_epi32(v0);
      else if constexpr( std::is_same_v<In, double> && (N::value <= 2) ) return _mm_cvttpd_epi32(v0);
      else if constexpr (sizeof(In) == 1 && N() <= 4)
      {
             if constexpr( eve::current_api < eve::sse4_1 )
        {
          using type16 = std::conditional_t<std::is_signed_v<In>, std::int16_t, std::uint16_t>;
          auto wide16 = eve::convert(v0, eve::as<type16>{});
          return eve::convert(wide16, tgt);
        }
        else if constexpr ( std::is_signed_v<In> )                       return _mm_cvtepi8_epi32(v0);
        else                                                             return _mm_cvtepu8_epi32(v0);
      }
      else if constexpr (sizeof(In) == 2 && N() <= 4)
      {
             if constexpr( eve::current_api < eve::sse4_1 )
        {
          auto const mask = [&]() { if constexpr(std::is_signed_v<In>)  return (v0<0).bits();
                                    else                                return _mm_setzero_si128();
                                  }();

          if constexpr(N::value <= 8)
          {
            return _mm_unpacklo_epi16( v0, mask );
          }
          else
          {
            // clang can generate this from aggregate+above, but not gcc nor msvc
            wide<Out, fixed<4>> l = _mm_unpacklo_epi16( v0, mask );
            wide<Out, fixed<4>> h = _mm_unpackhi_epi16( v0, mask );
            return wide<Out, N>(l,h);
          }
        }
        else if constexpr ( std::is_signed_v<In> )                      return _mm_cvtepi16_epi32(v0);
        else                                                            return _mm_cvtepu16_epi32(v0);
      }
      else
      {
        return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    //==============================================================================================
    // Convert to 16 bits integer
    //==============================================================================================
    else if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 2) )
    {
      //============================================================================================
      // 8 -> 16 bits
      //============================================================================================
      if constexpr( std::is_integral_v<In> && (sizeof(In) == 1) )
      {
        if constexpr( current_api >= sse4_1 )
        {
          if constexpr( std::is_signed_v<In> && (N::value <= 8) )
          {
            return _mm_cvtepi8_epi16(v0);
          }
          else if constexpr( !std::is_signed_v<In>  && (N::value <= 8) )
          {
            return _mm_cvtepu8_epi16(v0);
          }
          else
          {
            return convert_(EVE_RETARGET(simd_), v0, tgt);
          }
        }
        else
        {
          auto const mask = [&]() { if constexpr(std::is_signed_v<In>)  return (v0<0).bits();
                                    else                                return _mm_setzero_si128();
                                  }();

          if constexpr(N::value <= 8)
          {
            return _mm_unpacklo_epi8( v0, mask );
          }
          else
          {
            // clang can generate this from aggregate+above, but not gcc nor msvc
            wide<Out, fixed<8>> l = _mm_unpacklo_epi8( v0, mask );
            wide<Out, fixed<8>> h = _mm_unpackhi_epi8( v0, mask );
            return wide<Out, N>(l,h);
          }
        }
      }
      else
      {
        return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    //==============================================================================================
    // Convert to 64 bits integer
    //==============================================================================================
    else if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 8) )
    {
      //============================================================================================
      // 8 -> 64 bits
      //============================================================================================
      if constexpr( std::is_integral_v<In> && (sizeof(In) == 1))
      {
        if constexpr( current_api >= sse4_1 )
        {
          if constexpr( std::is_signed_v<In> && (N::value <= 2) )
          {
            return _mm_cvtepi8_epi64(v0);
          }
          else if constexpr( !std::is_signed_v<In>  && (N::value <= 2) )
          {
            return _mm_cvtepu8_epi64(v0);
          }
          else
          {
            return convert_(EVE_RETARGET(simd_), v0, tgt);
          }
        }
        else
        {
          return convert_(EVE_RETARGET(simd_), v0, tgt);
        }
      }
      //============================================================================================
      // 16 -> 64 bits
      //============================================================================================
      if constexpr( std::is_integral_v<In> && (sizeof(In) == 2))
      {
        if constexpr( current_api >= sse4_1 )
        {
          if constexpr( std::is_signed_v<In> && (N::value <= 2) )
          {
            return _mm_cvtepi16_epi64(v0);
          }
          else if constexpr( !std::is_signed_v<In>  && (N::value <= 2) )
          {
            return _mm_cvtepu16_epi64(v0);
          }
          else
          {
            return convert_(EVE_RETARGET(simd_), v0, tgt);
          }
        }
        else
        {
          return convert_(EVE_RETARGET(simd_), v0, tgt);
        }
      }
      //============================================================================================
      // 32 -> 64 bits
      //============================================================================================
      if constexpr( std::is_integral_v<In> && (sizeof(In) == 4))
      {
        if constexpr( current_api >= sse4_1 )
        {
          if constexpr( std::is_signed_v<In> && (N::value <= 2) )
          {
            return _mm_cvtepi32_epi64(v0);
          }
          else if constexpr( !std::is_signed_v<In>  && (N::value <= 2) )
          {
            return _mm_cvtepu32_epi64(v0);
          }
          else
          {
            return convert_(EVE_RETARGET(simd_), v0, tgt);
          }
        }
        else
        {
          auto const mask = [&]() { if constexpr(std::is_signed_v<In>)  return (v0<0).bits();
                                    else                                return _mm_setzero_si128();
                                  }();

          if constexpr(N::value <= 2)
          {
            return _mm_unpacklo_epi32( v0, mask );
          }
          else
          {
            // clang can generate this from aggregate+above, but not gcc nor msvc
            wide<Out, fixed<2>> l = _mm_unpacklo_epi32( v0, mask );
            wide<Out, fixed<2>> h = _mm_unpackhi_epi32( v0, mask );
            return wide<Out, N>(l,h);
          }
        }
      }
      else
      {
        return convert_(EVE_RETARGET(simd_), v0, tgt);
      }
    }
    else
    {
      return convert_(EVE_RETARGET(simd_), v0, tgt);
    }
  }

  template<real_scalar_value In, typename N, real_scalar_value Out>
  EVE_FORCEINLINE logical<wide<Out, N>>
  convert_(EVE_SUPPORTS(sse2_), logical<wide<In, N>> const &v0, as<logical<Out>> const &tgt) noexcept
    requires std::same_as<abi_t<In, N>, x86_128_> && (abi_t<In, N>::is_wide_logical)
  {
    constexpr auto c  = categorize<wide<In, N>>();

    if constexpr ( match(c, category::int16x8, category::uint16x8) && sizeof(Out) == 1 )
    {
      return  _mm_packs_epi16(v0, v0);
    }
    else return convert_(EVE_RETARGET(simd_), v0, tgt);
  }
}
