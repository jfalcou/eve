//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_NONE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_NONE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/any.hpp>
#include <eve/logical.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE bool none_(EVE_SUPPORTS(cpu_)
                           , logical<wide<T, N, ABI>> const &v) noexcept
  {
    return !any(v); 
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE bool none_(EVE_SUPPORTS(cpu_)
                           , wide<T, N, ABI> const &v) noexcept
  {
    return none(is_nez(v)); 
  }
}

#endif
