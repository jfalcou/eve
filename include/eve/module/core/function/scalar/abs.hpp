//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//================================================================================================== 
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_notand.hpp>
#include <eve/constant/mzero.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr T abs_(EVE_SUPPORTS(cpu_)
                                  , T const &a) noexcept
  {
    if constexpr(std::is_arithmetic_v<T>)
    {
      if constexpr(std::is_floating_point_v<T>) return bitwise_notand(Mzero<T>(),a);
      if constexpr(std::is_integral_v<T> && std::is_unsigned_v<T>)  return a;
      if constexpr(std::is_integral_v<T> && std::is_signed_v<T>)
      {
        using u_t = eve::detail::as_integer_t<T, unsigned>;
        u_t mask = a >> (sizeof(T)*8 - 1);
        return (a + mask) ^ mask;
      }
      else
      {
        static_assert(std::is_arithmetic_v<T>,
                      "[ eve::abs] - No support for logical values");
      }
    }
  }
}


#endif
