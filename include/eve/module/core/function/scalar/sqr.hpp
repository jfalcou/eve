//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SQR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SQR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/abs.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto sqr_( EVE_SUPPORTS(cpu_),
                                       saturated_type const & ,
                                       T const &a0
                                     ) noexcept
  requires(T, Vectorizable<T>)
  {
    if (std::is_integral_v<T>)
    {
      if constexpr(std::is_signed_v<T>)
      {
        return (eve::saturated_(eve::abs)(a0) > Sqrtvalmax(as(a0))) ? Valmax(as(a0)) : sqr(a0);
      }
      else
      {
        return (a0 > Sqrtvalmax(as(a0))) ? Valmax(as(a0)) : sqr(a0);
      }
    }
    else
    {
      return sqr(a0);
    }
  }
}

#endif

