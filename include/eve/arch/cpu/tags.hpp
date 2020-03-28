//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_CPU_TAGS_HPP_INCLUDED
#define EVE_ARCH_CPU_TAGS_HPP_INCLUDED

namespace eve
{
  //================================================================================================
  // Dispatching tag for generic implementation
  struct cpu_
  {
  };

  //================================================================================================
  // Dispatching tag for generic SIMD implementation
  struct simd_ : cpu_
  {
    using parent  = cpu_;
  };

  //================================================================================================
  // Dispatching tag for emulated SIMD implementation of large register
  struct aggregated_ : cpu_
  {
    using parent = cpu_;
  };

  //================================================================================================
  // Dispatching tag for emulated SIMD implementation
  struct emulated_ : cpu_
  {
    using parent = cpu_;
  };

  //================================================================================================
  // Indicator for construction from arbitrary storage
  struct from_bits_
  {
  };

  static constexpr inline from_bits_ from_bits = {};

  //================================================================================================
  // Runtime detection of CPU support
  inline bool is_supported(cpu_ const &) noexcept { return true; }
}

#endif
