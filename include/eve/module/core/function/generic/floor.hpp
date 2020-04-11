//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_FLOOR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_FLOOR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/trunc.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T floor_(EVE_SUPPORTS(cpu_)
                                    , T const &a0) noexcept
  {
    if constexpr(integral_real_value<T>) return a0;
    else if constexpr(native<T>)
    {
      T z = eve::trunc(a0);
      return dec[ z > a0 ](z);
    }
    else return apply_over(floor, a0);
  }
}

#endif
