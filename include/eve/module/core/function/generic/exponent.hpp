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
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/expobits_mask.hpp>
#include <eve/constant/maxexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>


namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr as_integer_t<T> exponent_(EVE_SUPPORTS(cpu_)
                                                     , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto z =  bit_and(Expobits_mask<T>(), a);
      if constexpr(scalar_value<T>)
      {
        if (is_not_finite(a)) return as_integer_t<T>(0);
        auto x = shr(z, Nbmantissabits<T>());
        return sub[is_nez(a)](x, Maxexponent<T>());
      }
      else
      {
        auto x = shr(z, Nbmantissabits<T>());
        return if_else(is_not_finite(a), eve::zero_, sub[is_nez(a)](x, Maxexponent<T>()));
      }
    }
    else return apply_over(exponent, a);
  }

}

