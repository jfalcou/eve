//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ASINPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ASINPI_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/asin.hpp>
#include <eve/function/inpi.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto asinpi_(EVE_SUPPORTS(cpu_)
                                  , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>) return inpi(asin(a));
    else                    return apply_over(asinpi, a);
  }

}

#endif
