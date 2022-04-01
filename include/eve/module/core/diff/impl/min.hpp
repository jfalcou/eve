//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/diff/detail/minmax_kernel.hpp>
#include <eve/module/core/constant/one.hpp>

namespace eve::detail
{
  template<int N, typename T0, typename T1, typename... Ts>
  auto min_(EVE_SUPPORTS(cpu_), diff_type<N>
           , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    auto o = [](auto m){return eve::one(as(m)); };
    return minmax_kernel<N>(eve::min, o, arg0, arg1, args...);
  }

  template<int N, conditional_expr C, typename T0, typename T1, typename... Ts>
  auto min_(EVE_SUPPORTS(cpu_), C const & cond, diff_type<N>
           , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    return mask_op(  cond, diff_nth<N>(eve::min), arg0, arg1, args...);
  }
}
