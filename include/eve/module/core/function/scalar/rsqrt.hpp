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
#include <eve/constant/inf.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqrt.hpp>
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
    return a0 ? rec(eve::sqrt(a0)) : Inf(as(a0));
    //needed as by sqrt IEEE requirements : sqrt(-0.0) is -0.0
  }
}

#endif
