//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_REM_PIO2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_REM_PIO2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/detail/scalar/ieee_754_rem_pio2.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto rem_pio2_(EVE_SUPPORTS(cpu_)
                                             , T const &a0) noexcept
  requires(std::tuple<T, T>, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      using r_t =  std::tuple<T, T>; 
      if constexpr(std::is_same_v<T, double>)
      {
        if (a0 == Inf<T>()) return r_t(Zero<T>(), Nan<T>());
        T y[2];
        std::int32_t n = __ieee754_rem_pio2(a0, y);
        return r_t(static_cast<T>(n&std::int32_t(3)), y[0]);
      }
      else if constexpr(std::is_same_v<T, float>)
      {
        if (a0 == Inf<T>()) return r_t(Zero<T>(), Nan<T>());
        // This is the musl way
        // invpio2:  53 bits of 2/pi
        // pio2_1:   first 25 bits of pi/2
        // pio2_1t:  pi/2 - pio2_1
        //
        static const double
          invpio2 = 6.36619772367581382433e-01, /* 0x3FE45F30, 0x6DC9C883 */
          pio2_1  = 1.57079631090164184570e+00, /* 0x3FF921FB, 0x50000000 */
          pio2_1t = 1.58932547735281966916e-08; /* 0x3E5110b4, 0x611A6263 */
        int32_t ix =  bitwise_cast<int32_t>(a0);
        uint32_t uix = bitwise_cast<uint32_t>(ix& 0x7fffffff);
        /* 25+53 bit pi is good enough for medium size */
        if (uix < 0x4dc90fdb) {  /* |x| ~< 2^28*(pi/2), medium size */
          double fn = nearest(double(a0)*invpio2);
          return {quadrant(fn), (a0 - fn*pio2_1) - fn*pio2_1t};
        }
        auto [fn, x] =  eve::rem_pio2(double(a0));
        return {static_cast<float>(fn), static_cast<float>(x)};
      }
    }
    else
    {
      static_assert(std::is_floating_point_v<value_type_t<T>>, "rem_pio2 paramete is not IEEEValue");
      return {T{}, T{}}; 
    }
  }
}

#endif
