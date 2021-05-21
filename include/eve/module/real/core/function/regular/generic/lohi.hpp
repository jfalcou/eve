//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/meta.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/swizzle.hpp>
#include <tuple>
#include <bit>

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE constexpr auto lohi_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    using std::endian;
    if constexpr(has_native_abi_v<T>)
    {
      using elt_t = element_type_t<T>;
      if constexpr (sizeof(elt_t) ==  1) //nibbles extraction
      {
        using ui_t = as_integer_t<T, unsigned>;
        auto uia0 =  bit_cast(a0, as<ui_t>());
        return std::tuple<ui_t, ui_t>{ui_t(uia0 & ui_t(0xF)), ui_t((uia0 & ui_t(0xF0)) >> 4)};
      }
      else
      {
        using si_t = downgrade_t<as_integer_t<elt_t, unsigned>>;

        if constexpr(simd_value<T>)
        {
          using ui_t       = wide<si_t, typename cardinal_t<T>::combined_type>;
          auto uia0        = bit_cast(a0, as<ui_t>());
          auto constexpr p = as_pattern ( [](auto i, auto c)
                                          {
                                            return (i < c/2) ? 2 * i : 2 * (i-c/2)+1;
                                          }
                                        );
          auto z = uia0[p].slice();

          if constexpr(endian::native == endian::little)  return decltype(z){std::get<1>(z), std::get<0>(z)};
          else                                            return decltype(z){std::get<1>(z), std::get<0>(z)};
        }
        else
        {
          using si_t  = downgrade_t<as_integer_t<elt_t, unsigned>>;
          using r_t   = std::tuple<si_t, si_t>;
          auto z      = bit_cast(a0, as<r_t>());

          if constexpr(endian::native == endian::little)  return std::tuple<si_t, si_t>{std::get<1>(z), std::get<0>(z)};
          else                                            return std::tuple<si_t, si_t>{std::get<1>(z), std::get<0>(z)};
        }
      }
    }
    else return apply_over2(lohi, a0);
  }
}
