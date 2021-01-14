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

#include <eve/function/nthroot.hpp>

#include <eve/function/rec.hpp>
#include <eve/function/nthroot.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_real_value T, value N>
  EVE_FORCEINLINE constexpr T nthroot_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T x, N n) noexcept
  {
    using elt_t = element_type_t<T>;
    auto tn = convert(n, as<elt_t>());
    return nthroot(x, n)*rec(x*tn);
  }
}
