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

#include <eve/function/minmag.hpp>
#include <eve/function/derivative.hpp>
#include <eve/module/real/core/function/derivative/detail/minmax_kernel.hpp>

namespace eve::detail
{
  template<int N, typename T0, typename T1, typename... Ts>
  auto minmag_(EVE_SUPPORTS(cpu_), derivative_type<N>
           , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    return minmax_kernel<N>(eve::minmag, arg0, arg1, args...);
  }
}
