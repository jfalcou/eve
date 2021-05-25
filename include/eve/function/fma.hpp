//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(fma_, fma);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/fma.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/fma.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/fma.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/fma.hpp>
#endif
