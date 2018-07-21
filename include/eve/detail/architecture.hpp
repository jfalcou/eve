//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_ARCHITECTURE_HPP_INCLUDED
#define EVE_DETAIL_ARCHITECTURE_HPP_INCLUDED

// Detect if we are on X86
#if   defined(i386)      || defined(__i386__)  || defined(__i486__)      \
  ||  defined(__i586__)  || defined(__i686__)  || defined(__i386)        \
  ||  defined(_M_IX86)   || defined(_X86_)     || defined(__THW_INTEL__) \
  ||  defined(__I86__)   || defined(__INTEL__)

#define EVE_ARCH_IS_X86_32
#endif

// Detect if we are on X86_64
#if  defined(__x86_64)  || defined(__x86_64__) || defined(__amd64__) \
  || defined(__amd64)   || defined(_M_X64)
#define EVE_ARCH_IS_X86_64
#endif

// Detect if we are on any X86 variant
#if defined(EVE_ARCH_IS_X86_32) || defined(EVE_ARCH_IS_X86_64)
#define EVE_ARCH_IS_X86
#endif

#if     defined(__powerpc)    ||  defined(__powerpc__)    ||  defined(__POWERPC__)                  \
    || defined(__ppc__)       ||  defined(_M_PPC)         ||  defined(_ARCH_PPC)                    \
    || defined(__PPCGECKO__)  || defined(__PPCBROADWAY__) ||  defined(_XENON)
#define EVE_ARCH_IS_PPC
#endif

#if     defined(__arm__)            || defined(__arm64)             || defined(__thumb__) \
    ||  defined(__TARGET_ARCH_ARM)  || defined(__TARGET_ARCH_THUMB) || defined(_M_ARM)
#define EVE_ARCH_IS_ARM
#endif

#endif
