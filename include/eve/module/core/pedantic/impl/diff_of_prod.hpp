//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<floating_real_value T
           , floating_real_value U, floating_real_value V, floating_real_value W >
  EVE_FORCEINLINE auto diff_of_prod_(EVE_SUPPORTS(cpu_)
                                   , pedantic_type const &
                                   , const T& a
                                   , const U& b
                                   , const V& c
                                   , const W& d
                                   ) noexcept
{
  return arithmetic_call(pedantic(diff_of_prod), a, b, c, d);
}

  template<floating_real_value T>
  EVE_FORCEINLINE auto diff_of_prod_(EVE_SUPPORTS(cpu_)
                                   , pedantic_type const &
                                   , const T& a
                                   , const T& b
                                   , const T& c
                                   , const T& d
                                   ) noexcept
  requires(has_native_abi_v<T>)
  {
    T mcd = c * d;
    T err = pedantic(fma)(-c, d, mcd);
    T dop = pedantic(fms)(a, b, mcd);
    return if_else(is_finite(err), dop + err, dop);
  }
}
