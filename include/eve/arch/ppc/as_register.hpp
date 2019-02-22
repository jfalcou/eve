//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_PPC_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_PPC_AS_REGISTER_HPP_INCLUDED

#include <eve/arch/ppc/predef.hpp>

#if EVE_HW_POWERPC >= EVE_VMX_VERSION
#  include <eve/arch/ppc/vmx/as_register.hpp>
#endif

#if EVE_HW_POWERPC >= EVE_VSX_VERSION
#  include <eve/arch/ppc/vsx/as_register.hpp>
#endif

#endif
