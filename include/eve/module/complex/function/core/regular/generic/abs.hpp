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

#include <eve/concept/complex_value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/function/hypot.hpp>
#include <eve/function/pedantic/hypot.hpp>
#include <eve/function/complex/real.hpp>
#include <eve/function/complex/imag.hpp>

namespace eve::detail
{
  template<complex_value T>
  EVE_FORCEINLINE constexpr as_real<T> abs_(EVE_SUPPORTS(cpu_), T const &u) noexcept
  {
    return hypot(real(u), imag(u)
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, complex_value U>
  EVE_FORCEINLINE auto abs_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    auto t = mask_op( EVE_CURRENT_API{}, cond, eve::abs, t);
    return U(mask_op( t.val(), if_else(cond, t.der(), one);
  }
}
