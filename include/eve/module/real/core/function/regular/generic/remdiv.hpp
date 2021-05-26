//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/decorator.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_unordered.hpp>
#include <eve/function/trunc.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto
  remdiv_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires compatible_values<T, U>
  {
    using r_t = common_compatible_t<T, U>;
    if constexpr(has_native_abi_v<T>&& has_native_abi_v<U>)
    {
      auto d = trunc(div(a,b));
      if constexpr(floating_real_value<T>)
      {
        auto r = if_else(is_unordered(a, b) || is_infinite(a) || is_eqz(b)
                        , allbits
                        , if_else(is_eqz(a)
                                 , a
                                 , fnma(b, d, a)
                                 )
                        );
        return kumi::make_tuple( r_t(r), r_t(d) );
      }
      else
      {
        auto r = fnma(b, d, a);
        return kumi::make_tuple( r_t(r), r_t(d) );
      }
    }
    else return apply_over2(remdiv, r_t(a), r_t(b));
  }
}
