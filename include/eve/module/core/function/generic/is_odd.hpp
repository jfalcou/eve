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

#include <eve/detail/implementation.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/is_even.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/constant/one.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_odd_(EVE_SUPPORTS(cpu_)
                                                   , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        auto da = dec(a);
        return (a!= da) && is_even(da);
      }
      else if constexpr(scalar_value<T>) return (a & One(eve::as(a)));
      else                               return is_nez((a & One(eve::as(a))));
    }
    else return apply_over(is_odd, a);
  }
}

