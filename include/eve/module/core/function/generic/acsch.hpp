//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ACSCH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ACSCH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/asinh.hpp>
#include <eve/function/rec.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto acsch_(EVE_SUPPORTS(cpu_)
                                  , T const &x) noexcept
  {
    if constexpr(native<T>) return asinh(rec(x));
    else                    return apply_over(acsch, x);
  }
  
}

#endif
