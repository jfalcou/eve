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
  EVE_FORCEINLINE Target do_swizzle ( EVE_SUPPORTS(neon128_), slide_left const&
                                    , as_<Target>, [[maybe_unused]] Pattern const& p, Wide const& v
                                    )
  {
    constexpr auto c  = cardinal_v<Wide>;
    constexpr auto sz = Pattern::size(c);
    using in_t  = typename Wide::storage_type;

    constexpr auto slider = []<typename N>(auto w, N const&)
    {
           if constexpr(std::is_same_v<in_t, int64x1_t>) return Target{vext_s64 (w,Wide{0},N::value)};
      else if constexpr(std::is_same_v<in_t, int64x2_t>) return Target{vextq_s64(w,Wide{0},N::value)};
      else if constexpr(std::is_same_v<in_t,uint64x1_t>) return Target{vext_u64 (w,Wide{0},N::value)};
      else if constexpr(std::is_same_v<in_t,uint64x2_t>) return Target{vextq_u64(w,Wide{0},N::value)};
      else if constexpr(std::is_same_v<in_t, int32x2_t>) return Target{vext_s32 (w,Wide{0},N::value)};
      else if constexpr(std::is_same_v<in_t, int32x4_t>) return Target{vextq_s32(w,Wide{0},N::value)};
      else if constexpr(std::is_same_v<in_t,uint32x2_t>) return Target{vext_u32 (w,Wide{0},N::value)};
      else if constexpr(std::is_same_v<in_t,uint32x4_t>) return Target{vextq_u32(w,Wide{0},N::value)};
      else if constexpr(std::is_same_v<in_t, int16x4_t>) return Target{vext_s16 (w,Wide{0},N::value)};
      else if constexpr(std::is_same_v<in_t, int16x8_t>) return Target{vextq_s16(w,Wide{0},N::value)};
      else if constexpr(std::is_same_v<in_t,uint16x4_t>) return Target{vext_u16 (w,Wide{0},N::value)};
      else if constexpr(std::is_same_v<in_t,uint16x8_t>) return Target{vextq_u16(w,Wide{0},N::value)};
      else if constexpr(std::is_same_v<in_t, int8x8_t >) return Target{vext_s8  (w,Wide{0},N::value)};
      else if constexpr(std::is_same_v<in_t, int8x16_t>) return Target{vextq_s8 (w,Wide{0},N::value)};
      else if constexpr(std::is_same_v<in_t,uint8x8_t >) return Target{vext_u8  (w,Wide{0},N::value)};
      else if constexpr(std::is_same_v<in_t,uint8x16_t>) return Target{vextq_u8 (w,Wide{0},N::value)};
    };

    if constexpr(std::is_floating_point_v<typename Wide::value_type>)
    {
      return bit_cast ( do_swizzle( EVE_RETARGET(neon128_), slide_left{}
                                  , as<as_integer_t<Target>>(), p
                                  , bit_cast( v, as<as_integer_t<Wide>>())
                                  )
                      , as<Target>()
                      );
    }
    else if constexpr( c == sz ) // same cardinal in and out
    {
      constexpr auto s  = Pattern()(0,c);
      return slider(v,std::integral_constant<std::ptrdiff_t,s>{});
    }
    else if constexpr( c > sz )
    {
      auto r = v[ fix_pattern<c>(p) ];
      return bit_cast(r.slice(lower_), as_<Target>());
    }
  }
}
