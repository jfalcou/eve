//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
#include <eve/arch/tags.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  // Local renaming for spy SIMD detector
  inline constexpr auto current_api = spy::simd_instruction_set;

# if defined(EVE_NO_SIMD)
  inline constexpr bool supports_simd = false;
# else
  inline constexpr bool supports_simd = true;
# endif
}

#endif
