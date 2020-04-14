//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IS_NLEZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IS_NLEZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/constant/zero.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_nlez_(EVE_SUPPORTS(cpu_)
                                                   , T const &a) noexcept
  {
    if constexpr(unsigned_value<T>)       return is_nez(a);
    if constexpr(native<T>)
    {
      if constexpr(scalar_value<T>)
      {
        if constexpr(integral_value<T>)      return is_gtz(a);
        else if constexpr(floating_value<T>) return is_gtz(a) || is_nan(a);
      }
      else                                   return is_not_less_equal(a, Zero(as(a)));
    }
    else                                     return apply_over(is_nlez, a);
  }
}

#endif
