//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ACOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ACOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/rec.hpp>
#include <eve/module/core/detail/generic/atan_kernel.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto acot_(EVE_SUPPORTS(cpu_)
                                      , T const &a) noexcept
  {
    if constexpr(native<T>)
    {
      T x  = eve::abs(a);
      return bit_xor(atan_kernel(rec(x), x), bitofsign(a));
    }
    else return apply_over(acot, a);
  }
}

#endif
