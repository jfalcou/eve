//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IS_LESSGREATER_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IS_LESSGREATER_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/as_logical.hpp>
#include <eve/function/scalar/is_ordered.hpp>
#include <eve/function/scalar/is_not_equal.hpp>
#include <eve/function/scalar/logical_and.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto is_lessgreater_(EVE_SUPPORTS(cpu_)
                                                , T const &a
                                                , U const &b) noexcept
  requires( as_logical_t<T>, Vectorizable<T>, Vectorizable<U> )
  {
    if constexpr(std::is_integral_v<T>)
      return is_not_equal(a, b);
    else
      return logical_and(is_not_equal(a, b), is_ordered(a, b));
  }
}

#endif
