//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#if !defined(EVE_NO_SIMD)
#  include <eve/arch/x86/spec.hpp>
#  include <eve/arch/ppc/spec.hpp>
#  include <eve/arch/arm/spec.hpp>
#endif

#include <eve/arch/cpu/spec.hpp>
#include <eve/arch/tags.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  // Local renaming for spy SIMD detector
# if defined(EVE_NO_SIMD)
  inline constexpr auto current_api     = spy::undefined_simd_;
  inline constexpr bool supports_simd   = false;
# else
#   if !defined(EVE_INCOMPLETE_AVX512_SUPPORT)
  inline constexpr auto current_api   = spy::simd_instruction_set;
#   else
  inline constexpr auto current_api   = spy::avx2_;
#   endif
  inline constexpr bool supports_simd = true;
# endif
}

