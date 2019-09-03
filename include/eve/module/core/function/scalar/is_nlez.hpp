//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NLEZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NLEZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/scalar/is_nan.hpp>
#include <eve/function/scalar/is_nez.hpp>
#include <eve/function/scalar/is_gtz.hpp>
#include <eve/constant/false.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_nlez_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr(std::is_unsigned_v<T>)
      return is_nez(a);
    else
    {
      if constexpr(std::is_floating_point_v<T>) return is_gtz(a).value() || is_nan(a).value();
      if constexpr(std::is_integral_v<T>) return is_gtz(a);
    }
  }

}

#endif
