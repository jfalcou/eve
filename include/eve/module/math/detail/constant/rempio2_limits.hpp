//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/constant/pi.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/constant/pio_4.hpp>

namespace eve
{
  template<typename Options>
  struct Rempio2_limit_t : elementwise_callable<Rempio2_limit_t, Options, quarter_circle_option, half_circle_option
                                                , full_circle_option, medium_option, big_option>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(Rempio2_limit_t, Rempio2_limit_);
  };

  inline constexpr auto Rempio2_limit = functor<Rempio2_limit_t>;

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr T Rempio2_limit_(EVE_REQUIRES(cpu_), O const&, as<T>) noexcept
    {
      if constexpr (floating_value<T>)
      {
        if constexpr (O::contains(quarter_circle))
          return pio_4(as<T>{});
        else if constexpr (O::contains(half_circle))
          return pio_2(as<T>{});
        else if constexpr (O::contains(full_circle))
        {
          // this to ensure that converting from float to double will preserve belonging to the interval
          return T(pi(as<float>{}));
        }
        else if constexpr(O::contains(medium))
          return ieee_constant<0x1.9220e60p+50f, 0x1.6bcc41e900000p+47>(as<T>{}); // 1.76858e+15,  2.0e14
        else
          return valmax(as<T>{});
      }
      else
        return valmax(as<T>{});
    }
  }
}
