//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/special/regular/factorial.hpp>
#include <eve/module/special/regular/log_abs_gamma.hpp>

namespace eve::detail
{

template<integral_value T>
EVE_FORCEINLINE auto
lfactorial_(EVE_SUPPORTS(cpu_), T n) noexcept
{
  EVE_ASSERT(eve::all(is_flint(n)), "lfactorial : some entry elements are not flint");
  EVE_ASSERT(eve::all(is_gez(n)), "lfactorial : some entry elements are not positive");
  if constexpr( has_native_abi_v<T> )
  {
    auto r = eve::log(factorial(n));
    if( eve::all(n < 171) ) return r;
    else { return if_else(n < 171, r, eve::log_abs_gamma(float64(inc(n)))); }
  }
  else return apply_over(lfactorial, n);
}

template<floating_real_value T>
EVE_FORCEINLINE auto
lfactorial_(EVE_SUPPORTS(cpu_), T n) noexcept
{
  EVE_ASSERT(eve::all(is_flint(n)), "lfactorial : some entry elements are not flint");
  EVE_ASSERT(eve::all(is_gez(n)), "lfactorial : some entry elements are not positive");
  if constexpr( has_native_abi_v<T> )
  {
    using elt_t        = element_type_t<T>;
    constexpr auto max = std::same_as<elt_t, double> ? 171 : 35;
    auto           r   = eve::log(factorial(n));
    if( eve::all(n < max) ) return r;
    else return if_else(n < max, r, log_abs_gamma(inc(n)));
  }
  else return apply_over(lfactorial, n);
}
}
