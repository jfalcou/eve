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
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/lrising_factorial.hpp>
#include <eve/function/srising_factorial.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/exp.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/traits/common_compatible.hpp>
#include <type_traits>


namespace eve::detail
{
  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE auto rising_factorial_(EVE_SUPPORTS(cpu_)
                                        , I n,  T x) noexcept
  {
    if constexpr(integral_simd_value<I>)
    {
      using elt_t = element_type_t<T>;
      using r_t = as_wide_t<elt_t, cardinal_t<I>>;
      auto nn = convert(n, as(elt_t()));
      return rising_factorial(nn, r_t(x));
    }
    else if  constexpr(integral_scalar_value<I>)
    {
      return rising_factorial(T(n), x);
    }
    else
    {
      using r_t = common_compatible_t<I, T>;
      return rising_factorial(r_t(n), r_t(x));
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto rising_factorial_(EVE_SUPPORTS(cpu_)
                                        , T n,  T x) noexcept
  {
     if constexpr(has_native_abi_v<T>)
     {
       auto r = nan(as(x));
       auto xeqz = is_eqz(x);
       auto xeqminf = x == minf(as(x));
       r = if_else(xeqz, one, if_else(xeqminf, zero, x));
       auto done =  is_nan(x)|| xeqz || xeqminf;
       auto tmp = lrising_factorial(n, x); 
       return if_else(done, r, eve::exp(tmp)); //*srising_factorial(n, x));
     }
    else
      return apply_over(rising_factorial, n, x);
  }
}
