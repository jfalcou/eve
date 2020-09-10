//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/function/patterns/slide_left.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(neon128_), slide_left const&
                                  , as_<Target>, [[maybe_unused]] Pattern const& p, Wide const& v
                                  )
  {
    using in_t = typename Wide::storage_type;
    constexpr auto c  = cardinal_v<Wide>;
    constexpr auto sz = Pattern::size(c);
    constexpr auto s  = sz-1-slide_left::find_slide(Pattern());

    [[maybe_unused]] Wide z(0);

    if constexpr( c == sz ) // same cardinal in and out
    {
           if constexpr(std::is_same_v<in_t,  int64x1_t>) return Target{vext_s64 (v,z,s)};
      else if constexpr(std::is_same_v<in_t,  int64x2_t>) return Target{vextq_s64(v,z,s)};
      else if constexpr(std::is_same_v<in_t, uint64x1_t>) return Target{vext_u64 (v,z,s)};
      else if constexpr(std::is_same_v<in_t, uint64x2_t>) return Target{vextq_u64(v,z,s)};
      else if constexpr(std::is_same_v<in_t,  int32x2_t>) return Target{vext_s32 (v,z,s)};
      else if constexpr(std::is_same_v<in_t,  int32x4_t>) return Target{vextq_s32(v,z,s)};
      else if constexpr(std::is_same_v<in_t, uint32x2_t>) return Target{vext_u32 (v,z,s)};
      else if constexpr(std::is_same_v<in_t, uint32x4_t>) return Target{vextq_u32(v,z,s)};
      else if constexpr(std::is_same_v<in_t,  int16x4_t>) return Target{vext_s16 (v,z,s)};
      else if constexpr(std::is_same_v<in_t,  int16x8_t>) return Target{vextq_s16(v,z,s)};
      else if constexpr(std::is_same_v<in_t, uint16x4_t>) return Target{vext_u16 (v,z,s)};
      else if constexpr(std::is_same_v<in_t, uint16x8_t>) return Target{vextq_u16(v,z,s)};
      else if constexpr(std::is_same_v<in_t,  int8x8_t >) return Target{vext_s8  (v,z,s)};
      else if constexpr(std::is_same_v<in_t,  int8x16_t>) return Target{vextq_s8 (v,z,s)};
      else if constexpr(std::is_same_v<in_t, uint8x8_t >) return Target{vext_u8  (v,z,s)};
      else if constexpr(std::is_same_v<in_t, uint8x16_t>) return Target{vextq_u8 (v,z,s)};
      else
      {
        return bit_cast ( do_swizzle( EVE_RETARGET(neon128_), slide_left{}
                                    , as<as_integer_t<Target>>(), p
                                    , bit_cast( v, as<as_integer_t<Wide>>())
                                    )
                        , as<Target>()
                        );
      }
    }
    else if constexpr( c > sz ) // 128 -> 64
    {
      auto r = v.slice(lower_);
      return r[ p ];
    }
    else // 64->128
    {
      return Target( v[ pattern_view<0,sz/2>(p) ], v[ pattern_view<sz/2,sz/2>(p) ] );
    }
  }
}
