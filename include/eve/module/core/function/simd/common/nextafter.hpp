//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_NEXTAFTER_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_NEXTAFTER_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/next.hpp>    
#include <eve/forward.hpp>
#include <eve/concept/vectorized.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto nextafter_(EVE_SUPPORTS(cpu_)
                                 , T const &x
                                 , U const &y) noexcept
  requires(T, Vectorized<T>)
  {
    return if_else(x < y,  next(x), if_else(y < x, prev(x), x)); 
 
  }
}

#endif
