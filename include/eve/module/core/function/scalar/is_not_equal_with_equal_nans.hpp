//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NOT_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_NOT_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp>
#include <eve/function/numeric.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto is_not_equal_(
      EVE_SUPPORTS(cpu_),
      numeric_type const &,
      T const &a,
      U const &b) noexcept requires(as_logical_t<T>, vectorizable<T>, vectorizable<U>)
  {
    if constexpr(std::is_floating_point_v<T>) { return (a != b) && ((a == a) || (b == b)); }
    else
    {
      return a != b;
    }
  }
}

#endif
