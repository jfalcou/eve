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
  // convert: logical -> logical
  //================================================================================================
  template<real_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE logical<wide<U, N>> convert_impl( EVE_SUPPORTS(sse2_)
                                                  , logical<wide<T,N>> v, as<logical<U>> const &tgt
                                                  ) noexcept
  {
    constexpr auto c_in   = categorize<wide<T, N>>();
    constexpr auto c_out  = categorize<wide<U, N>>();

    //==============================================================================================
    // 8 bits cases - Always slice
    //==============================================================================================
    if constexpr( sizeof(T) == 1 && sizeof(U) > 2 && N::value > 1)
    {
      return convert( convert(v,as<logical<std::int16_t>>{}), tgt);
    }
    //==============================================================================================
    // 16 bits cases
    //==============================================================================================
    else  if constexpr( c_in == category::int16x8 && sizeof(U) == 1 )
    {
      return  _mm_packs_epi16(v, v);
    }
    else  if constexpr( c_in == category::int16x16 && sizeof(U) == 1 )
    {
      return _mm_packs_epi16(v.slice(lower_), v.slice(upper_));
    }
    //==============================================================================================
    // 32 bits cases
    //==============================================================================================
    else  if constexpr( c_in == category::int32x4 && sizeof(U) < 4 )
    {
      auto w = _mm_packs_epi32(v, v);
      if constexpr(sizeof(U) == 1) return _mm_packs_epi16(w, w);
      else return w;
    }
    else  if constexpr( c_in == category::float32x4  )
    {
            if constexpr( sizeof(U) < 4 )
      {
        return convert( convert(v,as<logical<as_integer_t<T,signed>>>{}), tgt);
      }
      else  if constexpr( match(c_out, category::int64x2, category::uint64x2) )
      {
        return convert( convert(v,as<logical<std::int32_t>>{}), tgt);
      }
      else  if constexpr( sizeof(U) == 8 && N::value == 4 )
      {
        return eve::combine(convert( v.slice(lower_), tgt), convert( v.slice(upper_), tgt));
      }
      else return convert_impl(EVE_RETARGET(cpu_),v,tgt);
    }
    else  if constexpr( N::value == 8 && sizeof(T) == 4  )
    {
      return eve::combine(convert( v.slice(lower_), tgt), convert( v.slice(upper_), tgt));
    }
    //==============================================================================================
    // 64 cases
    //==============================================================================================
    else  if constexpr( sizeof(T) == 8 && sizeof(U) < 4 )
    {
      return convert( convert(v,as<logical<downgrade_t<as_integer_t<T,signed>>>>{}), tgt);
    }
    else  if constexpr(   c_in == category::float64x2
                      && match(c_out, category::int64x2, category::uint64x2)
                      )
    {
      return convert( convert(v,as<logical<float>>{}), tgt);
    }
    else  if constexpr( c_in == category::int64x2 )
    {
      using i_t = as<logical<std::int32_t>>;

      if constexpr(match(c_out, category::float64x2, category::float32x4))
        return convert( convert(v,i_t{}), tgt);
      else
        return convert_impl(EVE_RETARGET(cpu_),v,tgt);
    }
    else if constexpr( c_in == category::int64x4 && c_out == category::float32x4 )
    {
      return convert( convert(v,as<logical<std::int32_t>>{}), tgt);
    }
    //==============================================================================================
    // Generic case
    //==============================================================================================
    else
    {
      return convert_impl(EVE_RETARGET(cpu_),v,tgt);
    }
  }

  //================================================================================================
  // convert: float64 -> U
  //================================================================================================
  template<typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N> convert_impl ( EVE_SUPPORTS(sse2_)
                                          , wide<double,N> v, as<U> const &tgt
                                          ) noexcept
  {
    constexpr auto c_i = categorize<wide<double, N>>();
    constexpr auto c_o = categorize<wide<U, N>>();

          if constexpr( c_i == category::float64x2 )
    {
            if constexpr( c_o == category::float32x4 ) return _mm_cvtpd_ps(v);
      else  if constexpr( c_o == category::uint64x2 )
      {
        if constexpr(current_api >= avx512) return _mm_cvttpd_epu64(v);
        else                                return map(convert,v,tgt);
      }
      else  if constexpr( c_o == category::int64x2 )
      {
        if constexpr(current_api >= avx512) return _mm_cvttpd_epi64(v);
        else                                return map(convert,v,tgt);
      }
      else  if constexpr( match(c_o,category::uint32x4,category::int32x4) )
      {
        return _mm_cvttpd_epi32(v);
      }
      else  if constexpr( match(c_o,category::uint16x8,category::int16x8) )
      {
        return _mm_shufflelo_epi16(_mm_cvttpd_epi32(v), 0b00001000);
      }
      else if constexpr( match(c_o,category::uint8x16,category::int8x16) )
      {
        return convert( convert(v, as<upgrade_t<U>>{}), tgt);
      }
    }
    else  if constexpr( c_i == category::float64x4 )
    {
            if constexpr( c_o == category::float32x4 ) return _mm256_cvtpd_ps(v);
      else  if constexpr( c_o == category::uint64x4 )
      {
        if constexpr(current_api >= avx512) return _mm256_cvttpd_epu64(v);
        else                                return map(convert,v,tgt);
      }
      else  if constexpr( c_o == category::int64x4 )
      {
        if constexpr(current_api >= avx512) return _mm256_cvttpd_epi64(v);
        else                                return map(convert,v,tgt);
      }
      else  if constexpr( match(c_o,category::uint32x4,category::int32x4) )
      {
        return _mm256_cvttpd_epi32(v);
      }
      else
      {
        return convert( convert(v, as<upgrade_t<U>>{}), tgt);
      }
    }
    else  if constexpr( c_i == category::float64x8 )
    {
            if constexpr( c_o == category::float32x8) return _mm512_cvtpd_ps(v);
      else  if constexpr( c_o == category::uint64x8 ) return _mm512_cvttpd_epu64(v);
      else  if constexpr( c_o == category::int64x8  ) return _mm512_cvttpd_epi64(v);
      else  if constexpr( c_o == category::int32x8  ) return _mm512_cvttpd_epi32(v);
      else  if constexpr( c_o == category::uint32x8 ) return _mm512_cvttpd_epi32(v);
      else                     return convert( convert(v, as<upgrade_t<U>>{}), tgt);
    }
    //==============================================================================================
    // Handle aggregations
    //==============================================================================================
    else
    {
      // Save the large chunk of code required by combine on int8x16
      if constexpr( match(c_o, category::int8x16, category::uint8x16) && N::value >= 4)
      {
        return convert( convert(v, as<upgrade_t<U>>{}), tgt);
      }
      else return convert_impl(EVE_RETARGET(cpu_),v,tgt);
    }
  }

  //================================================================================================
  // convert: float32 -> U
  //================================================================================================
  template<typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N> convert_impl ( EVE_SUPPORTS(sse2_)
                                          , wide<float,N> v, as<U> const &tgt
                                          ) noexcept
  {
    constexpr auto c_i = categorize<wide<float, N>>();
    constexpr auto c_o = categorize<wide<U, N>>();
    constexpr bool api_512 = current_api >= avx512;

          if constexpr( c_i == category::float32x4 )
    {
            if constexpr( c_o == category::float64x2) return _mm_cvtps_pd(v);
      else  if constexpr( c_o == category::float64x4) return _mm256_cvtps_pd(v);
      else  if constexpr( c_o == category::int32x4  ) return _mm_cvttps_epi32(v);
      else  if constexpr( api_512 && c_o == category::uint32x4 ) return _mm_cvttps_epu32(v);
      else  if constexpr( c_o == category::uint32x4 ) return _mm_cvttps_epi32(v);
      else  if constexpr( match (c_o, category::int16x8 , category::int8x16
                                    , category::uint16x8, category::uint8x16
                        )       )
      {
        using t_t = std::conditional_t< std::is_signed_v<U>,std::int32_t, std::uint32_t>;
        return convert(convert(v, as<t_t>{}), tgt);
      }
      else  if constexpr(std::same_as<U,double> && N::value == 4)
      {
        auto[l,h] = v.slice();
        return {convert(l,tgt), convert(h,tgt)};
      }
      else  if constexpr(c_o == category::int64x2  && api_512) return _mm_cvttps_epi64(v);
      else  if constexpr(c_o == category::uint64x2 && api_512) return _mm_cvttps_epu64(v);
      else  if constexpr(c_o == category::int64x4  && api_512) return _mm256_cvttps_epi64(v);
      else  if constexpr(c_o == category::uint64x4 && api_512) return _mm256_cvttps_epu64(v);
      else  return convert_impl(EVE_RETARGET(cpu_),v,tgt);
    }
    else  if constexpr( c_i == category::float32x8 )
    {
            if constexpr( c_o == category::int32x8   ) return _mm256_cvttps_epi32(v);
      else  if constexpr( c_o == category::uint32x8  ) return _mm256_cvttps_epi32(v);
      else  if constexpr( match (c_o, category::int16x8 , category::int8x16
                                    , category::uint16x8, category::uint8x16
                        )       )
      {
        using t_t = std::conditional_t< std::is_signed_v<U>,std::int32_t, std::uint32_t>;
        return convert(convert(v, as<t_t>{}), tgt);
      }
      else  if constexpr( c_o == category::int64x8   && api_512 ) return _mm512_cvttps_epi64(v);
      else  if constexpr( c_o == category::uint64x8  && api_512 ) return _mm512_cvttps_epu64(v);
      else  if constexpr( c_o == category::float64x8 && api_512 ) return _mm512_cvtps_pd(v);
      else  return {convert(v.slice(lower_),tgt), convert(v.slice(upper_),tgt)};
    }
    else  if constexpr( c_i == category::float32x16 )
    {
            if constexpr( c_o == category::int32x16   ) return _mm512_cvttps_epi32(v);
      else  if constexpr( c_o == category::uint32x16  ) return _mm512_cvttps_epu32(v);
      else  if constexpr( match (c_o, category::int16x16 , category::int8x16
                                    , category::uint16x16, category::uint8x16
                        )       )
      {
        using t_t = std::conditional_t< std::is_signed_v<U>,std::int32_t, std::uint32_t>;
        return convert(convert(v, as<t_t>{}), tgt);
      }
      else  return {convert(v.slice(lower_),tgt), convert(v.slice(upper_),tgt)};
    }
    else return convert_impl(EVE_RETARGET(cpu_),v,tgt);
  }

  //================================================================================================
  // convert: (u)int64 -> U
  //================================================================================================
  template<integral_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N>  convert_impl( EVE_SUPPORTS(sse2_)
                                          , wide<T, N> const& v, as<U> const &tgt
                                          ) noexcept
  requires (sizeof(T) == 8)
  {
    constexpr auto c_i = categorize<wide<T, N>>();
    constexpr auto c_o = categorize<wide<U, N>>();
    constexpr auto api_512 = current_api >= avx512;

          if constexpr( match(c_i, category::int64x2, category::uint64x2))
    {
            if constexpr(c_o == category::float64x2 && api_512)
      {
        if constexpr( std::is_signed_v<T> ) return _mm_cvtepi64_pd(v);
        else                                return _mm_cvtepu64_pd(v);
      }
      else  if constexpr(c_o == category::float32x4 && api_512)
      {
        if constexpr( std::is_signed_v<T> ) return _mm_cvtepi64_ps(v);
        else                                return _mm_cvtepu64_ps(v);
      }
      else  if constexpr(c_o == category::int16x8   && api_512) return _mm_cvtepi64_epi16(v);
      else  if constexpr(c_o == category::uint16x8  && api_512) return _mm_cvtepi64_epi16(v);
      else  if constexpr(c_o == category::int8x16   && api_512) return _mm_cvtepi64_epi8(v);
      else  if constexpr(c_o == category::uint8x16  && api_512) return _mm_cvtepi64_epi8(v);
      else  if constexpr( match(c_o, category::int32x4, category::uint32x4) )
      {
        if constexpr(api_512) return _mm_cvtepi64_epi32(v);
        else                  return convert_integers_shuffle(v,tgt);
      }
      else if constexpr( c_o && category::integer_ )
      {
        // *int16 go through to *int32 then proper pack{u}s
        // *int8  go through to *int16 then *int32
        return convert( convert(v, as<upgrade_t<U>>{}), tgt);
      }
      else return convert_impl(EVE_RETARGET(cpu_),v,tgt);
    }
    else  if constexpr( match(c_i, category::int64x4, category::uint64x4))
    {
      if constexpr(api_512 && c_o == category::float64x4)
      {
        if constexpr(c_i == category::int64x4)  return _mm256_cvtepi64_pd(v);
        else                                    return _mm256_cvtepu64_pd(v);
      }
      else  if constexpr(c_o == category::float32x4 && api_512)
      {
        if constexpr(c_i == category::int64x4)  return _mm256_cvtepi64_ps(v);
        else                                    return _mm256_cvtepu64_ps(v);
      }
      else  if constexpr(c_o == category::int32x4   && api_512) return _mm256_cvtepi64_epi32(v);
      else  if constexpr(c_o == category::uint32x4  && api_512) return _mm256_cvtepi64_epi32(v);
      else  if constexpr(c_o == category::int16x8   && api_512) return _mm256_cvtepi64_epi16(v);
      else  if constexpr(c_o == category::uint16x8  && api_512) return _mm256_cvtepi64_epi16(v);
      else  if constexpr(c_o == category::int8x16   && api_512) return _mm256_cvtepi64_epi8(v);
      else  if constexpr(c_o == category::uint8x16  && api_512) return _mm256_cvtepi64_epi8(v);
      else  if constexpr( match(c_o, category::int32x4, category::uint32x4) )
      {
        if constexpr(api_512) return _mm256_cvtepi64_epi32(v);
        else if constexpr(current_api >= avx2)
        {
          auto const p = _mm256_permutevar8x32_epi32(v, _mm256_set_epi32(7, 5, 3, 1, 6, 4, 2, 0));
    #ifdef __clang__
          // What's the difference between this clang specific version and the
          // generic one you may ask? That's a good question, especially because
          // _mm256_extractf128_si128 has a latency of 3 cycles...
          //
          // It turns out clang understands better the semantic of permutevar8x32 +
          // extractf128 than permutevar8x32 + castsi256_si128. We can see this by
          // looking at the LLVM IR generated by these sequences: https://godbolt.org/z/K4dnTWPWo
          // With extractf128, we can see that clang understands that we are
          // truncating a vector of <4 x i64> to a vector of <4 x i32>. With
          // castsi256_si128, it generates a bunch of shuffles (which are still
          // semantically equivalent). Nevertheless, with only this code, we see
          // that the codegen in the end is the same.
          //
          // But interesting optimizations can then occur on more complex code,
          // like this one: https://godbolt.org/z/45sor8Ta1. In this case, we are
          // truncating and then zero-extending our vector, which can be optimized
          // as a simple mask operation (only keeping the low 32 bits of each
          // 64-bit packed number). By looking at the generated LLVM IR, we can see
          // that LLVM successfully manages to understand & optimize this if we use
          // extractf128, whereas it is not the case with castsi256_si128! The
          // codegen also looks far better, and only use 1-latency cycle
          // instructions.
          return _mm256_extractf128_si256(p, 0);
    #else
          return _mm256_castsi256_si128(p);
    #endif
        }
        else return wide<U, N>(convert(v.slice(lower_),tgt),convert(v.slice(upper_),tgt));
      }
      else  if constexpr( match ( c_o , category::int16x8, category::uint16x8
                                      , category::int8x16, category::uint8x16
                                )
                        )
      {
        // *int16 go through to *int32
        // *int8  go through to *int16 then *int32
        return convert( convert(v, as<upgrade_t<U>>{}), tgt);
      }
      else return convert_impl(EVE_RETARGET(cpu_),v,tgt);
    }
    else  if constexpr( match(c_i, category::int64x8, category::uint64x8))
    {
            if constexpr(c_o == category::float64x8 )
      {
        if constexpr(c_i == category::int64x8)  return _mm512_cvtepi64_pd(v);
        else                                    return _mm512_cvtepu64_pd(v);
      }
      else  if constexpr(c_o == category::float32x8)
      {
        if constexpr(c_i == category::int64x8)  return _mm512_cvtepi64_ps(v);
        else                                    return _mm512_cvtepu64_ps(v);
      }
      else  if constexpr(c_o == category::int32x8   ) return _mm512_cvtepi64_epi32(v);
      else  if constexpr(c_o == category::uint32x8  ) return _mm512_cvtepi64_epi32(v);
      else  if constexpr(c_o == category::int16x8   ) return _mm512_cvtepi64_epi16(v);
      else  if constexpr(c_o == category::uint16x8  ) return _mm512_cvtepi64_epi16(v);
      else  if constexpr(c_o == category::int8x16   ) return _mm512_cvtepi64_epi8(v);
      else  if constexpr(c_o == category::uint8x16  ) return _mm512_cvtepi64_epi8(v);
    }
    else
    {
      // Help compilers with (int64x2)*N to int8x(2*N) by forcing passage through int16
      if((sizeof(U) == 1) && (N::value >= 4) )
      {
        return convert( convert(v, as<upgrade_t<U>>{}), tgt);
      }
      else return convert_impl(EVE_RETARGET(cpu_),v,tgt);
    }
  }

  //================================================================================================
  // convert: (u)int32 -> U
  //================================================================================================
  template<integral_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N>  convert_impl( EVE_SUPPORTS(sse2_)
                                          , wide<T, N> const& v, as<U> const &tgt
                                          ) noexcept
  requires (sizeof(T) == 4)
  {
    constexpr auto c_i      = categorize<wide<T, N>>();
    constexpr auto c_o      = categorize<wide<U, N>>();
    constexpr bool api_512  = current_api >= avx512;
    constexpr bool api_sse4 = current_api >= sse4_1;

    if constexpr( match(c_i, category::int32x4, category::uint32x4))
    {
            if constexpr(c_o == category::float32x4)
      {
        if constexpr(c_i == category::int32x4) return _mm_cvtepi32_ps(v);
        else
        {
          // From https://stackoverflow.com/a/40766669/737268
          // Convert u32 to float by converting half the value and reconstructing it
          __m128i v2 = _mm_srli_epi32(v, 1);
          __m128i v1 = _mm_and_si128(v, _mm_set1_epi32(1));
          return _mm_add_ps ( _mm_add_ps(_mm_cvtepi32_ps(v2), _mm_cvtepi32_ps(v2))
                            , _mm_cvtepi32_ps(v1)
                            );
        }
      }
      else  if constexpr(c_o == category::float64x2)
      {
        if constexpr(c_i == category::int32x4) return _mm_cvtepi32_pd(v);
        else
        {
          // From https://stackoverflow.com/a/40766669/737268 - Adapted for float64
          __m128i v2 = _mm_srli_epi32(v, 1);
          __m128i v1 = _mm_and_si128(v, _mm_set1_epi32(1));
          return _mm_add_pd ( _mm_add_pd(_mm_cvtepi32_pd(v2), _mm_cvtepi32_pd(v2))
                            , _mm_cvtepi32_pd(v1)
                            );
        }
      }
      else  if constexpr(match(c_o, category::int64x2, category::uint64x2))
      {
              if constexpr( api_sse4 && c_i == category::int32x4)   return _mm_cvtepi32_epi64(v);
        else  if constexpr( api_sse4 && c_i == category::uint32x4)  return _mm_cvtepu32_epi64(v);
        else
        {
          return _mm_unpacklo_epi32(v, sign_extend(v));
        }
      }
      else  if constexpr(match(c_o, category::int16x8, category::uint16x8))
      {
        if constexpr( api_512 ) return _mm_cvtepi32_epi16(v);
        else                    return map(convert,v,tgt);
      }
      else  if constexpr(match(c_o, category::int8x16, category::uint8x16))
      {
        if constexpr( api_512 ) return _mm_cvtepi32_epi8(v);
        else                    return convert(convert(v, as<upgrade_t<U>>{}), tgt);
      }
      else
      {
              if constexpr( c_o == category::float64x4 )
        {
                if constexpr( c_i == category::int32x4)             return _mm256_cvtepi32_pd(v);
          else  if constexpr( api_512 && c_i == category::uint32x4) return _mm256_cvtepu32_pd(v);
          else  return wide<U,N>(convert(v.slice(lower_),tgt), convert(v.slice(upper_),tgt));
        }
        else  if constexpr(   current_api >= avx2
                          &&  match(c_o, category::int64x4, category::uint64x4)
                          )
        {
                if constexpr( c_i == category::int32x4)   return _mm256_cvtepi32_epi64(v);
          else  if constexpr( c_i == category::uint32x4)  return _mm256_cvtepu32_epi64(v);
        }
        else  if constexpr((sizeof(U) == 8) && (N::value == 4) )
        {
          return wide<U,N>(convert(v.slice(lower_),tgt), convert(v.slice(upper_),tgt));
        }
        else return convert_impl(EVE_RETARGET(cpu_),v,tgt);
      }
    }
    else if constexpr( match(c_i, category::int32x8, category::uint32x8))
    {
      if constexpr(c_o == category::float32x8 )
      {
              if constexpr( c_i == category::int32x8)   return _mm256_cvtepi32_ps(v);
        else  return wide<U, N>(convert(v.slice(lower_),tgt),convert(v.slice(upper_),tgt));
      }
      else if constexpr( match(c_o, category::int16x8, category::uint16x8) )
      {
        if constexpr( api_512  ) return _mm256_cvtepi32_epi16(v);
        else           return wide<U, N>(convert(v.slice(lower_),tgt),convert(v.slice(upper_),tgt));
      }
      else if constexpr( api_512 && match(c_o, category::int8x16, category::uint8x16) )
      {
        return _mm256_cvtepi32_epi8(v);
      }
      else
      {
        return wide<U, N>(convert(v.slice(lower_),tgt),convert(v.slice(upper_),tgt));
      }
    }
    else if constexpr( match(c_i, category::int32x16, category::uint32x16))
    {
      if constexpr(c_o == category::float32x16 )
      {
              if constexpr( c_i == category::int32x16)   return _mm512_cvtepi32_ps(v);
        else  if constexpr( c_i == category::uint32x16)  return _mm512_cvtepu32_ps(v);
      }
      else  if constexpr(match(c_o, category::int16x16, category::uint16x16))
      {
        return _mm512_cvtepi32_epi16(v);
      }
      else if constexpr(match(c_o, category::int8x16, category::uint8x16))
      {
        return _mm512_cvtepi32_epi8(v);
      }
      else
      {
        return wide<U, N>(convert(v.slice(lower_),tgt),convert(v.slice(upper_),tgt));
      }
    }
    else
    {
      return convert_impl(EVE_RETARGET(cpu_),v,tgt);
    }
  }

  //================================================================================================
  // convert: (u)int16 -> U
  //================================================================================================
  template<integral_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N>  convert_impl( EVE_SUPPORTS(sse2_)
                                          , wide<T, N> const& v, as<U> const &tgt
                                          ) noexcept
  requires (sizeof(T) == 2)
  {
    constexpr auto c_i      = categorize<wide<T, N>>();
    constexpr auto c_o      = categorize<wide<U, N>>();
    constexpr auto api_512  = current_api >= avx512;
    constexpr auto api_avx2 = current_api >= avx2;
    constexpr auto api_41   = current_api >= sse4_1;

    if constexpr( match(c_i, category::int16x8, category::uint16x8) )
    {
            if constexpr(match(c_o, category::int8x16, category::uint8x16))
      {
        if constexpr(api_512) return _mm_cvtepi16_epi8(v);
        else return map(convert,v,tgt);
      }
      else  if constexpr(match(c_o, category::int32x4, category::uint32x4))
      {
        if constexpr(api_41)
        {
          if constexpr( std::is_signed_v<T> ) return _mm_cvtepi16_epi32(v);
          else                                return _mm_cvtepu16_epi32(v);
        }
        else
        {
          return _mm_unpacklo_epi16(v, sign_extend(v));
        }
      }
      else  if constexpr(api_41 && match(c_o, category::int64x2, category::uint64x2))
      {
        if constexpr( std::is_signed_v<T> ) return _mm_cvtepi16_epi64(v);
        else                                return _mm_cvtepu16_epi64(v);
      }
      else  if constexpr(api_512 && c_o == category::float64x8)
      {
        if constexpr( std::is_signed_v<T> ) return _mm512_cvtepi64_pd(_mm512_cvtepi16_epi64(v));
        else                                return _mm512_cvtepi64_pd(_mm512_cvtepu16_epi64(v));
      }
      else  if constexpr(c_o == category::float32x4)
      {
        // Adapted from https://stackoverflow.com/a/9161855/737268
        return _mm_cvtepi32_ps(_mm_unpacklo_epi16(v, sign_extend(v)));
      }
      else  if constexpr(c_o == category::float32x8)
      {
        // Adapted from https://stackoverflow.com/a/9161855/737268
        auto const m = sign_extend(v);
        return eve::combine ( wide<U,fixed<4>>{_mm_cvtepi32_ps(_mm_unpacklo_epi16(v, m))}
                            , wide<U,fixed<4>>{_mm_cvtepi32_ps(_mm_unpackhi_epi16(v, m))}
                            );
      }
      else  if constexpr(c_o && category::float_)
      {
        return convert( convert(v, as<upgrade_t<T>>{}), tgt);
      }
      else  if constexpr( api_512 && match(c_o, category::int64x8, category::uint64x8))
      {
        if constexpr( std::is_signed_v<T> ) return _mm512_cvtepi16_epi64(v);
        else                                return _mm512_cvtepu16_epi64(v);
      }
      else  if constexpr(api_avx2 && match(c_o, category::int64x4, category::uint64x4))
      {
        if constexpr(c_i == category::int16x8)  return _mm256_cvtepi16_epi64(v);
        else                                    return _mm256_cvtepu16_epi64(v);
      }
      else  if constexpr(api_avx2 && match(c_o, category::int32x8, category::uint32x8))
      {
        if constexpr(c_i == category::int16x8)  return _mm256_cvtepi16_epi32(v);
        else                                    return _mm256_cvtepu16_epi32(v);
      }
      else  if constexpr((sizeof(U) == 8) && N::value == 4)
      {
        return convert(convert(v,as<upgrade_t<T>>{}), tgt);
      }
      else  if constexpr((sizeof(U) >= 4) && N::value == 8)
      {
        return wide<U,N>(convert(v.slice(lower_), tgt), convert(v.slice(upper_), tgt));
      }
      else return convert_impl(EVE_RETARGET(cpu_),v,tgt);
    }
    else if constexpr( match(c_i, category::int16x16, category::uint16x16) )
    {
       if constexpr( match(c_o,category::int8x16, category::uint8x16) )
      {
        if constexpr(api_512)
        {
          return _mm256_cvtepi16_epi8(v);
        }
        else return wide<U, N>(eve::convert(v.slice(lower_),tgt),eve::convert(v.slice(upper_),tgt));
      }
      else if constexpr(match(c_o, category::int32x16, category::uint32x16))
      {
        if constexpr(c_i == category::int16x16) return _mm512_cvtepi16_epi32(v);
        else                                    return _mm512_cvtepu16_epi32(v);
      }
      else if constexpr(c_o && category::float_)
      {
        return convert( convert(v,as<upgrade_t<T>>{}), tgt);
      }
      else
      {
        auto const w = [](auto x)
        {
          if constexpr(sizeof(U) == 1)  return x & wide<T, N> {0xff}; else return x;
        }(v);
        return wide<U, N>(eve::convert(w.slice(lower_),tgt),eve::convert(w.slice(upper_),tgt));
      }
    }
    else if constexpr( match(c_i, category::int16x32, category::uint16x32) )
    {
      if constexpr(match(c_o, category::int8x32, category::uint8x32))
      {
        return _mm512_cvtepi16_epi8(v);
      }
      else
      {
        return wide<U, N>(eve::convert(v.slice(lower_),tgt),eve::convert(v.slice(upper_),tgt));
      }
    }
    else
    {
      return convert_impl(EVE_RETARGET(cpu_),v,tgt);
    }
  }

  //================================================================================================
  // convert: (u)int8 -> U
  //================================================================================================
  template<integral_scalar_value T, typename N, real_scalar_value U>
  EVE_FORCEINLINE wide<U, N>  convert_impl( EVE_SUPPORTS(sse2_)
                                          , wide<T, N> const& v, as<U> const &tgt
                                          ) noexcept
  requires (sizeof(T) == 1)
  {
    constexpr auto c_i      = categorize<wide<T, N>>();
    constexpr auto c_o      = categorize<wide<U, N>>();
    constexpr auto api_avx2 = current_api >= avx2;
    constexpr auto api_41   = current_api >= sse4_1;

          if constexpr( match(c_i, category::int8x16, category::uint8x16))
    {
            if constexpr(match(c_o, category::int16x8, category::uint16x8))
      {
              if constexpr(api_41 && c_i == category::int8x16)  return _mm_cvtepi8_epi16(v);
        else  if constexpr(api_41 && c_i == category::uint8x16) return _mm_cvtepu8_epi16(v);
        else  return _mm_unpacklo_epi8(v, sign_extend(v));
      }
      else  if constexpr(match(c_o, category::int16x16, category::uint16x16))
      {
              if constexpr(api_avx2 && c_i == category::int8x16 ) return _mm256_cvtepi8_epi16(v);
        else  if constexpr(api_avx2 && c_i == category::uint8x16) return _mm256_cvtepu8_epi16(v);
        else return wide<U,N>(convert(v.slice(lower_), tgt), convert(v.slice(upper_), tgt));
      }
      else  if constexpr(match(c_o, category::int32x4, category::uint32x4))
      {
              if constexpr(api_avx2)  return convert(eve::combine(v,v),tgt).slice(lower_);
        else  if constexpr(api_41 && c_i == category::int8x16)  return _mm_cvtepi8_epi32(v);
        else  if constexpr(api_41 && c_i == category::uint8x16) return _mm_cvtepu8_epi32(v);
        else                          return convert( convert(v, as<upgrade_t<T>>{}), tgt);
      }
      else  if constexpr(match(c_o, category::int32x8, category::uint32x8))
      {
              if constexpr(api_avx2 && c_i == category::int8x16 ) return _mm256_cvtepi8_epi32(v);
        else  if constexpr(api_avx2 && c_i == category::uint8x16) return _mm256_cvtepu8_epi32(v);
        else return wide<U,N>(convert(v.slice(lower_), tgt), convert(v.slice(upper_), tgt));
      }
      else  if constexpr(match(c_o, category::int32x16, category::uint32x16))
      {
              if constexpr(c_i == category::int8x16 ) return _mm512_cvtepi8_epi32(v);
        else  if constexpr(c_i == category::uint8x16) return _mm512_cvtepu8_epi32(v);
      }
      else  if constexpr(match(c_o, category::int64x2, category::uint64x2))
      {
              if constexpr(api_41 && c_i == category::int8x16) return _mm_cvtepi8_epi64(v);
        else  if constexpr(api_41 && c_i == category::uint8x16) return _mm_cvtepu8_epi64(v);
        else                  return convert( convert(v, as<downgrade_t<U>>{}), tgt);
      }
      else  if constexpr(match(c_o, category::int64x4, category::uint64x4))
      {
              if constexpr(api_avx2 && c_i == category::int8x16 ) return _mm256_cvtepi8_epi64(v);
        else  if constexpr(api_avx2 && c_i == category::uint8x16) return _mm256_cvtepu8_epi64(v);
        else                              return convert( convert(v, as<downgrade_t<U>>{}), tgt);
      }
      else  if constexpr(match(c_o, category::int64x8, category::uint64x8))
      {
              if constexpr(c_i == category::int8x16 ) return _mm512_cvtepi8_epi64(v);
        else  if constexpr(c_i == category::uint8x16) return _mm512_cvtepu8_epi64(v);
      }
      else  if constexpr(c_o && category::float_)
      {
        using t_t = std::conditional_t< std::is_signed_v<T>
                                      , as_integer_t<U,signed>, as_integer_t<U,unsigned>
                                      >;
        return convert(convert(v, as<t_t>{}), tgt);
      }
      else
      {
        if constexpr( sizeof(U) == 2  && N::value >= 8)
        {
          return wide<U,N>(convert(v.slice(lower_), tgt), convert(v.slice(upper_), tgt));
        }
        else if constexpr( sizeof(U) == 4  && N::value >= 4)
        {
          return wide<U,N>(convert(v.slice(lower_), tgt), convert(v.slice(upper_), tgt));
        }
        else if constexpr( sizeof(U) == 8  && N::value >= 2)
        {
          return wide<U,N>(convert(v.slice(lower_), tgt), convert(v.slice(upper_), tgt));
        }
        else return convert_impl(EVE_RETARGET(cpu_),v,tgt);
      }
    }
    else
    {
      return wide<U,N>(convert(v.slice(lower_), tgt), convert(v.slice(upper_), tgt));
    }
  }
}
