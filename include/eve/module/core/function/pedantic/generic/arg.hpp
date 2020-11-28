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
#include <eve/constant/allbits.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/platform.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto arg_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto z = if_else(is_negative(a), pi(eve::as(a)), eve::zero);
      if constexpr( platform::supports_nans)
      {
        return if_else(is_nan(a), eve::allbits, z);
      }
      else
      {
        return z;
      }
    }
    else
    {
      return apply_over(pedantic_type(arg), a);
    }
  }
}
