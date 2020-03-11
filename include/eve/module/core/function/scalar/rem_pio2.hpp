//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
#include <eve/constant/twoopi.hpp>
#include <eve/function/abs.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto rem_pio2_(EVE_SUPPORTS(cpu_)
                                             , T const &a0) noexcept
  requires(std::tuple<T, T, T>, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      using r_t =  std::tuple<T, T, T>; 
      if constexpr(std::is_same_v<T, double>)
      {
        if (a0 == Inf<T>()) return r_t(Zero<T>(), Nan<T>(), Nan<T>());
        T y[2];
        std::int32_t n = __ieee754_rem_pio2(a0, y);
        return r_t(static_cast<T>(n&std::int32_t(3)), y[0], y[1]);
      }
      else if constexpr(std::is_same_v<T, float>)
      {
        if (a0 == Inf<T>()) return r_t(Zero<T>(), Nan<T>(), Nan<T>());
        // This is the musl way
        // pio2_1:   first 25 bits of pi/2
        // pio2_1t:  pi/2 - pio2_1
        //
        static const double
          pio2_1  = 1.57079631090164184570e+00, /* 0x3FF921FB, 0x50000000 */
          pio2_1t = 1.58932547735281966916e-08; /* 0x3E5110b4, 0x611A6263 */
        if (abs(a0) < 4.2166e+08)/* |x| ~< 2^28*(pi/2), medium size */
        {
          /* 25+53 bit pi is good enough for medium size */
          double fn = nearest(double(a0)*Twoopi<double>());
          return {static_cast<float>(quadrant(fn)), static_cast<float>((a0 - fn*pio2_1) - fn*pio2_1t), 0.0f};
        }
        auto [fn, x, dx] =  eve::rem_pio2(double(a0));
        float fx = static_cast<float>(x);
        return {static_cast<float>(fn), fx, 0.0f };
      }
    }
    else
    {
      static_assert(std::is_floating_point_v<value_type_t<T>>, "rem_pio2 parameter is not IEEEValue");
      return {T{}, T{}, T{}}; 
    }
  }
}

#endif
