//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/predef.hpp>
#include <eve/arch/tags.hpp>

#if !defined(EVE_NO_SIMD)
#  if defined(EVE_INCLUDE_X86_HEADER)
#    include <eve/arch/x86/spec.hpp>
#  elif defined(EVE_INCLUDE_POWERPC_HEADER)
#    include <eve/arch/ppc/spec.hpp>
#  elif defined(EVE_INCLUDE_ARM_SVE_HEADER)
#    include <eve/arch/arm/sve/spec.hpp>
#  elif defined(EVE_INCLUDE_ARM_NEON_HEADER)
#    include <eve/arch/arm/neon/spec.hpp>
#  elif defined(EVE_INCLUDE_RISCV_HEADER)
#    include <eve/arch/riscv/spec.hpp>
#  endif
#endif

#include <eve/arch/cpu/spec.hpp>

namespace eve
{
  //================================================================================================
  // Local renaming for spy SIMD detector
  inline constexpr EVE_CURRENT_API  current_api = {};

  //================================================================================================
  // Types & objects for ABI/API detection
  using current_abi_type = EVE_CURRENT_ABI;
  using current_api_type = EVE_CURRENT_API;
}

