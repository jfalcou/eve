//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/product_type.hpp>

namespace eve::detail
{
  //================================================================================================
  // Interleave pairs of wides
  //================================================================================================
  template<scalar_value T, typename N>
  EVE_FORCEINLINE auto interleave_(EVE_SUPPORTS(sse2_), wide<T,N> v0, wide<T,N> v1) noexcept
  requires (N::value > 1) && x86_abi<abi_t<T,N>>
  {
    using type = wide<T,N>;
    constexpr auto c = categorize<type>();

    if constexpr( c == category::float64x2 )
    {
      return kumi::make_tuple(type(_mm_unpacklo_pd(v0, v1)),type(_mm_unpackhi_pd(v0, v1)));
    }
    else if constexpr( match(c,category::int64x2, category::uint64x2) )
    {
      return kumi::make_tuple(type(_mm_unpacklo_epi64(v0,v1)), type(_mm_unpackhi_epi64(v0,v1)));
    }
    else if constexpr( c == category::float64x4 )
    {
      auto[a0,a1] = v0.slice();
      auto[b0,b1] = v1.slice();
      auto[x0,x1] = eve::interleave(a0,b0);
      auto[y0,y1] = eve::interleave(a1,b1);

      return kumi::make_tuple(type(x0,x1), type(y0,y1));
    }
    else if constexpr( c == category::float32x4 )
    {
      if constexpr(N::value == 2)
      {
        auto xy = _mm_shuffle_ps(v0,v1,0b10011001);
        return kumi::make_tuple ( type(_mm_unpacklo_ps(v0,v1))
                                , type(_mm_shuffle_ps(xy,xy,0b11011000))
                                );
      }
      else if constexpr(N::value == 4)
      {
        return kumi::make_tuple(type(_mm_unpacklo_ps(v0,v1)), type(_mm_unpackhi_ps(v0,v1)));
      }
    }
    else if constexpr( match(c,category::int32x4, category::uint32x4) )
    {
      if constexpr(N::value == 2)
      {
        using  ftype = as<wide< as_floating_point_t<T>,N>>;
        auto that = interleave(bit_cast(v0,ftype()),bit_cast(v1,ftype()));
        return kumi::map( [](auto m){ return bit_cast(m,as<type>()); }, that);
      }
      else if constexpr(N::value == 4)
      {
        return kumi::make_tuple(type(_mm_unpacklo_epi32(v0,v1)), type(_mm_unpackhi_epi32(v0,v1)));
      }
    }
    else if constexpr( c == category::float32x8 )
    {
      auto[a0,a1] = v0.slice();
      auto[b0,b1] = v1.slice();
      auto[x0,x1] = eve::interleave(a0,b0);
      auto[y0,y1] = eve::interleave(a1,b1);

      return kumi::make_tuple(type(x0,x1), type(y0,y1));
    }
    else if constexpr( match(c,category::int16x8, category::uint16x8) )
    {
      if constexpr(N::value == 8)
      {
        return kumi::make_tuple(type(_mm_unpacklo_epi16(v0,v1)), type(_mm_unpackhi_epi16(v0,v1)));
      }
      else
      {
        wide<T,fixed<8>> v01 = _mm_unpacklo_epi16(v0.storage(),v1.storage());
        if constexpr(N::value == 2 )
        {
          auto[l,h] = v01.slice(lower_).slice();
          return kumi::make_tuple(l,h);
        }
        else if constexpr(N::value == 4)
        {
          auto[l,h] = v01.slice();
          return kumi::make_tuple(l,h);
        }
      }
    }
    else if constexpr( match(c,category::int8x16, category::uint8x16) )
    {
      if constexpr(N::value == 16)
      {
        return kumi::make_tuple(type(_mm_unpacklo_epi8(v0,v1)), type(_mm_unpackhi_epi8(v0,v1)));
      }
      else
      {
        wide<T,fixed<16>> v01 = _mm_unpacklo_epi8(v0.storage(),v1.storage());

        if constexpr(N::value == 2)
        {
          auto[l,h] = v01.slice(lower_).slice(lower_).slice();
          return kumi::make_tuple(l,h);
        }
        else if constexpr(N::value == 4)
        {
          auto[l,h] = v01.slice(lower_).slice();
          return kumi::make_tuple(l,h);
        }
        else if constexpr(N::value == 8)
        {
          auto[l,h] = v01.slice();
          return kumi::make_tuple(l,h);
        }
      }
    }
    else if constexpr( match(c,category::int8x16, category::uint8x16) )
    {
      if constexpr (N() == 16) return kumi::make_tuple(type(_mm_unpacklo_epi8(v0, v1)), type(_mm_unpackhi_epi8(v0, v1)));
      else
      {
        type combined = _mm_unpacklo_epi8(v0, v1);
        auto [lo, hi] = combined.slice();
        return kumi::make_tuple(eve::bit_cast(lo, eve::as(v0)), eve::bit_cast(lo, eve::as(v1)));
      }
    }
    else if constexpr ( match(c,category::int8x32,  category::uint8x32,
                                category::int16x16, category::uint16x16)
                        && current_api >= avx2 )
    {
      type ul_lanes = sizeof(T) == 2 ? _mm256_unpacklo_epi16(v0, v1) : _mm256_unpacklo_epi8(v0, v1);
      type uh_lanes = sizeof(T) == 2 ? _mm256_unpackhi_epi16(v0, v1) : _mm256_unpackhi_epi8(v0, v1);
      type ul       = _mm256_permute2f128_si256(ul_lanes, uh_lanes, 0x20);
      type uh       = _mm256_permute2f128_si256(ul_lanes, uh_lanes, 0x31);
      return kumi::make_tuple(ul, uh);
    }
    else if constexpr ( match(c, category::int8x32, category::uint8x32) )
    {
      auto [a0, a1] = v0.slice();
      auto [b0, b1] = v1.slice();
      auto [ab00, ab01] = interleave(a0, b0);
      auto [ab10, ab11] = interleave(a1, b1);
      return kumi::make_tuple(type(ab00, ab01), type(ab10, ab11));
    }
    else if constexpr ( match(c, category::int8x64, category::uint8x64) )
    {
      type ul_lanes = _mm512_unpacklo_epi8(v0, v1);
      type uh_lanes = _mm512_unpackhi_epi8(v0, v1);

      // Can't use shuffle_i32x4, only applies within lanes
      using idx_t = typename type::template rebind<std::uint64_t, fixed<8>>;
      idx_t lo_idx { 0, 1,  8,  9, 2, 3, 10, 11 };
      idx_t hi_idx { 4, 5, 12, 13, 6, 7, 14, 15 };

      type ul = _mm512_permutex2var_epi64(ul_lanes, lo_idx, uh_lanes);
      type uh = _mm512_permutex2var_epi64(ul_lanes, hi_idx, uh_lanes);
      return kumi::make_tuple(ul, uh);
    }
    else
    {
      return interleave_(EVE_RETARGET(cpu_),v0,v1);
    }
  }

