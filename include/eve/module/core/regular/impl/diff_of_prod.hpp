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
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/fms.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_finite.hpp>

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
      T cd = c * d;
      T err = fnma(c, d, cd);
      T dop = fms(a, b, cd);
     return if_else(is_finite(err), dop + err, dop);
   }

  template<floating_real_value T, floating_real_value U, floating_real_value V, floating_real_value W >
  EVE_FORCEINLINE auto diff_of_prod_(EVE_SUPPORTS(cpu_)
                                   , raw_type const &
                                   , const T& a
                                   , const U& b
                                   , const V& c
                                   , const W& d
                                   ) noexcept
  {
    return arithmetic_call(raw(diff_of_prod), a, b, c, d);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto dif_of_prod_(EVE_SUPPORTS(cpu_)
                                   , raw_type const &
                                   , const T& a
                                   , const T& b
                                   , const T& c
                                   , const T& d
                                   ) noexcept
  requires(has_native_abi_v<T>)
  {
    return fms(a, b, c*d);
  }
}
