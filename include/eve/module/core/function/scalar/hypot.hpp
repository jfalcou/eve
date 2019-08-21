//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_HYPOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_HYPOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/scalar/fma.hpp>
#include <eve/function/scalar/sqr.hpp>
#include <eve/function/scalar/sqrt.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto hypot_(EVE_SUPPORTS(cpu_)
                                       , T const &a0
                                       , T const &a1) noexcept
  requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
      return sqrt(fma(a0,a0, sqr(a1)));
    else
      static_assert(std::is_floating_point_v<T>
                   , "eve::[hypot] - not defined from non floating types"); 
  }
}

#endif