  template<scalar_value T, typename N>
  EVE_FORCEINLINE auto interleave_( EVE_SUPPORTS(sse2_)
                                  , logical<wide<T,N>> v0, logical<wide<T,N>> v1
                                  ) noexcept
  requires (N::value > 1) && x86_abi<abi_t<T,N>>
  {
    if constexpr( !abi_t<T,N>::is_wide_logical )
    {
      using s_t = typename logical<wide<T,N>>::storage_type;
      using v_t = typename s_t::type;

      auto deposit_low = [](auto v)
      {
        if constexpr(sizeof(v) <= 4)  return _pdep_u32(v,0x55555555UL);
        else                          return _pdep_u64(v,0x5555555555555555ULL);
      };

      auto deposit_high = [](auto v)
      {
        if constexpr(sizeof(v) <= 4)  return _pdep_u32(v,0xAAAAAAAAUL);
        else                          return _pdep_u64(v,0xAAAAAAAAAAAAAAAAULL);
      };

      auto x = v0.storage().value;
      auto y = v1.storage().value;

      auto lx = deposit_low (x);
      auto ly = deposit_high(y);
      auto l  = s_t{v_t(lx | ly)};

      constexpr auto offset = N::value/2;
      auto hx = deposit_low (v_t(x >> offset));
      auto hy = deposit_high(v_t(y >> offset));
      auto h  = s_t{v_t(hx | hy)};

      return kumi::make_tuple(logical<wide<T,N>>(l),logical<wide<T,N>>(h));
    }
    else
    {
      return interleave_( EVE_RETARGET(cpu_),v0,v1);
    }
  }

