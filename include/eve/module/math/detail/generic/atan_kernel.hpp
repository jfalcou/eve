//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>
#include <eve/module/math/constant/pi.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/constant/pio_4.hpp>
#include <eve/module/math/decorator/trigo_tags.hpp>

namespace eve::detail
{
  template<floating_ordered_value T>
  EVE_FORCEINLINE auto
  atan_kernel(T const& x, T const& recx) noexcept
  {
    const auto flag1 = x < ieee_constant<T>(0x1.3504f40p+1f, 0x1.3504f333f9de6p+1); // tan(3pi/8)
    const auto flag2 =
      x >= ieee_constant<T>(0x1.a8279a0p-2f, 0x1.a827999fcef31p-2) && flag1; // tan(pi/8)
    T yy       = eve::if_else(flag1, eve::zero, pio_2(eve::as(x)));
    yy         = eve::if_else(flag2, pio_4(eve::as(x)), yy);
    T xx       = eve::if_else(flag1, x, -recx);
    xx         = eve::if_else(flag2, eve::dec(x) / eve::inc(x), xx);
    T z        = eve::sqr(xx);
    using vt_t = element_type_t<T>;
    if constexpr( std::is_same_v<vt_t, float> )
    {
      z = z
        *
        eve::reverse_horner(z, T(-0x1.555454p-2f), T(0x1.9924bep-3f), T(-0x1.1c370ap-3f), T(0x1.49e1a2p-4f))
        ;
    }
    else if constexpr( std::is_same_v<vt_t, double> )
    {
      z = z*eve::reverse_horner(z, T(-0x1.03669fd28ec8ep+6), T(-0x1.eb8bf2d05ba25p+6)
                               , T(-0x1.2c08c36880273p+6), T(-0x1.028545b6b807ap+4), T(-0x1.c007fa1f72594p-1))
        /
        eve::reverse_horner(z, T(0x1.8519efbbd62ecp+7), T(0x1.e563f13b049eap+8), T(0x1.b0e18d2e2be3bp+8)
                           , T(0x1.4a0dd43b8fa25p+7), T(0x1.8dbc45b14603cp+4), T(0x1.0p0));
    }
    z = eve::fma(xx, z, xx);
    z = add[flag2](z, ieee_constant<T>(-0x1.777a5c0p-26f, 0x1.1a62633145c07p-55));  // pio_4lo
    z = add[!flag1](z, ieee_constant<T>(-0x1.777a5c0p-25f, 0x1.1a62633145c07p-54)); // pio_2lo
    return yy + z;
  }
}
