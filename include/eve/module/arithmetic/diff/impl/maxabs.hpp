//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/derivative.hpp>
#include <eve/function/maxabs.hpp>
#include <eve/function/sign.hpp>
#include <eve/module/arithmetic/diff/detail/minmax_kernel.hpp>

namespace eve::detail
{
  template<int N, typename T0, typename T1, typename... Ts>
  auto maxabs_(EVE_SUPPORTS(cpu_), diff_type<N>
           , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    return minmaxabs_kernel<N>(eve::maxabs, eve::sign, arg0, arg1, args...);
  }
}
