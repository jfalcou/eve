//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/pattern.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_simd
//! @{
//! @var deinterleave_groups_shuffle
//!
//! @brief Callable object for a deinterleave groups shuffle
//!
//! deinterleaves elements from one or two registers
//!
//! Accepts either a register and a group size or two registers and a group size
//! group is how many elements are treated as one chunk, example:
//!
//! 01234567,  group_size = 1  ==> 02461235
//! 0123 4567, group_size = 2  ==> 01452367
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(deinterleave_groups_shuffle_, deinterleave_groups_shuffle);

template<std::ptrdiff_t G, std::ptrdiff_t N>
requires(G <= N) inline constexpr auto deinterleave_groups_shuffle_pattern = fix_pattern<N>(
    [](int i, int size)
    {
      if( size == G ) return i;

      int const group_n   = size / G;
      int const group_i   = i / G;
      int const group_pos = i % G;

      int take_from_group = 0;

      if( i < size / 2 ) take_from_group = group_i * 2;
      else take_from_group = (group_i - group_n / 2) * 2 + 1;

      return take_from_group * (int)G + group_pos;
    });
}

#include <eve/module/core/regular/impl/generic/deinterleave_groups_shuffle.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/deinterleave_groups_shuffle.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/deinterleave_groups_shuffle.hpp>
#endif
