//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/regular/minabs.hpp>
#include <eve/module/core/regular/sign.hpp>
#include <eve/module/core/diff/detail/minmax_kernel.hpp>

namespace eve::detail
{
  template<int N, typename T0, typename T1, typename... Ts>
  auto negminabs_(EVE_SUPPORTS(cpu_), diff_type<N>
           , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    return -minmaxabs_kernel<N>(eve::minabs, eve::sign, arg0, arg1, args...);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  // -----------------------------------------------------------------------------------------------
  template<int N, conditional_expr C, typename T, typename... Ts>
  EVE_FORCEINLINE auto negminabs_(EVE_SUPPORTS(cpu_), C const &cond, diff_type<N> const &
                               , T const &t, Ts ... ts ) noexcept
  {
    return mask_op(  cond, eve::diff_nth<N>(eve::negminabs), t, ts...);
  }
}
