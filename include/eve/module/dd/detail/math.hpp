//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/dd/regular/traits.hpp>
#include <eve/module/dd/detail/utilities.hpp>


namespace eve::detail
{

  //================================================================================================
  //  unary functions
  //================================================================================================
  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::exp_, Z const& z) noexcept
  {
    auto n = nearest(z);
    auto x = z - n;
    auto u = (((((((((((x +
                        156)*x + 12012)*x +
                      600600)*x + 21621600)*x +
                    588107520)*x + 12350257920)*x +
                  201132771840)*x + 2514159648000)*x +
                23465490048000)*x + 154872234316800)*x +
              647647525324800)*x + 1295295050649600;
    auto v = (((((((((((x -
                        156)*x + 12012)*x -
                      600600)*x + 21621600)*x -
                    588107520)*x + 12350257920)*x -
                  201132771840)*x + 2514159648000)*x -
                23465490048000)*x + 154872234316800)*x -
              647647525324800)*x + 1295295050649600;
    return pow(euler(as(z)), int(high(n)))*(u/v);
  }

//   //================================================================================================
//   //  Binary functions
//   //================================================================================================

//   EVE_FORCEINLINE auto
//   dd_binary_dispatch(eve::tag::pow_, auto const& z1, auto const& z2) noexcept
//   {
//     return z1 + z2;
//   }

}
