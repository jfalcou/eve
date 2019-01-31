//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_PPC_SPEC_HPP_INCLUDED
#define EVE_ARCH_PPC_SPEC_HPP_INCLUDED

#include <eve/arch/ppc/predef.hpp>
#include <cstddef>

// Register count
#if defined(EVE_HW_POWERPC)
namespace eve
{
  struct register_count
  {
    static constexpr std::size_t general = 32;

#  if EVE_HW_POWERPC == EVE_VMX_VERSION
    static constexpr std::size_t simd = 32;
#  else
    static constexpr std::size_t simd = 64;
#  endif
  };
}
#endif

#include <eve/arch/ppc/vmx/spec.hpp>
#include <eve/arch/ppc/vsx/spec.hpp>

#endif
