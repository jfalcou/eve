//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/ppc/predef.hpp>
#include <cstddef>

//==================================================================================================
// Register count
#if defined(EVE_HW_POWERPC)

namespace eve
{
  struct register_count
  {
    static constexpr std::size_t general = 32;
    static constexpr std::size_t simd = (spy::simd_instruction_set == spy::vmx_) ? 32 : 64;
  };
}

//==================================================================================================
// PPC SIMD ABI
# if !defined(EVE_CURRENT_API) && defined(SPY_SIMD_IS_PPC)

// #  ifndef EVE_NO_DENORMALS
// #    define EVE_NO_DENORMALS
// #  endif

#  if !defined(__APPLE_CC__) || __APPLE_CC__ <= 1 || __GNUC__ >= 4
#    include <altivec.h>
#  endif

#  ifdef bool
#    undef bool
#  endif

#  ifdef pixel
#    undef pixel
#  endif

#  ifdef vector
#    undef vector
#  endif

#  if defined(__IBMCPP__) || defined(__MWERKS__)
#    define __bool bool
#  endif

#  if !defined(EVE_ABI_DETECTED) && defined(SPY_SIMD_IS_PPC_VMX)
#   define EVE_CURRENT_ABI ::eve::ppc_
#   define EVE_CURRENT_API ::eve::vmx_
#   define EVE_ABI_NAMESPACE ppc_abi_v0
#   define EVE_ABI_DETECTED
#  elif !defined(EVE_ABI_DETECTED) && defined(SPY_SIMD_IS_PPC_VSX)
#   define EVE_CURRENT_ABI ::eve::ppc_
#   define EVE_CURRENT_API ::eve::vsx_
#   define EVE_ABI_NAMESPACE ppc_abi_v0
#   define EVE_ABI_DETECTED
#  endif
# endif

#endif
