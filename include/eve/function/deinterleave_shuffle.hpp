//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/pattern.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(deinterleave_shuffle_, deinterleave_shuffle);

  template <std::ptrdiff_t N>
  inline constexpr
  auto deinterleave_shuffle_pattern = fix_pattern<N>( [] (int i, int size) {
    if ( i < size / 2) return i * 2;
    else               return (i - size / 2) * 2 + 1;
  });
}

#include <eve/module/real/core/function/regular/generic/deinterleave_shuffle.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/deinterleave_shuffle.hpp>
#endif
