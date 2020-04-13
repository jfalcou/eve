//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IS_EQZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IS_EQZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/is_less.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_eqz_(EVE_SUPPORTS(cpu_)
                                                   , T const &a) noexcept
  {
    if constexpr(native<T>)
    {
      if constexpr(is_logical_v<T>) return logical_not(a);
      if constexpr(scalar_value<T>) return !a;
      else                          return is_equal(a,  Zero(as(a)));
    }
    else                            return apply_over(is_eqz, a);
  }
}

#endif
