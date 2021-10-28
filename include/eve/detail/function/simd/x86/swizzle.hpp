//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/function/simd/common/swizzle_helpers.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/traits/as_floating_point.hpp>
#include <eve/traits/as_integer.hpp>
#include <eve/forward.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  //================================================================================================
  // shuffle requires cross-api re-targeting (ie AVX512 128bits calling back SSSE3)
  // so instead of our classical one-size-fit-all overloads, we need to split it into
  // API supports overloads
  //================================================================================================

  //================================================================================================
  // Unary swizzle - logical on AVX512 ABI, call general case on others
  //================================================================================================
  template<typename T, typename N, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto basic_swizzle_ ( EVE_SUPPORTS(sse2_)
                                      , logical<wide<T,N>> const& v, Pattern p
                                      ) noexcept
      requires x86_abi<abi_t<T, N>>
  {
    if constexpr( current_api >= avx512 ) return to_logical((v.mask())[p]);
    else                                  return basic_swizzle_(EVE_RETARGET(cpu_),v,p);
  }

  //================================================================================================
  // Check a pattern fits the half-lane rules for x86 pseudo-shuffle
  //================================================================================================
  template<std::ptrdiff_t... I>
  consteval bool is_x86_shuffle_compatible(pattern_t<I...> p)
  {
    constexpr std::ptrdiff_t c  = sizeof...(I);
    std::ptrdiff_t idx[c];

    for(int i=0;i<c  ;++i)  idx[i] = p(i,c);
    for(int i=0;i<c/2;++i)  if(idx[i] >= c/2)                   return false;
    for(int i=c/2;i<c;++i)  if(idx[i] <  c/2 && idx[i] != na_)  return false;

    return true;
  }

  //================================================================================================
  // SSE2-SSSE3 variant
  //================================================================================================
  template<typename T, typename N, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto basic_swizzle_( EVE_SUPPORTS(sse2_), wide<T, N> const& v, Pattern const&)
    requires std::same_as<abi_t<T, N>, x86_128_>
  {
    constexpr auto sz = Pattern::size();
    using that_t      = as_wide_t<wide<T, N>, fixed<sz>>;

    constexpr Pattern q = {};

    // We're swizzling so much we aggregate the output
    if constexpr( has_aggregated_abi_v<that_t> )
    {
      return aggregate_swizzle(v,q);
    }
    else if constexpr(sizeof(T) == 8)
    {
      using f_t         = as_floating_point_t<that_t>;
      auto const vv     = bit_cast(v,as<f_t>{});
      constexpr auto m  = _MM_SHUFFLE2(q(1,2)&1, q(0,2)&1);
      return bit_cast(process_zeros(f_t{_mm_shuffle_pd(vv,vv,m)},q),as<that_t>{});
    }
    else if constexpr( current_api >= ssse3 )
    {
      using st_t    = typename that_t::storage_type;
      using bytes_t = typename that_t::template rebind<std::uint8_t,fixed<16>>;
      using i_t     = as_integer_t<wide<T, N>>;

      return that_t ( (st_t)_mm_shuffle_epi8( bit_cast(v,as<i_t>{}).storage()
                                            , as_bytes<that_t>(q,as<bytes_t>())
                                            )
                    );
    }
    else
    {
      if constexpr(sizeof(T) == 4)
      {
        constexpr auto m  = _MM_SHUFFLE(q(3,4)&3, q(2,4)&3, q(1,4)&3, q(0,4)&3);
        if constexpr( std::same_as<T,float> ) return process_zeros(that_t{_mm_shuffle_ps(v,v,m)} ,q);
        else                                  return process_zeros(that_t{_mm_shuffle_epi32(v,m)},q);
      }
      else if constexpr(sizeof(T) == 2)
      {
        if constexpr( (sz < 8) && q.strictly_under(4) )
        {
          constexpr auto m  = _MM_SHUFFLE(q(3,4)&3, q(2,4)&3, q(1,4)&3, q(0,4)&3);
          return process_zeros(that_t{_mm_shufflelo_epi16(v,m)},q);
        }
        else if constexpr( (sz < 8) && q.over(4) )
        {
          constexpr auto m  = _MM_SHUFFLE(q(3,4)&3, q(2,4)&3, q(1,4)&3, q(0,4)&3);
          return process_zeros(that_t{_mm_bsrli_si128(_mm_shufflehi_epi16(v,m),8)},q);
        }
        else
        {
          constexpr auto lp = pattern_view<0,4,8>(q);
          constexpr auto hp = pattern_view<4,8,8>(q);

                if constexpr( lp.strictly_under(4) && hp.over(4))
                return process_zeros(that_t{v[lp],v[hp]},q);
          else  if constexpr( hp.strictly_under(4) && lp.over(4))
                return process_zeros(that_t{v[lp],v[hp]},q);
          else  return basic_swizzle_(EVE_RETARGET(cpu_),v,q);
        }
      }
      else
      {
        return basic_swizzle_(EVE_RETARGET(cpu_),v,q);
      }
    }
  }

  //================================================================================================
  // AVX+ variant
  //================================================================================================
  template<typename T, typename N, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto basic_swizzle_( EVE_SUPPORTS(avx_), wide<T,N> const& v, Pattern const&)
      requires x86_abi<abi_t<T, N>>
  {
    constexpr auto cd = N::value;
    constexpr auto sz = Pattern::size();
    using that_t      = as_wide_t<wide<T,N>,fixed<sz>>;

    constexpr auto width_in   = cd*sizeof(T);
    constexpr auto width_out  = sz*sizeof(T);

    constexpr Pattern q = {};

    // We're swizzling so much we aggregate the output
    if constexpr( has_aggregated_abi_v<that_t> )
    {
      return aggregate_swizzle(v,q);
    }
    else if constexpr( width_in == 64 )
    {
      /// TODO: AVX512VBMI supports 128-bits permutexvar
      if constexpr(width_out <= 16)       return basic_swizzle_(EVE_RETARGET(cpu_),v,q);
      else if constexpr(width_out == 32)
      {
              if constexpr( q.strictly_under(cd/2) )  return v.slice(lower_)[q];
        else  if constexpr( q.over(cd/2) )            return v.slice(upper_)[slide_pattern<cd/2,sz>(q)];
        /// TODO: optimize using SSSE3 + binary shuffle
        else                             return basic_swizzle_(EVE_RETARGET(cpu_),v,q);
      }
      else
      {
        constexpr auto c = categorize<that_t>();
        auto const     m = as_indexes<that_t>(q);
        that_t s;

              if constexpr(c == category::float64x8 )                       s = _mm512_permutexvar_pd(m,v);
        else  if constexpr(c == category::float32x16)                       s = _mm512_permutexvar_ps(m,v);
        else  if constexpr(match(c,category::int32x16,category::uint32x16)) s = _mm512_permutexvar_epi32(m,v);
        else  if constexpr(match(c,category::int16x32,category::uint16x32)) s = _mm512_permutexvar_epi16(m,v);
        else  return basic_swizzle_(EVE_RETARGET(cpu_),v,q);

        return process_zeros(s,q);
      }
    }
    else if constexpr( width_in == 32 )
    {
      if constexpr(width_out <= 16)
      {
              if constexpr( q.strictly_under(cd/2) )  return v.slice(lower_)[ q ];
        else  if constexpr( q.over(cd/2) )            return v.slice(upper_)[ slide_pattern<cd/2,sz>(q) ];
        /// TODO: optimize using SSSE3 + binary shuffle
        else                              return basic_swizzle_(EVE_RETARGET(cpu_),v,q);
      }
      else
      {
        if constexpr(current_api >= avx512)
        {
          constexpr auto c = categorize<that_t>();
          auto const     m = as_indexes<that_t>(q);
          that_t s;

          if constexpr(match(c,category::int64x4 ,category::uint64x4) )
          {
            auto vc = bit_cast(v, as<as_floating_point_t<that_t>>{});
            return bit_cast( basic_swizzle(vc, q) , as(s));
          }
          else  if constexpr(match(c,category::int32x8 ,category::uint32x8) ) s = _mm256_permutexvar_epi32(m,v);
          else  if constexpr(match(c,category::int16x16,category::uint16x16)) s = _mm256_permutexvar_epi16(m,v);
          else  if constexpr(match(c,category::int8x32 ,category::uint8x32) )
          {
            if constexpr(supports_avx512vbmi_)                                s = _mm256_permutexvar_epi8(m,v);
            else  return basic_swizzle_(EVE_RETARGET(cpu_),v,q);
          }
          else  if constexpr(c == category::float64x4 )                       s = _mm256_permutexvar_pd(m,v);
          else  if constexpr(c == category::float32x8 )                       s = _mm256_permutexvar_ps(m,v);

          return process_zeros(s,q);
        }
        else if constexpr(current_api >= avx2)
        {
          if constexpr(sizeof(T) == 8)
          {
            constexpr auto m = _MM_SHUFFLE(q(3,4)&3,q(2,4)&3,q(1,4)&3,q(0,4)&3);

            if constexpr(std::same_as<T,double>)
              return process_zeros(that_t{ _mm256_permute4x64_pd(v, m) },q);
            else
              return process_zeros(that_t{ _mm256_permute4x64_epi64(v, m) },q);
          }
          else if constexpr(sizeof(T) == 4)
          {
            auto m = as_indexes<wide<T,N>>(q);

            if constexpr(std::same_as<T,float>)
              return process_zeros(that_t{ _mm256_permutevar8x32_ps(v, m) },q);
            else
              return process_zeros(that_t{ _mm256_permutevar8x32_epi32(v, m) },q);
          }
          else
          {
            /// TODO: optimize sub 32-bits using SSSE3 + binary shuffle
            return basic_swizzle_(EVE_RETARGET(cpu_),v,q);
          }
        }
        else
        {
          using f_t     = as_floating_point_t<wide<T,N>>;

          if constexpr(sizeof(T) == 8 && is_x86_shuffle_compatible(q) )
          {
            auto const vv     = bit_cast(v,as<f_t>{});

            //======================================================================================
            // Fix the pattern to fit the non-obvious control mask for _mm256_permutevar_pd
            // which read bits 1/65/129/193 instead of the obvious 0/64/128/192
            //======================================================================================
            constexpr auto fixed_pattern = fix_pattern<N::value>
            (
              [](auto i, auto c) { Pattern r; return (i<c/2 ? r(i,c) : r(i-c/2,c)) << 1; }
            );

            auto const m  = as_indexes<wide<T,N>>(fixed_pattern);
            return bit_cast(process_zeros(f_t{_mm256_permutevar_pd(vv,m)},q),as(v));
          }
          else if constexpr(sizeof(T) == 4 && is_x86_shuffle_compatible(q) )
          {
            auto const vv = bit_cast(v,as<f_t>{});
            auto const m  = as_indexes<wide<T,N>>(q);
            return bit_cast(process_zeros(f_t{_mm256_permutevar_ps(vv,m)},q),as(v));
          }
          else
          {
            /// TODO: optimize sub 32-bits using SSSE3 + shuffle
            return basic_swizzle_(EVE_RETARGET(cpu_),v,q);
          }
        }
      }
    }
    else if constexpr( width_in <= 16 )
    {
      return basic_swizzle_(EVE_RETARGET(sse2_), v, q);
    }
  }
}
