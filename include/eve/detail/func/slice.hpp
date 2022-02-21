//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/func/simd/common/slice.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/func/simd/x86/slice.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/detail/func/simd/ppc/slice.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/detail/func/simd/arm/neon/slice.hpp>
#endif
