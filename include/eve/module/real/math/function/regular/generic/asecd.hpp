//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/asec.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/regular.hpp>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto asecd_(EVE_SUPPORTS(cpu_), D const &decorator, T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return radindeg(decorator(eve::asec)(a));
    }
    else
    {
      return apply_over(decorator(eve::asecd), a);
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto asecd_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return asecd(regular_type(), a);
  }
}

