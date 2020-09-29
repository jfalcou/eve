//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE
s
  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/function/patterns/slide_right.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/swizzle.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename Wide, typename Target, shuffle_pattern Pattern>
  EVE_FORCEINLINE Target do_swizzle ( EVE_SUPPORTS(neon128_), slide_right const&
                                    , as_<Target>, [[maybe_unused]] Pattern const& p, Wide const& v
                                    )
  {
    constexpr auto c  = cardinal_v<Wide>;
    constexpr auto sz = Pattern::size(c);
    using in_t  = typename Wide::storage_type;

    constexpr auto slider = []<typename N>(auto w, N const&)
    {
           if constexpr(std::is_same_v<in_t, int64x1_t>) return Target{vext_s64 (Wide{0},w,N::value)};
      else if constexpr(std::is_same_v<in_t, int64x2_t>) return Target{vextq_s64(Wide{0},w,N::value)};
      else if constexpr(std::is_same_v<in_t,uint64x1_t>) return Target{vext_u64 (Wide{0},w,N::value)};
      else if constexpr(std::is_same_v<in_t,uint64x2_t>) return Target{vextq_u64(Wide{0},w,N::value)};
      else if constexpr(std::is_same_v<in_t, int32x2_t>) return Target{vext_s32 (Wide{0},w,N::value)};
      else if constexpr(std::is_same_v<in_t, int32x4_t>) return Target{vextq_s32(Wide{0},w,N::value)};
      else if constexpr(std::is_same_v<in_t,uint32x2_t>) return Target{vext_u32 (Wide{0},w,N::value)};
      else if constexpr(std::is_same_v<in_t,uint32x4_t>) return Target{vextq_u32(Wide{0},w,N::value)};
      else if constexpr(std::is_same_v<in_t, int16x4_t>) return Target{vext_s16 (Wide{0},w,N::value)};
      else if constexpr(std::is_same_v<in_t, int16x8_t>) return Target{vextq_s16(Wide{0},w,N::value)};
      else if constexpr(std::is_same_v<in_t,uint16x4_t>) return Target{vext_u16 (Wide{0},w,N::value)};
      else if constexpr(std::is_same_v<in_t,uint16x8_t>) return Target{vextq_u16(Wide{0},w,N::value)};
      else if constexpr(std::is_same_v<in_t, int8x8_t >) return Target{vext_s8  (Wide{0},w,N::value)};
      else if constexpr(std::is_same_v<in_t, int8x16_t>) return Target{vextq_s8 (Wide{0},w,N::value)};
      else if constexpr(std::is_same_v<in_t,uint8x8_t >) return Target{vext_u8  (Wide{0},w,N::value)};
      else if constexpr(std::is_same_v<in_t,uint8x16_t>) return Target{vextq_u8 (Wide{0},w,N::value)};
    };

    if constexpr( c == sz ) // same cardinal in and out
    {
      if constexpr(std::is_floating_point_v<typename Wide::value_type>)
      {
        return bit_cast ( do_swizzle( EVE_RETARGET(neon128_), slide_right{}
                                    , as<as_integer_t<Target>>(), p
                                    , bit_cast( v, as<as_integer_t<Wide>>())
                                    )
                        , as<Target>()
                        );
      }
      else
      {
        constexpr auto s  = sz - slide_right::find_slide(Pattern());
        return slider(v,std::integral_constant<std::size_t,s>{});
      }
    }
    else if constexpr( c > sz )
    {
      if constexpr(std::is_floating_point_v<typename Wide::value_type>)
      {
        return bit_cast ( do_swizzle( EVE_RETARGET(neon128_), slide_right{}
                                    , as<as_integer_t<Target>>(), p
                                    , bit_cast( v, as<as_integer_t<Wide>>())
                                    )
                        , as<Target>()
                        );
      }
      else if constexpr( std::is_same_v<typename Wide::abit_, arm_128_>)
      {
        auto r = v.slice(lower_);
        return r[ p ];
      }
      else
      {
        constexpr auto s  = sz - slide_right::find_slide(Pattern());
        return slider(v,std::integral_constant<std::size_t,s>{});
      }
    }
    else
    {
      return do_swizzle(EVE_RETARGET(neon128_), any_match{}, as_<Target>(),p,v );
    }
  }
}