  //================================================================================================
  // Interleave triplets of wides
  //================================================================================================
  template<scalar_value T, typename N>
  EVE_FORCEINLINE auto interleave_( EVE_SUPPORTS(sse2_)
                                  , wide<T,N> v0, wide<T,N> v1, wide<T,N> v2
                                  ) noexcept
  requires (N::value > 1) && x86_abi<abi_t<T,N>>
  {
    using type = wide<T,N>;
    constexpr auto c = categorize<type>();

    if constexpr( c == category::float32x4 )
    {
      if constexpr(N::value == 2)
      {
        return interleave_(EVE_RETARGET(cpu_),v0,v1,v2);
      }
      else if constexpr(N::value == 4)
      {
        type xy = _mm_unpacklo_ps(v0,v1);
        type xz = _mm_shuffle_ps(v0,v2,197);

        xy = _mm_shuffle_ps(xy,xz,36);
        xz = _mm_shuffle_ps(v2,v1,17);

        auto dy   = eve::bit_cast(v1, eve::as<wide<double,fixed<2>>>());
             dy   = _mm_unpackhi_pd(dy,eve::bit_cast(v0, eve::as<wide<double,fixed<2>>>()));
        auto yyx  = eve::bit_cast(dy, eve::as<type>());

        xz  = _mm_shuffle_ps(xz,yyx, 34);
        v0  = _mm_shuffle_ps(v0, v2, 35);
        v2  = _mm_shuffle_ps(v2, v1,255);
        v0  = _mm_shuffle_ps(v0, v2, 34);

        return kumi::make_tuple(xy,xz,v0);
      }
    }
    else if constexpr( match(c,category::int32x4, category::uint32x4) )
    {
      using  ftype = as<wide< as_floating_point_t<T>,N>>;
      auto that = interleave(bit_cast(v0,ftype()),bit_cast(v1,ftype()),bit_cast(v2,ftype()));
      return kumi::map( [](auto m){ return bit_cast(m,as<type>()); }, that);
    }
    else
    {
      return interleave_(EVE_RETARGET(cpu_),v0,v1,v2);
    }
  }

  //================================================================================================
  // Interleave quadruplets of wides
  //================================================================================================
  template<scalar_value T, typename N>
  EVE_FORCEINLINE auto interleave_( EVE_SUPPORTS(sse2_)
                                  , wide<T,N> v0, wide<T,N> v1, wide<T,N> v2, wide<T,N> v3
                                  ) noexcept
  requires (N::value > 1) && x86_abi<abi_t<T,N>>
  {
    using type = wide<T,N>;
    constexpr auto c = categorize<type>();

    if constexpr( c == category::float32x4 )
    {
      if constexpr(N::value == 2)
      {
        return interleave_(EVE_RETARGET(cpu_),v0,v1,v2,v3);
      }
      else if constexpr(N::value == 4)
      {
        auto[t0,t1] = interleave(v0,v2);
        auto[t2,t3] = interleave(v1,v3);

        auto[r0,r1] = interleave(t0,t2);
        auto[r2,r3] = interleave(t1,t3);

        return kumi::tuple{r0,r1,r2,r3};
      }
    }
    else if constexpr( match(c,category::int32x4, category::uint32x4) )
    {
      using  ftype = as<wide< as_floating_point_t<T>,N>>;
      auto that = interleave( bit_cast(v0,ftype()),bit_cast(v1,ftype())
                            , bit_cast(v2,ftype()),bit_cast(v3,ftype())
                            );
      return kumi::map( [](auto m){ return bit_cast(m,as<type>()); }, that);
    }
    else
    {
      return interleave_(EVE_RETARGET(cpu_),v0,v1,v2,v3);
    }
  }
}
