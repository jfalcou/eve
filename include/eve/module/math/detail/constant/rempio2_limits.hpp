//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/pi.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/constant/pio_4.hpp>
#include <eve/module/math/decorator/trigo_tags.hpp>

namespace eve::detail
{
template<typename D, typename T>
EVE_FORCEINLINE T
Rempio2_limit(D const&, as<T> const&) noexcept
{
  if constexpr( floating_value<T> )
  {
    if constexpr( std::is_same_v<D, quarter_circle_type> ) { return pio_4(eve::as<T>()); }
    else if constexpr( std::is_same_v<D, half_circle_type> ) { return pio_2(eve::as<T>()); }
    else if constexpr( std::is_same_v<D, full_circle_type> )
    {
      return T(pi(eve::as<float>())); // this to ensure that converting from float to double will
                                      // preserve belonging to the interval
    }
    else if constexpr( std::is_same_v<D, medium_type> )
    {
      return ieee_cts<0x1.9220e60p+50f, 0x1.6bcc41e900000p+47>(eve::as<T>{}); // 1.76858e+15,  2.0e14
    }
    else { return valmax(eve::as<T>()); }
  }
  else { return valmax(eve::as<T>()); }
}
}
