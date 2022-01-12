//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/pattern.hpp>
#include <array>

namespace eve
{
  EVE_MAKE_CALLABLE(slide_right_, slide_right);

  template<std::ptrdiff_t Shift, std::ptrdiff_t N>
  inline constexpr
  auto slide_right_pattern = fix_pattern<N>( [](auto i, auto ){ return i<Shift ? na_ : i-Shift;} );

  namespace detail
  {
    //==============================================================================================
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
}

#include <eve/module/real/core/function/regular/generic/slide_right.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/slide_right.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/slide_right.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/slide_right.hpp>
#endif
