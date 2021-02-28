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

#include <tuple>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<value T>
  EVE_FORCEINLINE constexpr auto lohi_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  requires(sizeof(element_type_t<T>) > 1)
  {
    using elt_t = element_type_t<T>;
    using si_t = downgrade_t<as_integer_t<elt_t, unsigned>>;
    if constexpr(simd_value<T>)
    {
      using ui_t = wide<si_t, fixed<cardinal_t<T>::value*2>>;
      std::cout << tts::typename_of_(a0) << std::endl;
      std::cout << tts::typename_of_(ui_t()) << std::endl;
      std::cout << sizeof(ui_t) << std::endl;
      std::cout << sizeof(T)    << std::endl;
      //  return std::make_tuple(a0, a0);
      auto uia0 = bit_cast(a0, as<ui_t>());
      auto constexpr p = fix_pattern([](auto i,  auto c) { return i&1 ? c/2+i/2 : i/2; });
      uia0 = basic_swizzle(uia0, p);
      return uia0.slice();
    }
    else
    {
      using r_t = std::pair<si_t, si_t>;
      return bit_cast(a0, as<r_t>());
    }
  }
}
