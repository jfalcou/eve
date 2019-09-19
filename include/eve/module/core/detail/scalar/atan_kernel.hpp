//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_DETAIL_SCALAR_ATAN_KERNEL_HPP_INCLUDED
#define EVE_MODULE_CORE_DETAIL_SCALAR_ATAN_KERNEL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/tags.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_equal.hpp> 
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <type_traits>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr
  auto atan_kernel( T  x,  T recx ) noexcept
  requires(T, Floating<T>)
  {
    // here T is float or double and x positive
    static_assert(std::is_same_v<T, float> || std::is_same_v<T, double>
                 , "[detail;:atan_kernel] - entry type is not IEEEValue"); 
    auto flag1 = x <  Ieee_constant<T,  0X401A827AU, 0X4003504F333F9DE6ULL>(); //tan(3pi/8)
    auto flag2 = (x >= Ieee_constant<T, 0x3ed413cdU, 0X3FDA827999FCEF31ULL>()) && flag1; // tan(pi/8)
    T yy = flag1 ? T(0) : Pio_2(as(x));
    if (flag2) yy =  Pio_4(as(x));
    T xx =  flag1 ? x : -recx;
    if (flag2) xx = eve::dec(x)/eve::inc(x); 
    T z = eve::sqr(xx);
    if constexpr(std::is_same_v<T, float>)
    {
       z = z*horn<T
        , 0xbeaaaa2au  // -3.3333293e-01
        , 0x3e4c925fu  //  1.9991724e-01
        , 0xbe0e1b85u  // -1.4031009e-01
        , 0x3da4f0d1u  //  8.5460119e-02
        > (z);
    }
    else
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
    if (flag2) z += Ieee_constant<T, 0XB2BBBD2EU, 0X3C81A62633145C07ULL>();  //pio_4lo
    if (!flag1) z += Ieee_constant<T,  0XB33BBD2EU, 0X3C91A62633145C07ULL>();//pio_2lo
    return yy + z;
  }
}

#endif
