//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

#include <array>

namespace eve
{
EVE_MAKE_CALLABLE(reverse_, reverse);

namespace detail
{
  template<int N, int... I>
  inline constexpr bool is_reverse = []
  {
    std::array idxs {I...};
    for( int i = 0; i != static_cast<int>(idxs.size()); ++i )
    {
      if( idxs[i] != (static_cast<int>(idxs.size()) - i - 1) ) return false;
    }
    return static_cast<int>(idxs.size()) == N;
  }();
}
}

#include <eve/module/core/regular/impl/reverse.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/reverse.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/reverse.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/reverse.hpp>
#endif
