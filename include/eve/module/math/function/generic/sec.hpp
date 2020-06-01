//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_MATH_FUNCTION_GENERIC_SEC_HPP_INCLUDED
#define EVE_MODULE_MATH_FUNCTION_GENERIC_SEC_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/rec.hpp>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto sec_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return rec(D()(eve::cos)(a0));
    }
    else
    {
      return apply_over(D()(sec), a0);
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sec_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return rec(eve::cos(a0));
    }
    else
    {
      return apply_over(sec, a0);
    }
  }

}

#endif
