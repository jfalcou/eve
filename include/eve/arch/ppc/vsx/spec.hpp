//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_PPC_VSX_SPEC_HPP_INCLUDED
#define EVE_ARCH_PPC_VSX_SPEC_HPP_INCLUDED

#include <eve/arch/ppc/vsx/tags.hpp>

#if !defined(EVE_CURRENT_ABI)
  #if EVE_HW_POWERPC == EVE_VSX_VERSION
    #define EVE_CURRENT_ABI ::eve::ppc_
    #define EVE_CURRENT_API ::eve::vsx_
  #endif
#endif

#endif
