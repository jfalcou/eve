//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/pattern.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(slide_right_, slide_right);

  //================================================================================================
  // Classify a pattern as a slide_right
  template<std::ptrdiff_t... I> inline constexpr std::ptrdiff_t is_slide_right = []()
  {
    constexpr std::ptrdiff_t card   = sizeof...(I);
    std::array<std::ptrdiff_t,card> ref = {I...};

    std::ptrdiff_t found = 0;
    for(std::ptrdiff_t n=1;n<card;++n)
    {
      std::array<std::ptrdiff_t,card> cur;
      for(std::ptrdiff_t i=0;i<card;i++) cur[i] = (i < n) ? -1 : i-n;

      if(ref == cur) return n;
    }

    return found;
  }();
}

#include <eve/detail/function/simd/common/slide_right.hpp>

#if defined(EVE_HW_X86)
#  include <eve/detail/function/simd/x86/slide_right.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/detail/function/simd/arm/neon/slide_right.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/detail/function/simd/ppc/slide_right.hpp>
#endif
