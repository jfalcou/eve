//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ATANPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ATANPI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/atan.hpp>
#include <eve/function/inpi.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto atanpi_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  {
    return inpi(atan(a0));
  }

}

#endif
