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
#include <eve/constant/inf.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/module/real/math/detail/generic/rem2.hpp>
#include <eve/module/real/math/detail/generic/trig_finalize.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cotpi_(EVE_SUPPORTS(cpu_), restricted_type const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) )
          return bit_or(a0, inf(eve::as(a0)));
        auto x = abs(a0);
        if( is_not_less_equal(x, T(0.25)) )
          return nan(eve::as<T>());
        return rec(tancot_eval(pi(eve::as<T>()) * a0));
      }
      else
      {
        auto x = eve::abs(a0);
        return if_else(
            is_eqz(a0),
            bit_or(a0, inf(eve::as(a0))),
            if_else(is_not_less_equal(x, T(0.25)), eve::allbits, rec(tancot_eval(pi(eve::as<T>()) * a0))));
      }
    }
    else
      return apply_over(restricted(cotpi), a0);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////
  // medium,  big,  small
  template<decorator D, floating_real_value T>
  EVE_FORCEINLINE constexpr auto cotpi_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) )
          return bit_or(a0, inf(eve::as(a0)));
        if( is_not_finite(a0) || is_flint(a0) )
          return nan(eve::as<T>());
      }
      auto x = abs(a0);
      if constexpr( simd_value<T> )
      {
        x = if_else(is_not_finite(a0) || is_flint(x), eve::allbits, x);
      }
      auto [fn, xr, dxr] = rem2(x);
      return cot_finalize(a0 * pi(eve::as<T>()), quadrant(fn), xr, dxr);
    }
    else
      return apply_over(D()(cotpi), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto cotpi_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto x = abs(a0);
      if( all(eve::abs(x) <= T(0.25)) )
        return restricted(cotpi)(a0);
      else
        return big(cotpi)(a0);
    }
    else
      return apply_over(cotpi, a0);
  }
}

