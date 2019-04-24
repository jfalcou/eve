//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NGEZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NGEZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp>
#include <eve/function/scalar/is_nan.hpp>
#include <eve/function/scalar/is_ltz.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto is_ngez_(EVE_SUPPORTS(cpu_), T const &a) noexcept
                            requires( as_logical_t<T>, Vectorizable<T> )
  {
    if constexpr(std::is_unsigned_v<T> || is_logical_v<T>)
      return False(as(a));
    else
    {
      if constexpr(std::is_floating_point_v<T>)
        return is_ltz(a).value() || is_nan(a).value();
      if constexpr(std::is_integral_v<T>)
        return is_ltz(a); 
    }
  }
}

#endif
