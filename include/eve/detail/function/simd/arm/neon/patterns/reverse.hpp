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

#include <eve/detail/implementation.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/element_type.hpp>

namespace eve::detail
{
  //================================================================================================
  // Match any pattern of the form [N-1 ... 2 1 0]
  //================================================================================================
  struct reverse_match
  {
    template<typename Wide, shuffle_pattern Pattern>
    static constexpr auto check(Pattern const&, as_<Wide> const&)  noexcept
    {
      constexpr Pattern p{};

      return      p.size(Wide::static_size) > 1
              &&
              (   p.is_similar( pattern<1,0> )
              ||  p.is_similar( pattern<3,2,1,0> )
              ||  p.is_similar( pattern<7,6,5,4,3,2,1,0> )
              ||  p.is_similar( pattern<15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0> )
              );
    }
  };

  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(neon128_), reverse_match const&
                                  , as_<Target> , Pattern const&, Wide const& v
                                  )
  {
    using in_t        = typename Wide::storage_type;

    if constexpr( Wide::static_size == Target::static_size)
    {
      [[maybe_unused]] Target s;

           if constexpr(std::is_same_v<in_t,  int32x2_t >) s = Target(vrev64_s32 (v));
      else if constexpr(std::is_same_v<in_t,  uint32x2_t>) s = Target(vrev64_u32 (v));
      else if constexpr(std::is_same_v<in_t,  int16x4_t >) s = Target(vrev32_s16 (v));
      else if constexpr(std::is_same_v<in_t,  uint16x4_t>) s = Target(vrev32_u16 (v));
      else if constexpr(std::is_same_v<in_t,  int8x8_t  >) s = Target(vrev64_s8  (v));
      else if constexpr(std::is_same_v<in_t,  uint8x8_t >) s = Target(vrev64_u8  (v));
      else if constexpr(std::is_same_v<in_t, float32x2_t>) s = Target(vrev64_f32 (v));
      else if constexpr(std::is_same_v<in_t,  int32x4_t >) s = Target(vrev64q_s32(v));
      else if constexpr(std::is_same_v<in_t,  uint32x4_t>) s = Target(vrev64q_u32(v));
      else if constexpr(std::is_same_v<in_t,  int16x8_t >) s = Target(vrev64q_s16(v));
      else if constexpr(std::is_same_v<in_t,  uint16x8_t>) s = Target(vrev64q_u16(v));
      else if constexpr(std::is_same_v<in_t,  int8x16_t >) s = Target(vrev64q_s8 (v));
      else if constexpr(std::is_same_v<in_t,  uint8x16_t>) s = Target(vrev64q_u8 (v));
      else if constexpr(std::is_same_v<in_t, float32x4_t>) s = Target(vrev64q_f32(v));
      else
      {
        return Target{v[1],v[0]};
      }

      auto[l,h] = s.slice();
      return Target(h,l);
    }
    else if constexpr( Wide::static_size > Target::static_size)
    {
      constexpr auto slicer = [](auto i)
      {
        constexpr Pattern p{};
        constexpr auto first = p(0,Wide::static_size);
        if(first == Wide::static_size-1)  return i.slice(upper_);
        else                              return i.slice(lower_);
      };

      auto s = slicer(v);

            if constexpr(std::is_same_v<in_t,  int32x4_t >) return Target(vrev64_s32(s));
      else  if constexpr(std::is_same_v<in_t,  uint32x4_t>) return Target(vrev64_u32(s));
      else  if constexpr(std::is_same_v<in_t,  int16x8_t >) return Target(vrev64_s16(s));
      else  if constexpr(std::is_same_v<in_t,  uint16x8_t>) return Target(vrev64_u16(s));
      else  if constexpr(std::is_same_v<in_t,  int8x16_t >) return Target(vrev64_s8 (s));
      else  if constexpr(std::is_same_v<in_t,  uint8x16_t>) return Target(vrev64_u8 (s));
      else  if constexpr(std::is_same_v<in_t, float32x4_t>) return Target(vrev64_f32(s));
      else
      {
        return Target{v[1]};
      }
    }
    else
    {
      puts("TODO: reverse");
      return Target{};
    }
  }
}
