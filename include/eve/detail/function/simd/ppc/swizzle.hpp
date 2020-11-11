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
#include <eve/detail/function/simd/ppc/patterns/basic.hpp>
#include <eve/detail/function/patterns/matcher.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Unary swizzle - arithmetic
  template<typename T, typename N, ppc_abi ABI, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto swizzle( vmx_ const&, wide<T,N,ABI> const& v, Pattern p ) noexcept
  {
    swizzle_matcher < zero_match, identity_match, broadcast_match
                    , slide_left, slide_right
                    , unpack_match, any_match
                    > that;
    return that(p, v);
  }
}
