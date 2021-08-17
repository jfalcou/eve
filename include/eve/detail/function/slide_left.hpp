//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/pattern.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(slide_left_, slide_left);

  //================================================================================================
  // Classify a pattern as a swag
  template<std::ptrdiff_t... I> inline constexpr std::ptrdiff_t is_slide_left = []()
  {
    constexpr std::ptrdiff_t card   = sizeof...(I);
    std::array<std::ptrdiff_t,card> ref = {I...};

    std::ptrdiff_t found = 0;
    for(std::ptrdiff_t n=1;n<card;++n)
    {
      std::array<std::ptrdiff_t,card> cur;
      for(std::ptrdiff_t i=0;i<card;i++) cur[i] = (i+n < card) ? i+n : -1;

      if(ref == cur) found = n;
    }

    return found;
  }();
}

#include <eve/detail/function/simd/common/slide_left.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/slide_left.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/detail/function/simd/arm/neon/slide_left.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/detail/function/simd/ppc/slide_left.hpp>
#endif
