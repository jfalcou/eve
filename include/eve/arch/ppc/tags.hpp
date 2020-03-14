//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_PPC_TAGS_HPP_INCLUDED
#define EVE_ARCH_PPC_TAGS_HPP_INCLUDED

#include <eve/arch/cpu/tags.hpp>
#include <eve/arch/ppc/predef.hpp>

namespace eve
{
  //================================================================================================
  // Tag for all PPC SIMD ABI
  struct ppc_ {};

  //================================================================================================
  // Dispatching tag for V*X SIMD implementation
  struct vmx_ : simd_ { using parent  = simd_;};
  struct vsx_ : vmx_  { using parent  = vmx_; };

  //================================================================================================
  // V*X extension tag objects
  inline const vmx_ vmx = {};
  inline const vsx_ vsx = {};

  //================================================================================================
  // Runtime detection of CPU support
#if defined(EVE_ARCH_IS_PPC)
  inline bool is_supported(vmx_ const &) noexcept
  {
    return false;
  }

  // Runtime detection of CPU support
  inline bool is_supported(vsx_ const &) noexcept
  {
    return true; // Fix later
  }
#else
  inline bool is_supported(vmx_ const &) noexcept { return false; }
  inline bool is_supported(vsx_ const &) noexcept { return false; }
#endif

}

#endif
