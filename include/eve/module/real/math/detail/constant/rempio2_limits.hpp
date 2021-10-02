//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pi.hpp>
#include <eve/concept/value.hpp>
#include <eve/as.hpp>

namespace eve::detail
{
  template <typename D, typename T>
  EVE_FORCEINLINE auto Rempio2_limit(D const &, as<T> const &) noexcept
  {
    if constexpr(floating_value<T>)
    {
      if constexpr(std::is_same_v<D, restricted_type>)
      {
        return pio_4(eve::as<T>());
      }
      else if constexpr(std::is_same_v<D, small_type>)
      {
        return pio_2(eve::as<T>());
      }
      else if constexpr(std::is_same_v<D, circle_type>)
      {
        return pi(eve::as<T>());
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
