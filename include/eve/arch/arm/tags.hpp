//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/arm/predef.hpp>
#include <eve/arch/cpu/tags.hpp>
#include <eve/detail/meta.hpp>

#if defined( SPY_SIMD_IS_ARM )
  #if defined( SPY_OS_IS_LINUX )
    #include <asm/hwcap.h>
    #include <sys/auxv.h>
  #endif
#endif

namespace eve
{
  // clang-format off
  //================================================================================================
  // ABI tags for all ARM bits SIMD registers
  //================================================================================================
  template<std::size_t Size, bool Logical> struct arm_abi_
  {
    static constexpr std::size_t bits                     = Size;
    static constexpr std::size_t bytes                    = Size/8;
    static constexpr bool        regular_logical_register = Logical;

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);
  };

  struct arm_64_  : arm_abi_<64,true> {};
  struct arm_128_ : arm_abi_<128,true> {};

  //================================================================================================
  // Dispatching tag for ARM SIMD implementation
  //================================================================================================
  struct neon64_  : simd_ {};
  struct neon128_ : simd_ {};

  //================================================================================================
  // NEON extension tag objects
  //================================================================================================
  inline constexpr auto neon = spy::neon_;

  struct aarch64_   {};
  inline constexpr auto aarch64 = aarch64_{};

  //================================================================================================
  // Runtime detection of CPU support
  //================================================================================================
  inline bool is_supported(spy::arm_simd_info<spy::detail::simd_version::neon_ > const &) noexcept
  {
    #if defined( SPY_SIMD_IS_ARM )
    auto hwcaps = getauxval(AT_HWCAP);
    return (hwcaps & (1 << 12)) != 0;
    #else
      return false;
    #endif
  }

  inline bool is_supported(aarch64_ const &) noexcept
  {
    #if defined( SPY_SIMD_IS_ARM )
    auto hwcaps = getauxval(AT_HWCAP);
    return (hwcaps & HWCAP_ASIMD) != 0;
    #else
      return false;
    #endif
  }

  //================================================================================================
  // ARM ABI concept
  //================================================================================================
  template<typename T> concept arm_abi = detail::is_one_of<T>(detail::types<arm_64_,arm_128_> {});
}
