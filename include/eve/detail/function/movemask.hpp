//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>

#include <eve/detail/function/simd/common/movemask.hpp>

#if defined(EVE_HW_X86)
#  include <eve/detail/function/simd/x86/movemask.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/detail/function/simd/arm/neon/movemask.hpp>
#endif
