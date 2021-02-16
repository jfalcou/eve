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
#include <eve/function/lgamma.hpp>
#include <eve/function/exp.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<integral_value I, floating_value T>
  EVE_FORCEINLINE auto rising_factorial_(EVE_SUPPORTS(cpu_)
                                        , I n,  T x) noexcept
  {
//     if constexpr(has_native_abi_v<T>)
//     {
      using elt_t =  element_type_t<T>;
      auto nn = convert(n, as<elt_t>());
      return eve::exp(lgamma(x+nn)-lgamma(x));
//     }
//     else
//       return apply_over(rising_factorial, n, x);
  }
}
