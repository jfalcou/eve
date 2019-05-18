//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REFINE_REC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_REFINE_REC_HPP_INCLUDED

//TODO generic, I believe, not simd
//TODO change as soon as fma fnms are available
#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/one.hpp>
//TODO#include <eve/function/fma.hpp>
//TODO#include <eve/function/fnms.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/add.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE T refine_rec_(EVE_SUPPORTS(cpu_)
                                  , wide<T, N, ABI> const &a
                                  , wide<T, N, ABI> const &x) noexcept
  {
    using t_t = wide<T, N, ABI>; 
    // Newton-Raphson: 1/X ~= x*(1-a0*x) + x
    return (One<t_t>()-a*x)*x+x; 
    //TODO return fma(fnms(x, a0, One<T>()), x, x);
  }
}

#endif
