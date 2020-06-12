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
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/cotpi.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/div_180.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_flint.hpp>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto cotd_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      using elt_t = element_type_t<T>;
      T a0_180;
      if constexpr(std::is_same_v<elt_t, float>)
      {
        a0_180 =  single_(div_180(double_(a0))); // better precision in float
      }
      else
      {
        a0_180 = div_180(a0);
      }
      auto test   = is_nez(a0_180) && is_flint(a0_180);
      if constexpr( scalar_value<T> ) // early return for nans in scalar case
      {
        if( test ) return Nan<T>();
      }
      auto tmp = D()(cotpi)(a0_180);
      if constexpr( scalar_value<T> ) return tmp;
      return if_else(test, eve::allbits_, tmp);
    }
    else
      return apply_over(D()(cotd), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cotd_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    return cotd(regular_type(), a0);
  }

}
