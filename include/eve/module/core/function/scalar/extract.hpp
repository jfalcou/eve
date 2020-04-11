3//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry LAPRESTE
  Copyright 2020 Joel Falcou

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_EXTRACT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_EXTRACT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  extract_(EVE_SUPPORTS(cpu_), T const &a, U const &) noexcept Requires(T, Vectorizable<T>)
  {
    return a;
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto extract_(EVE_SUPPORTS(cpu_),
                                          logical<T> const &a,
                                          U const &) noexcept Requires(logical<T>, Vectorizable<T>)
  {
    return a;
  }
}

#endif
