//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#if !defined(EVE_NO_SIMD)
#  include <eve/arch/x86/spec.hpp>
#  include <eve/arch/ppc/spec.hpp>
#  include <eve/arch/arm/sve/spec.hpp>
#  include <eve/arch/arm/neon/spec.hpp>
#endif

#include <eve/arch/cpu/spec.hpp>
#include <eve/arch/tags.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  // Local renaming for spy SIMD detector
# if defined(EVE_NO_SIMD)
  inline constexpr undefined_simd_ current_api  = {};
  inline constexpr bool supports_simd           = false;
# else
#   if !defined(EVE_INCOMPLETE_AVX512_SUPPORT)
  inline constexpr EVE_CURRENT_API  current_api = {};
#   else
  inline constexpr eve::avx2_       current_api = {};
#   endif
  inline constexpr bool supports_simd = true;
# endif

  //================================================================================================
  // Types & object s for ABI/API detection
  using current_abi_type = EVE_CURRENT_ABI;
  using current_api_type = std::decay_t<decltype(current_api)>;
}

