//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/decorator/trigo_tags.hpp>
#include <eve/module/math/constant/pio_4.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/constant/pi.hpp>

namespace eve::detail
{
  template <typename D, typename T>
  EVE_FORCEINLINE T Rempio2_limit(D const &, as<T> const &) noexcept
  {
    if constexpr(floating_value<T>)
    {
      if constexpr(std::is_same_v<D, quarter_circle_type>)
      {
        return pio_4(eve::as<T>());
      }
      else if constexpr(std::is_same_v<D, half_circle_type>)
      {
        return pio_2(eve::as<T>());
      }
      else if constexpr(std::is_same_v<D, full_circle_type>)
      {
        return T(pi(eve::as<float>())); // this to ensure that converting from float to double will preserve belonging to the interval
      }
      else  if constexpr(std::is_same_v<D, medium_type>)
      {
        return Ieee_constant<T, 0x58C91073U, 0x42E6BCC41E900000ULL>(); //1.76858e+15,  2.0e14
      }
      else
      {
        return valmax(eve::as<T>());
      }
    }
    else
    {
      return valmax(eve::as<T>());
    }
  }
}
