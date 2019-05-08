//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_PPC_PREDEF_HPP_INCLUDED
#define EVE_ARCH_PPC_PREDEF_HPP_INCLUDED

// VMX/VSX version numbering
#define EVE_VMX_VERSION 1000
#define EVE_VSX_VERSION 1100

// Detect current highest SSEx variant
#undef EVE_HW_POWERPC
#if !defined(EVE_HW_POWERPC) && defined(__VSX__)
#  define EVE_HW_POWERPC EVE_VSX_VERSION
#endif

#if !defined(EVE_HW_POWERPC) && (defined(__ALTIVEC__) || defined(__VEC__))
#  define EVE_HW_POWERPC EVE_VMX_VERSION
#endif

#endif
