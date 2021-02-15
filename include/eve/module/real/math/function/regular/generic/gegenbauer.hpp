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

#include <eve/concept/value.hpp>
#include <eve/function/add.hpp>
#include <eve/function/all.hpp>
#include <eve/function/any.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/eps.hpp>
#include <eve/traits/common_compatible.hpp>
#include <utility>
#include <iostream>

namespace eve::detail
{

  template<integral_scalar_value I, floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto gegenbauer_(EVE_SUPPORTS(cpu_), I n, U lambda, T x) noexcept
  requires compatible_values<T, U>
  {
    auto p0 = one(as(x));
    if(is_eqz(n)) return p0;

    auto y0 = p0;
    auto y1 = 2*lambda*x;

    auto yk = y1;
    auto k = 2;
    auto k_max = n*inc(eps(as(x)));
    auto gamma = 2*dec(lambda);
    auto test = k < k_max;
    while(any(test))
    {
      yk = if_else(test, fms((2+gamma/k)*x, y1, inc(gamma/k)*y0), yk);
      y0 = y1;
      y1 = yk;
      ++k;
      test = k < k_max;
    }
    return yk;
  }

  template<integral_simd_value I, floating_real_scalar_value T>
  EVE_FORCEINLINE auto gegenbauer_(EVE_SUPPORTS(cpu_), I nn, T x) noexcept
  {
    using f_t = as_wide_t<T, cardinal_t<I>>;
    return gegenbauer(nn, f_t(x));
  }

  template<integral_simd_value I, floating_real_simd_value T, floating_real_simd_value U>
  EVE_FORCEINLINE auto gegenbauer_(EVE_SUPPORTS(cpu_), I nn, U lambda, T x) noexcept
  requires index_compatible_values<I, T> && compatible_values<T, U>
  {
    using v_t =  common_compatible_t<T, U>;
    return gegenbauer(nn, v_t(lambda), v_t(x));
  }


  template<integral_simd_value I, floating_real_simd_value T>
  EVE_FORCEINLINE auto gegenbauer_(EVE_SUPPORTS(cpu_), I nn, T lambda, T x) noexcept
  requires index_compatible_values<I, T>
  {
    if (has_native_abi_v<T>)
    {
      using elt_t = element_type_t<T>;
      auto p0 = one(as(x));
      if(all(is_eqz(nn))) return p0;
      auto n =  convert(nn, as<elt_t>());
      auto y0 = p0;
      auto y1 = 2*lambda*x;

      auto yk = y1;
      auto k = T(2);
      auto k_max = n*inc(eps(as(x)));
      auto gamma = 2*dec(lambda);
      auto test = k < k_max;
      while(any(test))
      {
        yk = if_else(test, fms((2+gamma/k)*x, y1, inc(gamma/k)*y0), yk);
        y0 = y1;
        y1 = yk;
        k = inc(k);
        test = k < k_max;
      }
      return yk;
    }
    else
      return apply_over(gegenbauer, nn, x);
  }
}
