//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_PPC_VMX_TAGS_HPP_INCLUDED
#define EVE_ARCH_PPC_VMX_TAGS_HPP_INCLUDED

#include <eve/arch/cpu/tags.hpp>
#include <eve/detail/architecture.hpp>

namespace eve
{
  // Tag for all PPC SIMD ABI
  struct ppc_
  {
  };

  // dispatching tag for VMX SIMD implementation
  struct vmx_ : simd_
  {
    using parent = simd_;
  };

  // Runtime detection of CPU support
  inline bool is_supported(vmx_ const &) noexcept
  {
#if defined(EVE_ARCH_IS_PPC)
    return true; // Fix later
#else
    return false;
#endif
  }

  // VMX extension tag object
  inline const vmx_ vmx = {};
}

#endif
