//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_CONJ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_CONJ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/sqr.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr T conj_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr(!std::is_floating_point_v<value_type_t<T>>)
    {
      EVE_ASSERT(std::is_floating_point_v<value_type_t<T>>, "[eve::conj] -this function is not to be used with integral types");
      return {}; 
    }
    else
      return a;
  }
}

#endif
