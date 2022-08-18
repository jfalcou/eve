//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/module/core/regular/minabs.hpp>
#include <eve/module/core/regular/minus.hpp>

namespace eve::detail
{

template<typename  ...Ts>
EVE_FORCEINLINE auto
negminabs_(EVE_SUPPORTS(cpu_), Ts... args)
{
  return minus(minabs(args...));
}

template<conditional_expr C, typename  ...Ts>
EVE_FORCEINLINE auto
negminabs_(EVE_SUPPORTS(cpu_), C const & c, Ts... args)
{
  return minus[c](minabs[c](args...));
}

}
