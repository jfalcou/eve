//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/signnz.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE T negatenz_(EVE_SUPPORTS(cpu_), pedantic_type const &
                             , T const &a, T const &b) noexcept
  requires has_native_abi_v<T>
  {
    if constexpr( signed_value<T> )
    {
      return a*pedantic(signnz)(b);
    }
    else
    {
      return a;
    }
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto negatenz_(EVE_SUPPORTS(cpu_), pedantic_type const &
                                , T const &a, U const &b) noexcept
  requires std::same_as<element_type_t<T>, element_type_t<U>>
  {
    return arithmetic_call(pedantic(negatenz), a, b);
  }

}
