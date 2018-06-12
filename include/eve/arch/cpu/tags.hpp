//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_CPU_TAGS_HPP_INCLUDED
#define EVE_ARCH_CPU_TAGS_HPP_INCLUDED

namespace eve
{
  // dispatching tag for generic implementation
  struct cpu_ {};

  // dispatching tag for generic SIMD implementation
  struct simd_ : cpu_ { using parent = cpu_; };

  // dispatching tag for emulated SIMD implementation
  struct emulated_ : cpu_ { using parent = cpu_; };

  // Runtime detection of CPU support
  inline bool is_supported(cpu_ const& ) noexcept { return true; }
}

#endif
