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
#include <tts/tts.hpp>
#include <array>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<value T>
  EVE_FORCEINLINE constexpr auto lohi_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      using elt_t = element_type_t<T>;
      if constexpr (sizeof(elt_t) ==  1) //nibbles extraction
      {
        using ui_t = as_integer_t<T, unsigned>;
        auto uia0 =  bit_cast(a0, as<ui_t>());
        constexpr uint8_t masklo = std::uint8_t(~0) >> 4;
        constexpr uint8_t maskhi = masklo << 4;
        return std::array<ui_t, 2>{ui_t(uia0 & ui_t(masklo)), ui_t((uia0 & ui_t(maskhi)) >> 4)};
      }
      else
      {
        using si_t = downgrade_t<as_integer_t<elt_t, unsigned>>;
        if constexpr(simd_value<T>)
        {
          using ui_t = wide<si_t, fixed<cardinal_t<T>::value*2>>;
          auto uia0 = bit_cast(a0, as<ui_t>());
          auto constexpr p = as_pattern([](auto i,  auto c) { return i < c/2 ? 2 * i : 2 * (i-c/2)+1; });
          uia0 = uia0[p];
          return uia0.slice();
        }
        else
        {
          using r_t = std::array<si_t, 2>;
          std::cout << "1---------" << tts::typename_of_(a0) << std::endl;
          std::cout << "2---------" << tts::typename_of_( bit_cast(a0, as<r_t>())) << std::endl;
          std::cout << std::hex << "a0 "<< a0  << std::endl;
          std::cout << std::hex << "lo " << bit_cast(a0, as<r_t>())[0] << std::endl;
          std::cout << std::hex << "hi " << bit_cast(a0, as<r_t>())[1] << std::endl;
          std::cout << std::dec << std::endl;
          return bit_cast(a0, as<r_t>());
        }
      }
    }
    else return apply_over2(lohi, a0);
  }
}
