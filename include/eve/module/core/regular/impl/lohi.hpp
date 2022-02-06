//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/shuffle.hpp>
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
        return kumi::tuple<ui_t, ui_t>{ui_t(uia0 & ui_t(0xF)), ui_t((uia0 & ui_t(0xF0)) >> 4)};
      }
      else
      {
        using si_t = downgrade_t<as_integer_t<elt_t, unsigned>>;

        if constexpr(simd_value<T>)
        {
          using ui_t       = wide<si_t, typename cardinal_t<T>::combined_type>;
          using vi_t       = wide<si_t, cardinal_t<T>>;
          auto uia0        = bit_cast(a0, as<ui_t>());
          auto constexpr p = as_pattern ( [](auto i, auto c)
                                          {
                                            return (i < c/2) ? 2 * i : 2 * (i-c/2)+1;
                                          }
                                        );
          auto z = eve::shuffle(uia0,p).slice();

          if constexpr(endian::native == endian::little)  return kumi::tuple<vi_t, vi_t>{bit_cast(z[0], as<vi_t>()), bit_cast(z[1], as<vi_t>())};
          else                                            return kumi::tuple<vi_t, vi_t>{bit_cast(z[1], as<vi_t>()), bit_cast(z[0], as<vi_t>())};
        }
        else
        {
          using si_t  = downgrade_t<as_integer_t<elt_t, unsigned>>;
          using r_t   = std::array<si_t, 2>;
          auto z      = bit_cast(a0, as<r_t>());

          if constexpr(endian::native == endian::little)  return kumi::tuple<si_t, si_t>{z[0], z[1]};
          else                                            return kumi::tuple<si_t, si_t>{z[1], z[0]};
        }
      }
    }
    else return apply_over2(lohi, a0);
  }
}
