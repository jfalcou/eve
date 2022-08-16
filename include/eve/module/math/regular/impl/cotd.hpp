//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/cotpi.hpp>
#include <eve/module/math/regular/deginrad.hpp>
#include <eve/module/math/regular/div_180.hpp>

namespace eve::detail
{

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
cotd_(EVE_SUPPORTS(cpu_), quarter_circle_type const&, T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( scalar_value<T> )
    {
      if( is_eqz(a0) ) return bit_or(a0, inf(eve::as(a0)));
      auto x = abs(a0);
      if( is_not_less_equal(x, T(45)) ) return nan(eve::as<T>());
      return rec(tancot_eval(deginrad(a0)));
    }
    else
    {
      auto x = eve::abs(a0);
      return if_else(
          is_eqz(a0),
          bit_or(a0, inf(eve::as(a0))),
          if_else(is_not_less_equal(x, T(45)), eve::allbits, rec(tancot_eval(deginrad(a0)))));
    }
  }
  else return apply_over(quarter_circle(cotd), a0);
}

template<floating_real_value T, decorator D>
EVE_FORCEINLINE constexpr auto
cotd_(EVE_SUPPORTS(cpu_), D const&, T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto x      = eve::abs(a0);
    T    a0_180 = div_180(a0);
    auto test   = is_nez(a0_180) && is_flint(a0_180);
    if constexpr( scalar_value<T> ) // early return for nans in scalar case
    {
      if( test ) return nan(eve::as<T>());
    }
    else { x = if_else(test, eve::allbits, x); }
    auto [fn, xr, dxr] = rem180(x);
    return cot_finalize(deginrad(a0), fn, xr, dxr);
  }
  else return apply_over(D()(cotd), a0);
}

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
cotd_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto x = abs(a0);
    if( eve::all(eve::abs(x) <= T(45)) ) return quarter_circle(cotd)(a0);
    else return big(cotd)(a0);
  }
  else return apply_over(cotd, a0);
}
}
