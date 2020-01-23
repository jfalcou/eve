//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_COPYSIGN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_COPYSIGN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/signnz.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bit_notand.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  copysign_(EVE_SUPPORTS(cpu_), T const &a0, T const &a1) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
      return bit_or(bitofsign(a1), bit_notand(Signmask(as(a0)), a0));
    else
    {
      if constexpr(std::is_unsigned_v<T>)
        return a0;
      else
      {     
        return (a0 == Valmin(as(a0)))
          ? ((a1 > 0) ? Valmax(as(a0)) : a0) 
          : eve::abs(a0) * signnz(a1);
      }
    }
  }
}

#endif
