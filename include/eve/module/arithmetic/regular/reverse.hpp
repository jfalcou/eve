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
}

#include <eve/module/arithmetic/regular/impl/reverse.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/arithmetic/regular/impl/simd/x86/reverse.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/arithmetic/regular/impl/simd/arm/neon/reverse.hpp>
#endif
