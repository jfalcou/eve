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

namespace eve
{
  EVE_MAKE_CALLABLE(slide_right_, slide_right);

  template<std::ptrdiff_t Shift, std::ptrdiff_t N>
  inline constexpr
  auto slide_right_pattern = fix_pattern<N>( [](auto i, auto ){ return i<Shift ? na_ : i-Shift;} );
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
