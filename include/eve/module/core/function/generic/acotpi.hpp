//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ACOTPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ACOTPI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/acot.hpp>
#include <eve/function/inpi.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto acotpi_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  requires(T, Floating<value_type_t<T>>)
  {
    return inpi(acot(a0)); 
  }

}

#endif
