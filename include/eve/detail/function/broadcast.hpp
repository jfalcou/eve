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
  EVE_MAKE_CALLABLE(broadcast_, broadcast);

  // Acts as a pattern itself
  template<> struct is_pattern<tag::broadcast_> : std::true_type {};

  // Premade pattern generator
  template<std::ptrdiff_t I, std::ptrdiff_t N>
  inline constexpr auto broadcast_n = fix_pattern<N>( [](auto, auto) { return I; } );
}

#include <eve/detail/function/simd/common/broadcast.hpp>

#if defined(EVE_HW_POWERPC)
#  include <eve/detail/function/simd/ppc/broadcast.hpp>
#endif
