//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_X86_AS_REGISTER_HPP_INCLUDED

#include <eve/arch/x86/predef.hpp>

#if EVE_HW_X86 >= EVE_SSE2_VERSION
#  include <eve/arch/x86/sse2/as_register.hpp>
#endif

#if EVE_HW_X86 >= EVE_AVX_VERSION
#  include <eve/arch/x86/avx/as_register.hpp>
#endif

#endif
