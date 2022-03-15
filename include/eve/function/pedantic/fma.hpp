//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/pedantic/fma.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/pedantic/impl/simd/x86/fma.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/pedantic/impl/simd/ppc/fma.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/pedantic/impl/simd/arm/neon/fma.hpp>
#endif
