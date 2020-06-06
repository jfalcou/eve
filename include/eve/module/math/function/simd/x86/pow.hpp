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

#include <eve/detail/concepts.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/logical_andnot.hpp>
#include <eve/function/minus.hpp>

  // this implementation is better only if we are in  avx_ or greater
  template<floating_real_simd_value T>
  EVE_FORCEINLINE auto pow_(EVE_SUPPORTS(avx_), T a, T b) noexcept
  {
    if constexpr(has_native_abi_v<T> )
    {
      auto isinfb = is_infinite(b);
      auto nega    = is_negative(a);
      a =  if_else( a == Mone<T>() && isinfb , eve::one_, a);
      T    z       = pow_abs(a, b);
      z            = minus[logical_and(is_odd(b), nega)](z);
      auto invalid = logical_andnot(nega, logical_or(is_flint(b), is_infinite(b)));
      return if_else(invalid, eve::allbits_, z);
    }
    else
    {
      return apply_over(pow, a, b);
    }

  }
}
