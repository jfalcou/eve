//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/abi.hpp>
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

  template <simd_value Wide, std::ptrdiff_t Shift>
  EVE_FORCEINLINE Wide slide_right_(EVE_SUPPORTS(cpu_), Wide x, Wide y, index_t<Shift>) noexcept
  requires(Shift <= Wide::size() )
  {
         if constexpr ( Shift == 0                 ) return y;
    else if constexpr ( Shift == Wide::size()      ) return x;
    else if constexpr( is_bundle_v<typename Wide::abi_type> )
    {
      return Wide( kumi::map ( []<typename T>(T mx, T my) { return slide_right(mx, my, index<Shift>); }, x, y) );
    }
    else if constexpr ( has_aggregated_abi_v<Wide> )
    {
      // [aa bb] [cc dd] => [bccd], [abbc]
      auto [aa, bb] = x.slice();
      auto [cc, dd] = y.slice();

      constexpr std::ptrdiff_t half = Wide::size() / 2;

      if constexpr ( Shift <= half )
      {
        auto s = index<Shift>;
        return Wide{ slide_right(bb, cc, s), slide_right(cc, dd, s) };
      }
      else
      {
        auto s = index<Shift - half>;
        return Wide{ slide_right(aa, bb, s), slide_right(bb, cc, s) };
      }
    }
    else if constexpr ( !native_simd_for_abi<Wide, typename Wide::abi_type> )
    {
      return slide_right( eve::combine(x, y), index<Shift>).slice(upper_);
    }
    else
    {
      Wide res{ [&](int i, int size) {
        if (i < Shift) return x.get(size - Shift + i);
        else           return y.get(i - Shift);
      }};
      return res;
    }
  }

  template<simd_value Wide, std::ptrdiff_t Shift>
  EVE_FORCEINLINE auto slide_right_(EVE_SUPPORTS(cpu_), logical<Wide> v, index_t<Shift> s) noexcept
  requires(Shift <= Wide::size() )
  {
    return bit_cast(slide_right(v.bits(),s), as<logical<Wide>>{});
  }

  template<simd_value Wide, std::ptrdiff_t Shift>
  EVE_FORCEINLINE auto slide_right_(EVE_SUPPORTS(cpu_)
                                   , logical<Wide> x
                                   , logical<Wide> y
                                   , index_t<Shift> s) noexcept
  requires(Shift <= Wide::size() )
  {
    return bit_cast(slide_right(x.bits(), y.bits(), s), as<logical<Wide>>{});
  }
}
