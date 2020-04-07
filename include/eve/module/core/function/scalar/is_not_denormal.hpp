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
#include <eve/function/abs.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_not_less.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/true.hpp>
#include <eve/traits/is_logical.hpp>
#include <eve/platform.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto is_not_denormal_(EVE_SUPPORTS(cpu_),
                                                  T const &a) noexcept Requires(as_logical_t<T>,
                                                                                Vectorizable<T>)
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
