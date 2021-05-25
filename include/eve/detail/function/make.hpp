//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/function/simd/common/make.hpp>

#if defined(EVE_HW_X86)
#  include <eve/detail/function/simd/x86/make.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/detail/function/simd/ppc/make.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/detail/function/simd/arm/neon/make.hpp>
#endif
