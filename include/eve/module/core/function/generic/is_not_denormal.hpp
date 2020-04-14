//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IS_NOT_DENORMAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IS_NOT_DENORMAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_not_less.hpp>
#include <eve/function/logical_or.hpp>
#include <eve/constant/true.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_not_denormal_(EVE_SUPPORTS(cpu_)
                                                       , T const &a) noexcept
  {
    if constexpr(native<T>)
    {
      if constexpr(integral_value<T> || !platform::supports_denormals)
                                      return True(as(a));
      else                            return is_eqz(a) || is_not_less(eve::abs(a), Smallestposval(as(a)));
    }
    else                              return apply_over(is_not_denormal, a);
  }
}

#endif
