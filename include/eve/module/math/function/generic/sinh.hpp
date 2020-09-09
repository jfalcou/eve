//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/all.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/div.hpp>    // -> put in wide
#include <eve/function/fnma.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/half.hpp>
#include <type_traits>
#include <eve/detail/apply_over.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sinh_(EVE_SUPPORTS(cpu_)
                                     , T a0) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      if (is_eqz(a0)) return a0;
    }

    if constexpr(has_native_abi_v<T>)
    {
      T ovflimit =  Ieee_constant<T,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384
      T x = eve::abs(a0);

      if constexpr(scalar_value<T>)
      {
        T h = (a0 > T(0)) ? T(1) : T(-1);
        if (x >= ovflimit)
        {
          T w = exp(x*half(eve::as<T>()));
          T t = half(eve::as<T>())*w;
          t *= w;
          return t*h;
        }
        h*= half(eve::as<T>());
        T t = expm1(x);
        T inct = inc(t);
        T u = t/inct;
        T s = h*(fnma(t, u, t)+t);
        return s;
      }
      else
      {
        auto h = if_else( is_gtz(a0), One<T>(), eve::mone_);
        auto t = expm1(x);
        auto inct = inc(t);
        auto u = t/inct;
        auto z =  fnma(t, u, t);
        auto s = half(eve::as<T>())*h*(z+t);

        s = if_else (is_eqz(a0), a0,  s);
        auto test = x <  ovflimit;
        if (eve::all(test)) return s;

        auto w = exp(x*half(eve::as<T>()));
        t = half(eve::as<T>())*w;
        t *= w;

        return if_else(test, s, t*h);
      }
    }
    else
    {
      return apply_over(sinh, a0);
    }
  }
}

