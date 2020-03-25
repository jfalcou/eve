//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_LOOKUP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_LOOKUP_HPP_INCLUDED

#include <eve/function/definition/lookup.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>

namespace eve::detail
{
  template<typename T, typename I>
  EVE_FORCEINLINE constexpr auto lookup_(EVE_SUPPORTS(cpu_), T const &a, I const& i)
  noexcept Requires(T, Vectorizable<T>, Vectorizable<I>, integral<I>)
  {
    return (i == static_cast<I>(-1)) ? 0 : a;
  }
}

#endif
