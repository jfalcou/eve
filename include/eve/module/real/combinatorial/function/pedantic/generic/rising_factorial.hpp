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
#include <eve/function/exp.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/pedantic/lrising_factorial.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/signgam.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/exp.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/traits/common_compatible.hpp>
#include <type_traits>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE auto rising_factorial_(EVE_SUPPORTS(cpu_)
                                        , pedantic_type const &
                                        , T a,  T x) noexcept
  {
     if constexpr(has_native_abi_v<T>)
     {
       auto sgnrf = [](auto a ,  auto x)
         {
           auto sga = if_else(is_flint(a), one, signgam(a));
           auto sgapx = if_else(is_flint(a+x), one, signgam(a+x));
           return sga*sgapx;
         };
       auto lrn = pedantic(lrising_factorial)(a, x);
       return exp(lrn)*sgnrf(a, x);
     }
    else
      return apply_over(pedantic(rising_factorial), a, x);
  }
}
