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
    template<typename In, typename Out, shuffle_pattern Pattern>
    static constexpr auto check(Pattern, as_<In>, as_<Out>)  noexcept
    {
      constexpr Pattern p{};
      return      cardinal_v<Out> > 1
              &&
              (   p.is_similar( pattern<1,0> )
              ||  p.is_similar( pattern<3,2,1,0> )
              ||  p.is_similar( pattern<7,6,5,4,3,2,1,0> )
              ||  p.is_similar( pattern<15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0> )
              );
    }
  };

  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE Target do_swizzle ( EVE_SUPPORTS(neon128_), reverse_match const&
                                    , as_<Target> , Pattern const&, Wide const& v
                                    )
  {
    using           in_t    = typename Wide::value_type;
    constexpr auto  rebuild = [](auto s) { return Target{s.slice(upper_),s.slice(lower_)}; };
    constexpr auto  tsz     = Target::static_size;
    constexpr auto  wsz     = Wide::static_size;

          if constexpr( sizeof(in_t) == 8 )       return {v[1],v[0]};
    else  if constexpr( std::is_same_v<in_t, float> )
    {
            if constexpr(tsz == 2 && wsz == 2)    return vrev64_f32(v);
      else  if constexpr(tsz == 2 && wsz == 4)    return vrev64_f32(v.slice(upper_));
      else                                        return rebuild(Target{vrev64q_f32(v)});
    }
    else  if constexpr( std::is_integral_v<in_t> && sizeof(in_t) == 4 )
    {
      if constexpr( std::is_signed_v<in_t> )
      {
              if constexpr(tsz == 2 && wsz == 2)  return vrev64_s32(v);
        else  if constexpr(tsz == 2 && wsz == 4)  return vrev64_s32(v.slice(upper_));
        else                                      return rebuild(Target{vrev64q_s32(v)});
      }
      else
      {
              if constexpr(tsz == 2 && wsz == 2)  return vrev64_u32(v);
        else  if constexpr(tsz == 2 && wsz == 4)  return vrev64_u32(v.slice(upper_));
        else                                      return rebuild(Target{vrev64q_u32(v)});
      }
    }
    else if constexpr( std::is_integral_v<in_t> && sizeof(in_t) == 2 )
    {
      if constexpr( std::is_signed_v<in_t> )
      {
              if constexpr(wsz == 2)              return vrev32_s16(v);
        else  if constexpr(wsz == 4 && tsz == 2)  return vrev32_s16(v.slice(upper_));
        else  if constexpr(wsz == 4 && tsz != 2)  return rebuild(Target{vrev32_s16(v)});
        else  if constexpr(tsz == 8)              return rebuild(Target{vrev64q_s16(v)});
        else                                      return vrev64_s16(v.slice(upper_));
      }
      else
      {
              if constexpr(wsz == 2)              return vrev32_u16(v);
        else  if constexpr(wsz == 4 && tsz == 2)  return vrev32_u16(v.slice(upper_));
        else  if constexpr(wsz == 4 && tsz != 2)  return rebuild(Target{vrev32_u16(v)});
        else  if constexpr(tsz == 8)              return rebuild(Target{vrev64q_u16(v)});
        else                                      return vrev64_u16(v.slice(upper_));
      }
    }
    else if constexpr( std::is_integral_v<in_t> && sizeof(in_t) == 1 )
    {
      if constexpr( std::is_signed_v<in_t> )
      {
              if constexpr(wsz == 2)              return vrev16_s8(v);
        else  if constexpr(tsz == 2)              return vrev64_s8(v.slice(upper_));
        else  if constexpr(wsz == 4)              return rebuild(Target{vrev16_s8(v)});
        else  if constexpr(tsz == 4)              return vrev64_s8(v.slice(upper_));
        else  if constexpr(tsz == 8 && wsz == 8)  return rebuild(Target{vrev32_s8(v)});
        else  if constexpr(tsz == 8 && wsz != 8)  return vrev64_s8(v.slice(upper_));
        else                                      return rebuild(Target{vrev64q_s8(v)});
      }
      else
      {
              if constexpr(wsz == 2)              return vrev16_u8(v);
        else  if constexpr(tsz == 2)              return vrev64_u8(v.slice(upper_));
        else  if constexpr(wsz == 4)              return rebuild(Target{vrev16_u8(v)});
        else  if constexpr(tsz == 4)              return vrev64_u8(v.slice(upper_));
        else  if constexpr(tsz == 8 && wsz == 8)  return rebuild(Target{vrev32_u8(v)});
        else  if constexpr(tsz == 8 && wsz != 8)  return vrev64_u8(v.slice(upper_));
        else                                      return rebuild(Target{vrev64q_u8(v)});
      }
    }
  }
}
