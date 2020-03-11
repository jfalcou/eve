//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IROUND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IROUND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/iceil.hpp>
#include <eve/function/ifloor.hpp>
#include <eve/function/itrunc.hpp>
#include <eve/function/inearest.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto iround_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return eve::inearest(a);
  }

  template<typename TAG, typename T>
  EVE_FORCEINLINE constexpr auto iround_(EVE_SUPPORTS(cpu_), T const &a, TAG const &) noexcept
  {
    if constexpr(std::is_same_v<TAG, eve::upward_type>)
      return eve::iceil(a);
    else if constexpr(std::is_same_v<TAG, eve::downward_type>)
      return eve::ifloor(a);
    else if constexpr(std::is_same_v<TAG, eve::toward_zero_type>)
      return eve::itrunc(a);
    else if constexpr(std::is_same_v<TAG, eve::to_nearest_type>)
      return eve::inearest(a);
    else
    {
      return as_integer_t<T>(); 
    }
  }
}

#endif
