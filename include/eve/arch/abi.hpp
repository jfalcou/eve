//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/deps/spy.hpp>
#include <eve/arch/cpu/abi.hpp>

#if !defined(EVE_NO_SIMD)
#  if defined(EVE_INCLUDE_X86_HEADER)
#    include <eve/arch/x86/abi.hpp>
#  elif defined(EVE_INCLUDE_POWERPC_HEADER)
#    include <eve/arch/ppc/abi.hpp>
#  elif defined(EVE_INCLUDE_ARM_SVE_HEADER)
#    include <eve/arch/arm/sve/abi.hpp>
#  elif defined(EVE_INCLUDE_ARM_NEON_HEADER)
#    include <eve/arch/arm/neon/abi.hpp>
#  elif defined(EVE_INCLUDE_RISCV_HEADER)
#    include <eve/arch/riscv/abi.hpp>
#  endif
#endif
