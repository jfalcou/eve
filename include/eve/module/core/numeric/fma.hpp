//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/numeric/impl/fma.hpp>
#include <eve/module/core/regular/fma.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/numeric/impl/simd/x86/fma.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/numeric/impl/simd/ppc/fma.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/numeric/impl/simd/arm/neon/fma.hpp>
#endif
