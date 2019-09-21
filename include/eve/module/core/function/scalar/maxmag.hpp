//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_MAXMAG_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_MAXMAG_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/regular.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/max.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Default case
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto maxmag_(EVE_SUPPORTS(cpu_), T const &a0, U const &a1) noexcept
  {
    return maxmag(regular_type(), a0, a1);
  }

  // -----------------------------------------------------------------------------------------------
  // Regular, Pedantic or numeric case
  template<typename Tag, typename T>
  EVE_FORCEINLINE constexpr auto
  maxmag_(EVE_SUPPORTS(cpu_), Tag tag, T const &a0, T const &a1) noexcept requires(T,
                                                                                   Vectorizable<T>)
  {
    auto aa0 = eve::abs(a0);
    auto aa1 = eve::abs(a1);
    return aa0 < aa1 ? a1 : aa1 < aa0 ? a0 : tag(eve::max)(a0, a1);
  }
}

#endif
