//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_DETAIL_REFINE_RSQRT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_DETAIL_REFINE_RSQRT_HPP_INCLUDED

#include <type_traits>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/mul.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <eve/as.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // newton refining from rsqrt approximation
  template<typename T>
  EVE_FORCEINLINE constexpr auto refine_rsqrt(T const &a0, T const & x) noexcept
  {
    return fma( fnma(a0, sqr(x), One(as(x))), x*Half(as(x)), x);
  };


}

#endif
