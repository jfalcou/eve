//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ASECH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ASECH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/acosh.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto asech_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  requires(T, floating_point<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      return acosh(rec(a0));
    }
     else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::asech scalar ] - type is not an IEEEValue"); 
    }
  }
 
}

#endif
