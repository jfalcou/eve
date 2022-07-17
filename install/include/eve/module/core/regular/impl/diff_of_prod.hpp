//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U, floating_real_value V, floating_real_value W >
  EVE_FORCEINLINE auto diff_of_prod_(EVE_SUPPORTS(cpu_)
                                   , const T& a
                                   , const U& b
                                   , const V& c
                                   , const W& d
                                   ) noexcept
  {
    return arithmetic_call(diff_of_prod, a, b, c, d);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto diff_of_prod_(EVE_SUPPORTS(cpu_)
                                   , const T& a
                                   , const T& b
                                   , const T& c
                                   , const T& d
                                   ) noexcept
  requires(has_native_abi_v<T>)
  {
    return a*b-c*d;
  }
}
