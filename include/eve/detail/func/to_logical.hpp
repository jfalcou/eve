//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/func/simd/common/to_logical.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/func/simd/x86/to_logical.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/detail/func/simd/ppc/to_logical.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/detail/func/simd/arm/neon/to_logical.hpp>
#endif
