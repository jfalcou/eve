//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_ARM_SPEC_HPP_INCLUDED
#define EVE_ARCH_ARM_SPEC_HPP_INCLUDED

#include <eve/arch/arm/predef.hpp>
#include <cstddef>

// Register count
#if defined(EVE_HW_ARM)
namespace eve
{
  struct register_count
  {
    static constexpr std::size_t general = 32;
    static constexpr std::size_t simd    = 32;
  };
}

// NEON SIMD ABI
#  if !defined(EVE_CURRENT_ABI)
#    if EVE_HW_ARM == EVE_NEON_VERSION
#      define EVE_CURRENT_ABI ::eve::arm_
#      include <arm_neon.h>
#    endif
#  endif
#endif

// NEON SIMD API
#if !defined(EVE_CURRENT_API)
#  define EVE_CURRENT_API ::eve::neon128_
#endif

#endif
