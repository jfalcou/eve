//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NOT_DENORMAL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NOT_DENORMAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/scalar/abs.hpp>
#include <eve/function/scalar/is_eqz.hpp>
#include <eve/function/scalar/is_not_less.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/true.hpp>
#include <eve/is_logical.hpp>
#include <eve/platform.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/as_logical.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto is_not_denormal_(EVE_SUPPORTS(cpu_),
                                                  T const &a) noexcept requires(as_logical_t<T>,
                                                                                vectorizable<T>)
  {
    if constexpr(std::is_integral_v<T> || is_logical_v<T> || !platform::supports_denormals)
    { return True<T>(); }
    else
    {
      return is_eqz(a) || is_not_less(eve::abs(a), Smallestposval(as(a)));
    }
  }
}

#endif
