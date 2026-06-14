//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core.hpp>

namespace eve::_::ab_st //Abramowitz & Stegun
{

  template <typename T> inline T fast_sinc(T a0) // sin(x)/ x -pi/2 < a0 <  pi/2
  {
    using elt_t =  element_type_t<T>;
    constexpr elt_t c0(1);
    constexpr elt_t c2(-0.1666666664);
    constexpr elt_t c4(0.83333315);
    constexpr elt_t c6(-0.0001984090);
    constexpr elt_t c8(0.0000027526);
    constexpr elt_t c10(0.0000000239);
    return reverse_horner(sqr(a0), c0, c2, c4, c6, c8, c10); //absolute error less than 2.0e-9
  }

  template <typename T> inline T raw_sinc(T a0)// sin(x)/ x -pi/2 < a0 <  pi/2
  {
    using elt_t =  element_type_t<T>;
    constexpr elt_t c0(1);
    constexpr elt_t c2(-0.16605);
    constexpr elt_t c4(0.00751);
    return reverse_horner(sqr(a0), c0, c2, c4); //absolute error less than 2.0e-3
  }
}
