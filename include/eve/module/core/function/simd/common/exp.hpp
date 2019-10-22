//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_EXP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_EXP_HPP_INCLUDED
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/module/core/detail/generic/exp_kernel.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto exp_(EVE_SUPPORTS(cpu_)
                                     , const T &xx) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
    const T Maxlog  =  Ieee_constant<T, 0x42b0c0a5U, 0x40862e42fefa39efULL>();
    const T Minlog  =  Ieee_constant<T, 0xc2b0c0a5U, 0xc086232bdd7abcd2ULL>(); 
    T c = exp_kernel(xx); 
    c = if_else(is_less_equal(xx, Minlog), eve::zero_, c);
    c = if_else(is_greater_equal(xx, Maxlog), Inf<T>(), c);
    if constexpr(eve::platform::supports_nans)
      return if_else(is_nan(xx), xx, c);
    else
      return c;
  }
}

#endif
