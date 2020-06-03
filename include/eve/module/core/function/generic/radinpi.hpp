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

#include <eve/concept/value.hpp>
#include <eve/constant/invpi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto radinpi_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return Invpi(as(a)) * a;
    else
      return apply_over(radinpi, a);
  }
}

