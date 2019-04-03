//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_LOGICAL_NOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_LOGICAL_NOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/as_logical.hpp>
#include <eve/logical.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto logical_not_(EVE_SUPPORTS(cpu_), T const &a) noexcept
                            requires( as_logical_t<T>, Vectorizable<T> )
  {
    return !a;
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto logical_not_(EVE_SUPPORTS(cpu_), logical<T> const &a) noexcept
                            requires( as_logical_t<T>, Vectorizable<T> )
  {
    return a.not_value();
  }
}

// -------------------------------------------------------------------------------------------------
// Infix operator support
namespace eve
{
  template<typename T>
  EVE_FORCEINLINE auto operator!(T const &v) noexcept -> decltype(eve::logical_not(v))
  {
    return eve::logical_not(v);
  }
}
#endif
