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
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/all.hpp>
#include <eve/function/pow.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/nearest.hpp>

#include <type_traits>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<unsigned_value N, floating_value T,  value U>
  EVE_FORCEINLINE auto fibonacci_(EVE_SUPPORTS(cpu_), N n, T a, U b) noexcept
  requires compatible_values<U, T>
  {
    return indexed_call(fibonacci, n, a, b);
  }

  template< unsigned_value N, floating_value T>
  EVE_FORCEINLINE auto fibonacci_(EVE_SUPPORTS(cpu_), N n, T a, T b) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t =  element_type_t<T>;
      using eli_t =  as_integer_t<elt_t, unsigned>;
      constexpr elt_t gold      =  1.61803398874989484820458683436563811772030917980575;
      constexpr elt_t goldbar   = -0.61803398874989484820458683436563811772030917980575;
      constexpr elt_t oneosqrt5 =  0.4472135954999579392818347337462552470881236719223;
      auto nm1 = to_<eli_t>((n));
      auto c2 = fms(T(gold), a, b)*oneosqrt5;
      auto c1 = a-c2;
      auto f = fma(c1, pow(T(gold), nm1), c2*pow(T(goldbar), nm1));
      return if_else(is_flint(a) && is_flint(b), nearest(f), f);
    }
    else
      return apply_over(fibonacci, n, a, b);
  }
}
