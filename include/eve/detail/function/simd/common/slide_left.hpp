//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/slide_right.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  template<std::ptrdiff_t Shift, std::ptrdiff_t N>
  inline constexpr
  auto slide_left_pattern = fix_pattern<N>( [](auto i, auto c)
                                            {
                                              return (i+Shift) < c ? i+Shift : na_;
                                            }
                                          );

  template <std::ptrdiff_t Shift>
  struct slide_left_lambda
  {
    EVE_FORCEINLINE auto operator()(auto ... xs) const
    {
      return slide_left(xs..., index<Shift>);
    }
  };

  template<simd_value Wide, std::ptrdiff_t Shift>
  EVE_FORCEINLINE auto slide_left_(EVE_SUPPORTS(cpu_), Wide v, index_t<Shift>) noexcept
  requires(Shift <= Wide::size() )
  {
          if constexpr(Shift == 0)            return v;
    else  if constexpr(Shift == Wide::size()) return Wide{0};
    else if constexpr( has_aggregated_abi_v<Wide> )
    {
      if constexpr(Shift >= Wide::size()/2)
      {
        // We slide so much the upper part is full of zero
        // and the lower part is a slide of the former higher part
        auto h = v.slice(upper_);
        return Wide{ slide_left(h, index<Shift-Wide::size()/2>), decltype(h){0} };
      }
      else
      {
        auto[l,h] = v.slice();
        l = slide_left(l, h, index<Shift>);
        h = slide_left(h, index<Shift>);

        return Wide{l,h};
      }
    }
    else if constexpr( is_bundle_v<typename Wide::abi_type> )
    {
      return Wide( kumi::map ( []<typename T>(T m) { return slide_left(m,index<Shift>); }, v) );
    }
    else
    {
      if constexpr( logical_value<Wide> && Wide::abi_type::is_wide_logical)
      {
        return bit_cast(slide_left(v.bits(),index<Shift>), as<Wide>{});
      }
      else
      {
        return basic_swizzle(v, slide_left_pattern<Shift,Wide::size()>);
      }
    }
  }

  template <simd_value Wide, std::ptrdiff_t Shift>
  EVE_FORCEINLINE Wide slide_left_(EVE_SUPPORTS(cpu_), Wide x, Wide y, index_t<Shift>) noexcept
  requires( Shift <= Wide::size() )
  {
         if constexpr ( Shift == 0            ) return x;
    else if constexpr ( Shift == Wide::size() ) return y;
    else if constexpr( is_bundle_v<typename Wide::abi_type> )
    {
      return Wide( kumi::map ( slide_left_lambda<Shift>{}, x, y) );
    }
    else if constexpr ( has_aggregated_abi_v<Wide> )
    {
      // [aa bb] [cc dd] => [abbc], [bccd]

      auto [aa, bb] = x.slice();
      auto [cc, dd] = y.slice();

      constexpr std::ptrdiff_t half = Wide::size() / 2;

      if constexpr ( Shift <= half )
      {
        auto s = index<Shift>;
        return Wide{ slide_left( aa, bb, s ), slide_left(bb, cc, s) };
      }
      else
      {
        auto s = index<Shift - half>;
        return Wide{ slide_left( bb, cc, s ), slide_left(cc, dd, s) };
      }
    }
    else if constexpr ( !native_simd_for_abi<Wide, typename Wide::abi_type> )
    {
      return slide_left( eve::combine(x, y), index<Shift>).slice(lower_);
    }
    else
    {
      if constexpr( logical_value<Wide> && Wide::abi_type::is_wide_logical)
      {
        return bit_cast(slide_left(x.bits(), y.bits(), index<Shift>), as<Wide>{});
      }
      else
      {
        Wide res { [&](int i, int size) {
          if ( i < size - Shift ) return x.get(i + Shift);
          else                    return y.get(i + Shift - size);
        }};
        return res;
      }
    }
  }
}
