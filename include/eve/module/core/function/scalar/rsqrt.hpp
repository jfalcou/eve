//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_RSQRT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_RSQRT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/tags.hpp>
#include <eve/assert.hpp>
#include <type_traits>
#include <cmath>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr T rsqrt_( EVE_SUPPORTS(simd_),
                                     T const &a0
                                   ) noexcept
  {
    return rec(sqrt(a0)); 
  }
}

#endif

