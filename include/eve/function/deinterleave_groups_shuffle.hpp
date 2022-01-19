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
  EVE_MAKE_CALLABLE(deinterleave_groups_shuffle_, deinterleave_groups_shuffle);

  // A => A
  // AB => AB
  // ABAB 1 => AABB
  // AABBAABB 2 => AAAABBBB  01452367
  // AAAA'BBBB'AAAA'BBBB 4 =>
  // 0123'4567'89ab'cdef
  // 0123'89ab'4567'cdef

  // ABAB'ABAB 1 =>
  // 0123'4567
  // 0246'1357

  template <std::ptrdiff_t G, std::ptrdiff_t N>
    requires (G <= N)
  inline constexpr
  auto deinterleave_groups_shuffle_pattern = fix_pattern<N>( [] (int i, int size) {
    if (size == G) return i;

    int const group_n   = size / G;
    int const group_i   = i / G;
    int const group_pos = i % G;

    int take_from_group = 0;

    if (i < size / 2) take_from_group = group_i * 2;
    else              take_from_group = (group_i - group_n / 2) * 2 + 1;

    return take_from_group * (int) G + group_pos;
  });
}

#include <eve/module/real/core/function/regular/generic/deinterleave_groups_shuffle.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/deinterleave_groups_shuffle.hpp>
#endif
