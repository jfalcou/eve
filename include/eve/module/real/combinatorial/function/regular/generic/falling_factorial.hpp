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
#include <eve/function/convert.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/lgamma.hpp>
#include <eve/function/signgam.hpp>
#include <eve/function/rising_factorial.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<integral_value I, floating_value T>
  EVE_FORCEINLINE auto falling_factorial_(EVE_SUPPORTS(cpu_)
                                        , I n,  T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      using elt_t =  element_type_t<T>;
      auto nn = convert(n, as<elt_t>());
      //     auto fac = cospi(inc(nn));
 //      return if_else(is_lez(x)
//                     , fac*rising_factorial(n, -x)
      return signgam(inc(x))*signgam(inc(x-nn))*eve::exp(lgamma(inc(x))-lgamma(inc(x-nn)));
//      return if_else(is_eqz(nn), one, fac*rising_factorial(n, -x));
    }
    else
      return apply_over(falling_factorial, n, x);
  }
}
