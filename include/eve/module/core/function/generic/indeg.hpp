//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_INDEG_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_INDEG_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/function/fma.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto indeg_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  requires(T, behave_as<floating,T>)
 {
    auto radindeg  = Ieee_constant<T, 0X42652EE1U, 0X404CA5DC1A63C1F8ULL>();
    auto radindegr = Ieee_constant<T, 0X353387C0U, 0X3CE1E7AB456405F8ULL>();
    return fma(a, radindegr, a*radindeg);
  }
}

#endif
