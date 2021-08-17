//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  template<std::ptrdiff_t Shift, std::ptrdiff_t N>
  inline constexpr
  auto slide_right_pattern = fix_pattern<N>( [](auto i, auto ){ return i<Shift ? na_ : i-Shift;} );

  template<simd_value Wide, std::ptrdiff_t Shift>
  EVE_FORCEINLINE auto slide_right_(EVE_SUPPORTS(cpu_), Wide v, index_t<Shift>) noexcept
  requires(Shift <= Wide::size() )
  {
          if constexpr(Shift == 0)            return v;
    else  if constexpr(Shift == Wide::size()) return Wide{0};
    else if constexpr( has_aggregated_abi_v<Wide> && Shift >= Wide::size()/2)
    {
      // We slide so much the lower part is full of zero
      // and the upper part is a slide of the former higher part
      auto l = v.slice(lower_);
      return Wide{ decltype(l){0}, slide_right(l, index<Shift-Wide::size()/2>) };
    }
    else if constexpr( is_bundle_v<typename Wide::abi_type> )
    {
      return Wide( kumi::map ( []<typename T>(T m) { return slide_right(m,index<Shift>); }, v) );
    }
    else
    {
      return basic_swizzle(v, slide_right_pattern<Shift,Wide::size()>);
    }
  }

  template<simd_value Wide, std::ptrdiff_t Shift>
  EVE_FORCEINLINE auto slide_right_(EVE_SUPPORTS(cpu_), logical<Wide> v, index_t<Shift> s) noexcept
  requires(Shift <= Wide::size() )
  {
    return bit_cast(slide_right(v.bits(),s), as<logical<Wide>>{});
  }
}
