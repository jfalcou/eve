//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NGEZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NGEZ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/scalar/is_nan.hpp>
#include <eve/function/scalar/is_ltz.hpp>
#include <eve/constant/false.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_ngez_(EVE_SUPPORTS(cpu_)
                                                    , T const &a) noexcept
  {
    if constexpr(std::is_unsigned_v<T>)
      return False(as(a));
    else
    {
      if constexpr(std::is_floating_point_v<T>) return is_ltz(a).value() || is_nan(a).value();
      if constexpr(std::is_integral_v<T>) return is_ltz(a); 
    }
  }
  

  EVE_FORCEINLINE constexpr bool is_ngez_(EVE_SUPPORTS(cpu_)
                                        , bool const &a) noexcept
  {
    return false;
  }

}

#endif
