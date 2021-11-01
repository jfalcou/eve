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

#include <type_traits>

namespace eve::detail
{
  //================================================================================================
  // 256 bits ==> 256/128 bits
  // We need to care only for AVX-sized input, which means we'll only convert by using a
  // Split/Compute/Combine skeletons (my PHD director would be proud :p).
  // We don't call aggregate cause aggregate wants EVERYTHING to be sliceable.
  //================================================================================================
  template<real_scalar_value In, typename N, real_scalar_value Out>
  EVE_FORCEINLINE wide<Out, N>
  convert_(EVE_SUPPORTS(avx_), wide<In, N> const &v0, as<Out> const &tgt) noexcept
    requires std::same_as<abi_t<In, N>, x86_256_>
  {
    if constexpr( std::is_same_v<In, Out> )
    {
      return v0;
    }
    else if constexpr( current_api >= avx2 && (N::value == 4)
                       && std::is_integral_v<In> && (sizeof(In) == 8)
                       && std::is_integral_v<Out> && (sizeof(Out) == 4) )
    {
      // u64 to u32
      const auto p = _mm256_permutevar8x32_epi32(v0, _mm256_set_epi32(7, 5, 3, 1, 6, 4, 2, 0));
      return _mm256_extractf128_si256(p, 0);
    }
    else
    {
      auto[l,h] = v0.slice();
      auto ll = eve::convert(l,tgt);
      auto hh = eve::convert(h,tgt);
      return wide<Out, N>(ll,hh);
    }
  }

  //================================================================================================
  // 128 bits ==> 256 bits
  // This one actually calls stuff. The conversion available are the one that take an AVX
  // sized registers and put it back into a SSE sized register. E.g  converting 4x double AVX
  // will fit nicely into a 4x float AVX.
  //
  // Some conversion are done by hand because they're critical and doesn't exist in AVX/AVX2
  //================================================================================================
  template<real_scalar_value In, typename N, real_scalar_value Out>
  EVE_FORCEINLINE wide<Out, N>
  convert_(EVE_SUPPORTS(avx_), wide<In, N> const &v0, as<Out> const &tgt) noexcept
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
    else if constexpr( std::is_same_v<Out, double>  && (N::value == 4) )
    {
      if constexpr( std::is_same_v<In, float> )
      {
        return _mm256_cvtps_pd(v0);
      }
      else if constexpr( std::is_same_v<In, std::int32_t> )
      {
        return _mm256_cvtepi32_pd(v0);
      }
      else
      {
        return convert_(EVE_RETARGET(sse4_2_), v0, tgt);
      }
    }
    //==============================================================================================
    // Convert to 16 bits integers
    //==============================================================================================
    else if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 2) && (N::value == 16))
    {
      if constexpr( current_api >= avx2 )
      {
        if constexpr( std::is_integral_v<In> && (sizeof(In) == 1) )
        {
          if constexpr( std::is_signed_v<In> )
          {
            return _mm256_cvtepi8_epi16(v0);
          }
          else
          {
            return _mm256_cvtepu8_epi16(v0);
          }
        }
        else
        {
          return convert_(EVE_RETARGET(sse4_2_), v0, tgt);
        }
      }
      else
      {
        return convert_(EVE_RETARGET(sse4_2_), v0, tgt);
      }
    }
    //==============================================================================================
    // Convert to 32 bits integers
    //==============================================================================================
    else if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 4) && (N::value == 8))
    {
      if constexpr( current_api >= avx2 )
      {
        if constexpr( std::is_integral_v<In> && (sizeof(In) == 1) )
        {
          if constexpr( std::is_signed_v<In> )
          {
            return _mm256_cvtepi8_epi32(v0);
          }
          else
          {
            return _mm256_cvtepu8_epi32(v0);
          }
        }
        else if constexpr( std::is_integral_v<In> && (sizeof(In) == 2) )
        {
          if constexpr( std::is_signed_v<In> )
          {
            return _mm256_cvtepi16_epi32(v0);
          }
          else
          {
            return _mm256_cvtepu16_epi32(v0);
          }
        }
        else
        {
          return convert_(EVE_RETARGET(sse4_2_), v0, tgt);
        }
      }
      else
      {
        return convert_(EVE_RETARGET(sse4_2_), v0, tgt);
      }
    }
    //==============================================================================================
    // Convert to 64 bits integers
    //==============================================================================================
    else if constexpr( std::is_integral_v<Out> && (sizeof(Out) == 8) && (N::value == 4))
    {
      if constexpr( current_api >= avx2 )
      {
        if constexpr( std::is_integral_v<In> && (sizeof(In) == 1) )
        {
          if constexpr( std::is_signed_v<In> )
          {
            return _mm256_cvtepi8_epi64(v0);
          }
          else
          {
            return _mm256_cvtepu8_epi64(v0);
          }
        }
        else if constexpr( std::is_integral_v<In> && (sizeof(In) == 2) )
        {
          if constexpr( std::is_signed_v<In> )
          {
            return _mm256_cvtepi16_epi64(v0);
          }
          else
          {
            return _mm256_cvtepu16_epi64(v0);
          }
        }
        else if constexpr( std::is_integral_v<In> && (sizeof(In) == 4) )
        {
          if constexpr( std::is_signed_v<In> )
          {
            return _mm256_cvtepi32_epi64(v0);
          }
          else
          {
            return _mm256_cvtepu32_epi64(v0);
          }
        }
        else
        {
          return convert_(EVE_RETARGET(sse4_2_), v0, tgt);
        }
      }
      else
      {
        if constexpr( std::is_integral_v<In> && (sizeof(In) == 4) )
        {
          auto[l,h] = v0.slice();
          auto ll = eve::convert(l,tgt);
          auto hh = eve::convert(h,tgt);
          return wide<Out, N>(ll,hh);
        }
        else
        {
          return convert_(EVE_RETARGET(sse4_2_), v0, tgt);
        }
      }
    }
    else
    {
      return convert_(EVE_RETARGET(sse4_2_), v0, tgt);
    }
  }

  template<real_scalar_value In, typename N, real_scalar_value Out>
  EVE_FORCEINLINE logical<wide<Out, N>>
  convert_(EVE_SUPPORTS(sse2_), logical<wide<In, N>> const &v0, as<logical<Out>> const &tgt) noexcept
    requires std::same_as<abi_t<In, N>, x86_256_> && (abi_t<In, N>::is_wide_logical)
  {
    constexpr auto c  = categorize<wide<In, N>>();

    if constexpr ( match(c, category::int16x16, category::uint16x16) && sizeof(Out) == 1 )
    {
      auto [l, h] = v0.slice();
      return _mm_packs_epi16(l, h);
    }
    else return convert_(EVE_RETARGET(simd_), v0, tgt);
  }
}
