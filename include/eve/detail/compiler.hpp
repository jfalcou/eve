//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_COMPILER_HPP_INCLUDED
#define EVE_DETAIL_COMPILER_HPP_INCLUDED

// Detect if we are using clang compiler
#if !defined(EVE_COMP_DETECTED) && defined(__clang__)
#  define EVE_COMP_IS_CLANG
#  define EVE_COMP_DETECTED
#endif

// Detect if we are using GNU C compiler
#if !defined(EVE_COMP_DETECTED) && defined(__GNUC__)
#  define EVE_COMP_IS_GNUC
#  define EVE_COMP_DETECTED
#endif

// Detect if we are using ICPC compiler
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
#  if defined(EVE_COMP_DETECTED)
#    define EVE_COMP_IS_INTEL_EMULATED
#  else
#    define EVE_COMP_IS_INTEL
#  endif
#endif

// Detect if we are using MSVC compiler
#if defined(_MSC_VER)
#  define EVE_COMP_IS_MSVC
#  define EVE_COMP_DETECTED
#endif

#endif
