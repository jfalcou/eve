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

#include <eve/function/exp_int.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/dec.hpp>

namespace eve::detail
{

  template<floating_real_value T, integral_real_value N>
  EVE_FORCEINLINE constexpr T exp_int_(EVE_SUPPORTS(cpu_)
                                  , derivative_type<1> const &
                                  , N const &n
                                  , T const &x) noexcept
  {
    using elt_t = element_type_t<T>;
    auto nf = convert(dec(n), as<elt_t>());
    return -exp_int(nf, x);
  }
}
