//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/traits/product_type.hpp>

namespace eve::detail
{
  //================================================================================================
  // Interleave pairs of wides
  //================================================================================================
  template<scalar_value T, typename N>
  EVE_FORCEINLINE auto interleave_(EVE_SUPPORTS(neon128_), wide<T,N> v0, wide<T,N> v1) noexcept
  requires (N::value > 1) && arm_abi<abi_t<T,N>>
  {
    using type = wide<T,N>;

    constexpr auto c = categorize<type>();

    if constexpr( c == category::float32x2)
    {
      auto const s =  vzip_f32(v0,v1);
      return kumi::make_tuple(type(s.val[0]), type(s.val[1]));
    }
    else  if constexpr( c == category::int32x2  )
    {
      auto const s =  vzip_s32(v0,v1);
      return kumi::make_tuple(type(s.val[0]), type(s.val[1]));
    }
    else  if constexpr( c == category::uint32x2 )
    {
      auto const s =  vzip_u32(v0,v1);
      return kumi::make_tuple(type(s.val[0]), type(s.val[1]));
    }
    else  if constexpr( c == category::int16x4  )
    {
      auto s = vzip_s16(v0,v1);
      if constexpr(N::value == 4 ) return kumi::make_tuple(type(s.val[0]), type(s.val[1]));
      else
      {
        auto[l,h] = wide<T,fixed<4>>(s.val[0]).slice();
        return kumi::make_tuple(l,h);
      }
    }
    else  if constexpr( c == category::uint16x4 )
    {
      auto s = vzip_u16(v0,v1);
      if constexpr(N::value == 4 ) return kumi::make_tuple(type(s.val[0]), type(s.val[1]));
      else
      {
        auto[l,h] = wide<T,fixed<4>>(s.val[0]).slice();
        return kumi::make_tuple(l,h);
      }
    }
    else  if constexpr( c == category::int8x8   )
    {
      auto const s =  vzip_s8 (v0,v1);
      if constexpr(N::value == 8 ) return kumi::make_tuple(type(s.val[0]), type(s.val[1]));
      else if constexpr(N::value == 4 )
      {
        auto[l,h] = wide<T,fixed<8>>(s.val[0]).slice();
        return kumi::make_tuple(l,h);
      }
      else
      {
        auto[l,h] = wide<T,fixed<8>>(s.val[0]).slice(lower_).slice();
        return kumi::make_tuple(l,h);
      }
    }
    else  if constexpr( c == category::uint8x8  )
    {
      auto const s =  vzip_u8 (v0,v1);
      if constexpr(N::value == 8 ) return kumi::make_tuple(type(s.val[0]), type(s.val[1]));
      else if constexpr(N::value == 4 )
      {
        auto[l,h] = wide<T,fixed<8>>(s.val[0]).slice();
        return kumi::make_tuple(l,h);
      }
      else
      {
        auto[l,h] = wide<T,fixed<8>>(s.val[0]).slice(lower_).slice();
        return kumi::make_tuple(l,h);
      }
    }
    else  if constexpr( c == category::float32x4)
    {
      auto const s =  vzipq_f32(v0,v1);
      return kumi::make_tuple(type(s.val[0]), type(s.val[1]));
    }
    else  if constexpr( c == category::int32x4  )
    {
      auto const s =  vzipq_s32(v0,v1);
      return kumi::make_tuple(type(s.val[0]), type(s.val[1]));
    }
    else  if constexpr( c == category::uint32x4 )
    {
      auto const s =  vzipq_u32(v0,v1);
      return kumi::make_tuple(type(s.val[0]), type(s.val[1]));
    }
    else  if constexpr( c == category::int16x8  )
    {
      auto const s =  vzipq_s16(v0,v1);
      return kumi::make_tuple(type(s.val[0]), type(s.val[1]));
    }
    else  if constexpr( c == category::uint16x8 )
    {
      auto const s =  vzipq_u16(v0,v1);
      return kumi::make_tuple(type(s.val[0]), type(s.val[1]));
    }
    else  if constexpr( c == category::int8x16  )
    {
      auto const s =  vzipq_s8(v0,v1);
      return kumi::make_tuple(type(s.val[0]), type(s.val[1]));
    }
    else  if constexpr( c == category::uint8x16 )
    {
      auto const s =  vzipq_u8(v0,v1);
      return kumi::make_tuple(type(s.val[0]), type(s.val[1]));
    }
    else
    {
      return interleave_(EVE_RETARGET(cpu_),v0,v1);
    }
  }
}
