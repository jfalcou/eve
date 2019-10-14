//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_XOR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BITWISE_XOR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/scalar/bitwise_cast.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  bitwise_xor_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires(T,
                                                                             vectorizable<T>,
                                                                             vectorizable<U>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      using b_t = as_integer_t<T, unsigned>;
      auto const tgt = as_<b_t>{};

      return bitwise_cast(b_t(bitwise_cast(a,tgt) ^ bitwise_cast(b,tgt)), as(a));
    }
    else
    {
      if constexpr(std::is_same_v<T, U>) { return a ^ b; }
      else
      {
        return a ^ bitwise_cast(b, as(a));
      }
    }
  }
}

#endif
