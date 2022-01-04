//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/pattern.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(slide_left_, slide_left);

  template<std::ptrdiff_t Shift, std::ptrdiff_t N>
  inline constexpr
  auto slide_left_pattern = fix_pattern<N>( [](auto i, auto c)
                                            {
                                              return (i+Shift) < c ? i+Shift : na_;
                                            }
                                          );
}

#include <eve/module/real/core/function/regular/generic/slide_left.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/slide_left.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/slide_left.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/slide_left.hpp>
#endif
