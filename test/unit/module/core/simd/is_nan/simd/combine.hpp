//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_SIMD_COMBINE_HPP_INCLUDED
#define EVE_FUNCTION_SIMD_COMBINE_HPP_INCLUDED

#include <eve/function/scalar/combine.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/wide.hpp>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto
  combine_(EVE_SUPPORTS(cpu_), wide<T, N, ABI> const &a, wide<T, N, ABI> const &b) noexcept
  {
    return wide<T, typename N::combined_type>{a, b};
  }
}

#endif
