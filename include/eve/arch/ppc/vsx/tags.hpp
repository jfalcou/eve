//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_PPC_VSX_TAGS_HPP_INCLUDED
#define EVE_ARCH_PPC_VSX_TAGS_HPP_INCLUDED

#include <eve/arch/ppc/vmx/tags.hpp>
#include <eve/detail/architecture.hpp>

namespace eve
{
  // dispatching tag for VMX SIMD implementation
  struct vsx_ : vmx_
  {
    using parent = vmx_;
  };

  // Runtime detection of CPU support
  inline bool is_supported(vsx_ const &) noexcept
  {
#if defined(EVE_ARCH_IS_PPC)
    return true; // Fix later
#else
    return false;
#endif
  }

  // VMX extension tag object
  inline const vsx_ vsx = {};
}

#endif
