//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NORMAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NORMAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/function/scalar/is_greater_equal.hpp>
#include <eve/function/scalar/is_finite.hpp>
#include <eve/function/scalar/is_nez.hpp>
#include <eve/function/scalar/abs.hpp>
#include <eve/is_logical.hpp>
#include <eve/as_logical.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  is_normal_(EVE_SUPPORTS(cpu_), T const &a) noexcept requires(as_logical_t<T>, Vectorizable<T>)
  {
    if constexpr(std::is_integral_v<T> || is_logical_v<T>) { return is_nez(a); }
    else
    {
      return is_finite(a) && is_greater_equal(eve::abs(a), Smallestposval(as(a)));
    }
  }
}

#endif
