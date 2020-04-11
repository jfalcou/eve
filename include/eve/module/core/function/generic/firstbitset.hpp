//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_FIRSTBITSET_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_FIRSTBITSET_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_not.hpp>
#include <eve/function/inc.hpp>
#include <eve/constant/one.hpp>
#include <eve/forward.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<integral_real_value T>
  EVE_FORCEINLINE constexpr T firstbitset_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  {
    if constexpr(native<T>) return a0 & (inc(~a0));
    else                    return apply_over(firstbitset, a0);
  }

}

#endif
