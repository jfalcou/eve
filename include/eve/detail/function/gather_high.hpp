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

#include <eve/detail/overload.hpp>
#include <eve/concept/vectorized.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(gather_high_, gather_high);

  // Acts as a pattern itself
  template<> struct is_pattern<tag::gather_high_> : std::true_type {};

  // Premade pattern generator
  template<std::ptrdiff_t N>
  inline constexpr auto gather_high_n = fix_pattern<N>([](auto i, auto c) { return c/2 + i%(c/2); });
}

#include <eve/detail/function/simd/common/gather_high.hpp>

#if defined(EVE_HW_X86)
#  include <eve/detail/function/simd/x86/gather_high.hpp>
#endif
