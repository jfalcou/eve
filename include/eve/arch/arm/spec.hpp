//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_ARM_SPEC_HPP_INCLUDED
#define EVE_ARCH_ARM_SPEC_HPP_INCLUDED

#include <eve/arch/arm/predef.hpp>
#include <cstddef>

//==================================================================================================
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

//==================================================================================================
// NEON SIMD ABI
# if !defined(EVE_CURRENT_API) && defined(SPY_SIMD_IS_ARM)
#  include <arm_neon.h>
#  if !defined(EVE_CURRENT_ABI) && defined(SPY_SIMD_IS_ARM_NEON)
#   define EVE_CURRENT_ABI ::eve::arm_
#   define EVE_CURRENT_API ::eve::neon128_
#  endif
# endif

# if !defined(__aarch64__)
#  ifndef EVE_NO_DENORMALS
#   define EVE_NO_DENORMALS
#  endif
# endif

#endif

#endif
