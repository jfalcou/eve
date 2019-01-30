//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_AND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_AND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/scalar/bitwise_cast.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T, typename U> EVE_FORCEINLINE
  constexpr T bitwise_and_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
  {
    static_assert ( sizeof(T) == sizeof(U)
                  , "eve::bitwise_and - Arguments have incompatible size"
                  );

    if constexpr( std::is_floating_point_v<T>)
    {
      using b_t = as_integer_t<T,unsigned>;
      return bitwise_cast<T>(b_t(bitwise_cast<b_t>(a) & bitwise_cast<b_t>(b)));
    }
    else
    {
      if constexpr( std::is_same_v<T,U> )
      {
        return a & b;
      }
      else
      {
        return a & bitwise_cast<T>(b);
      }
    }
  }
}

#endif
