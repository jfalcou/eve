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

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // SSE mask generators
  //------------------------------------------------------------------------------------------------
  template<int S,typename P> constexpr auto swizzle_mask(P p) noexcept
  {
    auto p0 = (p(0,16/S) == -1 ? 0 : p(0,16/S)) & 3;
    auto p1 = (p(1,16/S) == -1 ? 1 : p(1,16/S)) & 3;

    if constexpr(S == 4)
    {
      auto p2 = (p(2,4) == -1 ? 2 : p(2,4)) & 3;
      auto p3 = (p(3,4) == -1 ? 3 : p(3,4)) & 3;

      return _MM_SHUFFLE(p3,p2,p1,p0);
    }
    else if constexpr(S == 8)
    {
      return _MM_SHUFFLE2( p1, p0 );
    }
  }

  template<typename P, int S> constexpr auto swizzle_mask() noexcept
  {
    return swizzle_mask<S>(P());
  }
}

#include <eve/detail/function/simd/x86/patterns/any_sse2.hpp>
#include <eve/detail/function/simd/x86/patterns/any_ssse3.hpp>
#include <eve/detail/function/simd/x86/patterns/int16.hpp>
#include <eve/detail/function/simd/x86/patterns/moves.hpp>
#include <eve/detail/function/simd/x86/patterns/slide_right.hpp>
#include <eve/detail/function/simd/x86/patterns/slide_left.hpp>
#include <eve/detail/function/simd/x86/patterns/unpack.hpp>
