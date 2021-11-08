//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/operators.hpp>
#include <eve/traits/common_compatible.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/promoted.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  //================================================================================================
  //== promoted case
  //================================================================================================
  template<real_value T,  real_value U>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(cpu_), promoted_type const &, T a, U b) noexcept
  {
    return arithmetic_call(promoted(mul), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(cpu_), promoted_type const &, T a, T b) noexcept
  requires has_native_abi_v<T>
  {
    using elt_t = element_type_t<T>;
    if constexpr(sizeof(elt_t) == 8)
    {
      return a*b;
    }
    else
    {
      return mul(upgrade_(a), upgrade_(b));
    }
  }
}
