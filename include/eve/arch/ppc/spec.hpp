//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
#   if defined(SPY_SIMD_IS_PPC_VMX_3_01)
#     define EVE_CURRENT_API ::eve::vmx_3_01_
#   elif defined(SPY_SIMD_IS_PPC_VMX_3_00)
#     define EVE_CURRENT_API ::eve::vmx_3_00_
#   elif defined(SPY_SIMD_IS_PPC_VMX_2_07)
#     define EVE_CURRENT_API ::eve::vmx_2_07_
#   elif defined(SPY_SIMD_IS_PPC_VMX_2_06)
#     define EVE_CURRENT_API ::eve::vmx_2_06_
#   elif defined(SPY_SIMD_IS_PPC_VMX_2_05)
#     define EVE_CURRENT_API ::eve::vmx_2_05_
#   elif defined(SPY_SIMD_IS_PPC_VMX_2_03)
#     define EVE_CURRENT_API ::eve::vmx_2_03_
#   endif
#   define EVE_ABI_NAMESPACE ppc_abi_v0
#   define EVE_ABI_DETECTED
#  elif !defined(EVE_ABI_DETECTED) && defined(SPY_SIMD_IS_PPC_VSX)
#   define EVE_CURRENT_ABI ::eve::ppc_
#   if defined(SPY_SIMD_IS_PPC_VSX_3_01)
#     define EVE_CURRENT_API ::eve::vsx_3_01_
#   elif defined(SPY_SIMD_IS_PPC_VSX_3_00)
#     define EVE_CURRENT_API ::eve::vsx_3_00_
#   elif defined(SPY_SIMD_IS_PPC_VSX_2_07)
#     define EVE_CURRENT_API ::eve::vsx_2_07_
#   elif defined(SPY_SIMD_IS_PPC_VSX_2_06)
#     define EVE_CURRENT_API ::eve::vsx_2_06_
#   endif
#   define EVE_ABI_NAMESPACE ppc_abi_v0
#   define EVE_ABI_DETECTED
#  endif
# endif

#endif
