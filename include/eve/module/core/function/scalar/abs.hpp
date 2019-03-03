//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
  EVE_FORCEINLINE constexpr auto abs_(EVE_SUPPORTS(cpu_)
                                  , T const &a) noexcept requires( T, Arithmetic<T>)
  {

    if constexpr(std::is_floating_point_v<T>) return a<T(0) ? -a : a;
    //return bitwise_notand(Mzero<T>(),a); //TODO TEST if bitwise_and with the mzero complement is speedier ?
    if constexpr(std::is_integral_v<T> && std::is_unsigned_v<T>)  return a;
    if constexpr(std::is_integral_v<T> && std::is_signed_v<T>)
    {
      using u_t = eve::detail::as_integer_t<T, unsigned>;
      u_t mask = a >> (sizeof(T)*8 - 1);
      return (a + mask) ^ mask;
    }
  }
}


#endif
