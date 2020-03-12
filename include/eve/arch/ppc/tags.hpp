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
  inline constexpr auto vmx = spy::vmx_;
  inline constexpr auto vsx = spy::vsx_;

  //================================================================================================
  // Runtime detection of CPU support
  template<auto Version>
  inline bool is_supported(spy::ppc_simd_info<Version> const &) noexcept
  {
    return false;
  }
}

#endif
