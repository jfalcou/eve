//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ATAN2PI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ATAN2PI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/atan2.hpp>
#include <eve/function/inpi.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto atan2pi_( EVE_SUPPORTS(cpu_)
                                       , T const &a0
                                       , T const &a1
                                       ) noexcept
  requires(T, floating<T>)
  {
    return inpi(atan2(a0, a1));
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto atan2pi_( EVE_SUPPORTS(cpu_)
                                       , pedantic_type const &
                                       , T a0
                                       , T a1
                                       ) noexcept
  requires(T, floating<T>)
  {
    return inpi(pedantic_(atan2)(a0, a1));
  }
}

#endif
