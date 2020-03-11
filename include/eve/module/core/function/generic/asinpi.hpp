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

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/asin.hpp>
#include <eve/function/inpi.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto asinpi_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  requires(T, behave_as<floating_point,T>)
  {
    return inpi(asin(a0));
  }

}

#endif
