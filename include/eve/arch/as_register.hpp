//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/spec.hpp>

#include <eve/arch/cpu/as_register.hpp>

#if !defined(EVE_NO_SIMD)
#  if defined(EVE_INCLUDE_X86_HEADER)
#    include <eve/arch/x86/as_register.hpp>
#  elif defined(EVE_INCLUDE_POWERPC_HEADER)
#    include <eve/arch/ppc/as_register.hpp>
#  elif defined(EVE_INCLUDE_ARM_SVE_HEADER)
#    include <eve/arch/arm/sve/as_register.hpp>
#  elif defined(EVE_INCLUDE_ARM_NEON_HEADER)
#    include <eve/arch/arm/neon/as_register.hpp>
#  elif defined(EVE_INCLUDE_RISCV_HEADER)
#    include <eve/arch/riscv/as_register.hpp>
#  endif
#endif
