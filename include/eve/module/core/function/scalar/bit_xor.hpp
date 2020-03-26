//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_BIT_XOR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_BIT_XOR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/concept/stdconcepts.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  bit_xor_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept 
  requires vectorizable<T> && vectorizable<U> && bit_compatible<T,U>
  {
    if constexpr(std::floating_point<T>)
    {
      using b_t = as_integer_t<T, unsigned>;
      auto const tgt = as_<b_t>{};

      return bit_cast(b_t(bit_cast(a,tgt) ^ bit_cast(b,tgt)), as(a));
    }
    else
    {
      if constexpr(std::same_as<T, U>)
      {
        return a ^ b;
      }
      else
      {
        return static_cast<T>(a ^ bit_cast(b, as(a)));
      }
    }
  }
}

#endif
