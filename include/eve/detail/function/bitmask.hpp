//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/function/simd/common/bitmask.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/bitmask.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/detail/function/simd/arm/sve/bitmask.hpp>
#endif
