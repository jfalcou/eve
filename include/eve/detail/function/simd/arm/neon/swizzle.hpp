//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/function/simd/arm/neon/patterns.hpp>
#include <eve/detail/function/patterns/matcher.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Unary swizzle - arithmetic
  template<typename T, typename N, typename P, arm_abi ABI, int Size>
  EVE_FORCEINLINE auto swizzle( neon128_ const&
                              , wide<T,N,ABI> const& v, swizzler_t<P,Size> p
                              ) noexcept
  {
    swizzle_matcher < detail::zeroing   , detail::identity
                    , detail::slide_left, detail::slide_right
                    , detail::broadcast
                    , detail::reverse
                    , detail::any_pattern
                    > that;

    return that(p, v);
  }
}
