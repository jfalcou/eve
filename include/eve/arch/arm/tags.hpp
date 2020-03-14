//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_ARM_TAGS_HPP_INCLUDED
#define EVE_ARCH_ARM_TAGS_HPP_INCLUDED

#include <eve/arch/cpu/tags.hpp>
#include <eve/arch/arm/predef.hpp>

namespace eve
{
  //================================================================================================
  // Tag for all ARM NEON SIMD ABI
  struct arm_ {};

  //================================================================================================
  // Dispatching tag for VMX SIMD implementation
  struct neon64_  : simd_ { using parent = simd_; };
  struct neon128_ : simd_ { using parent = simd_; };

  //================================================================================================
  // Runtime detection of CPU support
  inline bool is_supported(arm_ const &) noexcept
  {
#if defined(EVE_ARCH_IS_ARM)
    return true; // Fix later
#else
    return false;
#endif
  }

  //================================================================================================
  // NEON extension tag object
  inline const arm_ neon = {};
}

#endif
