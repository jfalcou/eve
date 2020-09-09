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
#include <eve/function/regular.hpp>
#include <eve/platform.hpp>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto arg_(EVE_SUPPORTS(cpu_), D const &decorator, T const &a) noexcept
      requires(is_one_of<D>(types<regular_type, pedantic_type> {}))
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto z = if_else(is_negative(a), Pi(eve::as(a)), eve::zero_);
      if constexpr( platform::supports_nans && std::same_as<D, pedantic_type> )
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
      return apply_over(decorator(arg), a);
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto arg_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return arg(regular_type {}, a);
  }
}

