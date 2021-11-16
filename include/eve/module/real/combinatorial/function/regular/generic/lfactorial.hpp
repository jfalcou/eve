//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/all.hpp>
#include <eve/function/factorial.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/lgamma.hpp>

#include <type_traits>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<integral_value T>
  EVE_FORCEINLINE auto lfactorial_(EVE_SUPPORTS(cpu_), T n) noexcept
  {
    EVE_ASSERT(eve::all(is_flint(n)), "lfactorial : some entry elements are not flint");
    EVE_ASSERT(eve::all(is_gez(n) )  , "lfactorial : some entry elements are not positive");
    if constexpr(has_native_abi_v<T>)
    {
      auto r = eve::log(factorial(n));
      if (eve::all(n < 171)) return r;
      else
      {
        return if_else(n < 171, r, eve::lgamma(float64(inc(n))));
      }
    }
    else
      return apply_over(lfactorial, n);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto lfactorial_(EVE_SUPPORTS(cpu_), T n) noexcept
  {
    EVE_ASSERT(eve::all(is_flint(n)), "lfactorial : some entry elements are not flint");
    EVE_ASSERT(eve::all(is_gez(n) )  , "lfactorial : some entry elements are not positive");
    if constexpr(has_native_abi_v<T>)
    {
      using elt_t =  element_type_t<T>;
      auto max = std::same_as<elt_t, double> ? 171 : 35;
      auto r = eve::log(factorial(n));
      if (eve::all(n < max)) return r;
      else
        return if_else(n < max, r, lgamma(inc(n)));
    }
    else
      return apply_over(lfactorial, n);
  }
}
