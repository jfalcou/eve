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
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_not_greater_equal.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/traits/common_compatible.hpp>

#include <type_traits>

namespace eve::detail
{

template<typename  ...Ts>
EVE_FORCEINLINE auto
negabsmax_(EVE_SUPPORTS(cpu_), Ts... args)
{
  return minus(absmax(args...));
}

template<conditional_expr C, typename  ...Ts>
EVE_FORCEINLINE auto
negabsmax_(EVE_SUPPORTS(cpu_), C const & c, Ts... args)
{
  return minus[c](absmax[c](args...));
}

}
