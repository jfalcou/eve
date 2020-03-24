//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NGEZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NGEZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/constant/false.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_ngez_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr(std::is_unsigned_v<T>) { return False<T>(); }
    else
    {
      if constexpr(std::is_floating_point_v<T>)
        return is_ltz(a) || is_nan(a);
      else
        return is_ltz(a);
    }
  }

  template<typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_ngez_(EVE_SUPPORTS(cpu_),
                                                     logical<T> const &a) noexcept
  {
    return False(as(a));
  }
}

#endif
