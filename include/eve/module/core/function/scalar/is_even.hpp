//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_EVEN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_EVEN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/half.hpp>
#include <eve/function/abs.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  is_even_(EVE_SUPPORTS(cpu_), T const &a) noexcept Requires(as_logical_t<T>, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if ( is_flint(a * Half(as(a))))
      {
        if constexpr(eve::platform::supports_denormals)
          return abs(a) != Mindenormal<T>();
        else
          return abs(a) != Smallestposval<T>();
      }
      else return false;
    }
    else
      return (!(a & One(as(a))));
  }
}

#endif
