//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_ARM_PREDEF_HPP_INCLUDED
#define EVE_ARCH_ARM_PREDEF_HPP_INCLUDED

// NEON version numbering
#define EVE_NEON_VERSION 1000

// Detect current highest NEON variant
#undef EVE_HW_ARM
#if !defined(EVE_HW_ARM) && (defined(__ARM_NEON__) || defined(_M_ARM) || defined(__aarch64__))
#  define EVE_HW_ARM EVE_NEON_VERSION
#endif

#endif
