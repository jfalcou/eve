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

#include <eve/arch/cpu/tags.hpp>
#include <eve/arch/ppc/predef.hpp>
#include <eve/detail/meta.hpp>

namespace eve
{
  // clang-format off
  //================================================================================================
  // Tag for all PPC SIMD ABI
  //================================================================================================
  struct ppc_
  {
    static constexpr std::size_t bits                     = 128;
    static constexpr std::size_t bytes                    = 16;
    static constexpr bool        is_wide_logical = true;

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);
  };

  //================================================================================================
  // Dispatching tag for V*X SIMD implementation
  //================================================================================================
  struct vmx_ : simd_ { using parent = simd_; };
  struct vsx_ : vmx_  { using parent = vmx_; };

  //================================================================================================
  // V*X extension tag objects
  //================================================================================================
  inline constexpr auto vmx = spy::vmx_;
  inline constexpr auto vsx = spy::vsx_;

  // clang-format on
  //================================================================================================
  // Runtime detection of CPU support
  //================================================================================================
  template<auto Version> inline bool is_supported(spy::ppc_simd_info<Version> const &) noexcept
  {
    #if defined( SPY_SIMD_IS_PPC )
    if constexpr( Version == spy::vmx_.version )
    {
      static const bool detected = (__builtin_cpu_supports( "altivec" ) != 0);
      return detected;
    }
    else if constexpr( Version == spy::vsx_.version )
    {
      static const bool detected = (__builtin_cpu_supports( "vsx" ) != 0);
      return detected;
    }
    else
    {
      return false;
    }
    #else
      return false;
    #endif
  }

  //================================================================================================
  // PPC ABI concept
  //================================================================================================
  template<typename T> concept ppc_abi = detail::is_one_of<T>(detail::types<ppc_> {});
}
