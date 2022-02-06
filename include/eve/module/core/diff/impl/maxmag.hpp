//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/maxmag.hpp>
#include <eve/module/core/diff/detail/minmax_kernel.hpp>
#include <eve/module/core/constant/one.hpp>

namespace eve::detail
{
  template<int N, typename T0, typename T1, typename... Ts>
  auto maxmag_(EVE_SUPPORTS(cpu_), diff_type<N>
           , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    auto o = [](auto m){return eve::one(as(m)); };
    return minmax_kernel<N>(eve::maxmag, o, arg0, arg1, args...);
  }
}
