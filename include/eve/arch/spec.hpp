//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_SPEC_HPP_INCLUDED
#define EVE_ARCH_SPEC_HPP_INCLUDED

#if !defined(EVE_NO_SIMD)
#  include <eve/arch/x86/spec.hpp>
#  include <eve/arch/ppc/spec.hpp>
#  include <eve/arch/arm/spec.hpp>
#endif

#include <eve/arch/cpu/spec.hpp>

#endif
