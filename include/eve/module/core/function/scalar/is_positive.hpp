//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_POSITIVE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_POSITIVE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_positive_(EVE_SUPPORTS(cpu_)
                                                        , T const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using si_t = eve::detail::as_integer_t<T, signed>; 
      return as_logical_t<T>(bitwise_cast<si_t>(a) >= si_t(0));
    }
    else if constexpr(std::is_signed_v<T>)
      return a >= T(0);
    else
      return True(as(a)); 
  }
 
}

#endif
