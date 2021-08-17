//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/add.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <type_traits>
#include <eve/module/real/core/detail/generic/horn.hpp>
#include <eve/module/real/core/detail/generic/horn1.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE
  auto atan_kernel( T const & x,  T const & recx ) noexcept
  {
    const auto flag1 = x <  Ieee_constant<T,  0X401A827AU, 0X4003504F333F9DE6ULL>(); //tan(3pi/8)
    const auto flag2 = x >= Ieee_constant<T, 0x3ed413cdU, 0X3FDA827999FCEF31ULL>() && flag1; // tan(pi/8)
    T yy  = eve::if_else(flag1, eve::zero, pio_2(eve::as(x)));
      yy  = eve::if_else(flag2, pio_4(eve::as(x)), yy);
    T xx  = eve::if_else(flag1, x, -recx);
      xx  = eve::if_else(flag2, eve::dec(x)/eve::inc(x),xx);
    T z   = eve::sqr(xx);
    using vt_t =  value_type_t<T>;
    if constexpr(std::is_same_v<vt_t, float>)
    {
       z = z*horn<T
        , 0xbeaaaa2au  // -3.3333293e-01
        , 0x3e4c925fu  //  1.9991724e-01
        , 0xbe0e1b85u  // -1.4031009e-01
        , 0x3da4f0d1u  //  8.5460119e-02
        > (z);
    }
    else if constexpr(std::is_same_v<vt_t, double>)
    {
      z = z* horn<T,
        0xc0503669fd28ec8ell,
        0xc05eb8bf2d05ba25ll,
        0xc052c08c36880273ll,
        0xc03028545b6b807all,
        0xbfec007fa1f72594ll
        >(z)/
        horn1<T,
        0x4068519efbbd62ecll,
        0x407e563f13b049eall,
        0x407b0e18d2e2be3bll,
        0x4064a0dd43b8fa25ll,
        0x4038dbc45b14603cll
        >(z);
    }
    z = eve::fma(xx, z, xx);
    z = add[flag2]     (z, Ieee_constant<T, 0XB2BBBD2EU, 0X3C81A62633145C07ULL>());  //pio_4lo
    z = add[!flag1](z, Ieee_constant<T,0XB33BBD2EU, 0X3C91A62633145C07ULL>());   //pio_2lo
    return yy + z;
  }
}
