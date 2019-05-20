//==================================================================================================
/**
  EVE - Expressive Vector Engine 
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE_TRUNC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_SSE_TRUNC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/wide.hpp>
#include <type_traits>
 
namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  EVE_FORCEINLINE wide<double, fixed<2>, sse_> trunc_(EVE_SUPPORTS(sse2_),
                            wide<double, fixed<2>, sse_> const &a0) noexcept
  {
    return wide<double, fixed<2>, sse_>(eve::trunc(a0[0]), eve::trunc(a0[1]));
  }
  
  EVE_FORCEINLINE wide<double, fixed<1>, sse_> trunc_(EVE_SUPPORTS(sse2_),
                            wide<double, fixed<1>, sse_> const &a0) noexcept
  {
    return wide<double, fixed<1>, sse_>(eve::trunc(a0[0]));
  }
   
}



#endif
