//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_XOP_SPEC_HPP_INCLUDED
#define EVE_ARCH_X86_XOP_SPEC_HPP_INCLUDED

#include <eve/detail/compiler.hpp>
#include <eve/arch/x86/avx/spec.hpp>

#if defined(EVE_SUPPORTS_XOP)
#  if defined(EVE_COMP_IS_MSVC)
#    include <intrin.h>
#  else
#    include <x86intrin.h>
#    include <xopintrin.h>
#  endif
#endif

#endif
