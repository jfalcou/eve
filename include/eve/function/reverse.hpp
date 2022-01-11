//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <array>

namespace eve
{
  EVE_MAKE_CALLABLE(reverse_, reverse);

  namespace detail
  {
    template <int N, int ...I> inline constexpr bool is_reverse = []
    {
      std::array idxs {I...};
      for (int i = 0; i != static_cast<int>(idxs.size()); ++i) {
        if (idxs[i] != (static_cast<int>(idxs.size()) - i - 1))
          return false;
      }
      return static_cast<int>(idxs.size()) == N;
    }();
  }
}

#include <eve/module/real/core/function/regular/generic/reverse.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/reverse.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/reverse.hpp>
#endif
