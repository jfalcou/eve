//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/derivative.hpp>
#include <eve/function/negabsmax.hpp>
#include <eve/function/sign.hpp>
#include <eve/module/real/core/function/diff/detail/minmax_kernel.hpp>

namespace eve::detail
{
  template<int N, typename T0, typename T1, typename... Ts>
  auto negabsmax_(EVE_SUPPORTS(cpu_), diff_type<N>
           , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    return -minmax_kernel<N>(eve::max, eve::sign, arg0, arg1, args...);
  }
}
