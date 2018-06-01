//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
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
