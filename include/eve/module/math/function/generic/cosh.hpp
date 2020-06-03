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
#include <eve/function/average.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/none.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/log_2.hpp>
#include <type_traits>
#include <eve/detail/apply_over.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cosh_(EVE_SUPPORTS(cpu_)
                                     , T a0) noexcept
  {
    //////////////////////////////////////////////////////////////////////////////
    // if x = abs(a0) according x < Threshold e =  exp(x) or exp(x/2) is
    // respectively computed
    // *  in the first case cosh (e+rec(e))/2
    // *  in the second     cosh is (e/2)*e (avoiding undue overflow)
    // Threshold is Maxlog - Log_2
    //////////////////////////////////////////////////////////////////////////////
    if constexpr(scalar_value<T>)
    {
      if (is_eqz(a0)) return One(as(a0));
    }
    if constexpr(has_native_abi_v<T>)
    {
      auto ovflimitmln2 =  Ieee_constant<T,0X42AF5DC0U, 0X408628B76E3A7B61LL >(); //87.68310404,  709.08956571282405469058276787854
      auto x = eve::abs(a0);
      if constexpr(scalar_value<T>)
      {
        if (x >= ovflimitmln2)
        {
          auto w = exp(x*Half<T>());
          auto t = Half<T>()*w;
          t *= w;
          return t;
        }
        auto t = exp(x);
        return (x > T(22.0f)) ? t*Half<T>() : average(t, rec(t));
      }
      else
      {
        auto t = exp(x);
        auto invt = if_else(x > T(22.0f), eve::zero_, rec(t));
        auto c = average(t, invt);
        auto test = x <  ovflimitmln2;
        if (eve::all(test)) return c;
        auto w = exp(x*Half<T>());
        t = Half<T>()*w;
        t *= w;

        c = if_else(test, c, t);
        return c;
      }
    }
    else return apply_over(cosh, a0);
  }
}

