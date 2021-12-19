//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/cosd.hpp>
#include <eve/function/secpi.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_not_flint.hpp>
#include <eve/function/rec.hpp>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto secd_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr( std::is_same_v<D, quarter_circle_type> )
      {
        return rec(D()(cosd)(a0));
      }
      auto a0_180 = div_180(a0);
      auto test   = is_not_flint(a0_180) && is_flint(a0_180+mhalf(eve::as(a0_180)));
      if constexpr( scalar_value<T> ) // early return for nans in scalar case
      {
        if( test ) return nan(eve::as<T>());
      }
      auto tmp = D()(secpi)(a0_180);
      if constexpr( scalar_value<T> ) return tmp;
      return if_else(test, eve::allbits, tmp);
    }
    else
      return apply_over(D()(secd), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto secd_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    return secd(regular_type(), a0);
  }

}
