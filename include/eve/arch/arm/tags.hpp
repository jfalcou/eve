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
#include <eve/detail/meta/traits.hpp>

namespace eve
{
  // clang-format off
  //================================================================================================
  // Tag for all ARM NEON SIMD ABI
  //================================================================================================
  struct arm_ {};

  //================================================================================================
  // Dispatching tag for VMX SIMD implementation
  //================================================================================================
  struct neon64_  : simd_ { using parent = simd_; };
  struct neon128_ : simd_ { using parent = simd_; };

  //================================================================================================
  // NEON extension tag object
  //================================================================================================
  inline constexpr auto neon = spy::neon_;

  // clang-format on
  //================================================================================================
  // Runtime detection of CPU support
  //================================================================================================
  template<auto Version> inline bool is_supported(spy::arm_simd_info<Version> const &) noexcept
  {
    return false;
  }

  //================================================================================================
  // ARM ABI concept
  //================================================================================================
  template<typename T> concept arm_abi = detail::is_one_of<T>(detail::types<neon128_, neon64_> {});
}

