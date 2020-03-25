//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BIT_NOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BIT_NOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_cast.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr T bit_not_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using b_t = as_integer_t<T, unsigned>;
      return bit_cast(~bit_cast(a,as_<b_t>()), as(a));
    }
    else
    {
      return ~a;
    }
  }
}

#endif
