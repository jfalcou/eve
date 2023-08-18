//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/named_shuffles/named_shuffle_utils.hpp>
#include <eve/module/core/regular/shuffle_v2.hpp>

namespace eve
{

//================================================================================================
//! @addtogroup core_named_shuffles
//! @{
//!   @var swap_adjacent
//!   @brief a named shuffle that goes all pairs of elements and swaps them:
//!          [0, 1, 2, 3] => [1, 0, 3, 2]
//!   Can do that for group sizes instead of elements.
//!   Group size has to be 0 < G < T::size()
//!
//!   @code
//!   template<simd_value T, std::ptrdiff_t G>
//!   T swap_adjacent(T x, fixed<G>)  // (1)
//!
//!   template<simd_value T>
//!   T swap_adjacent(T x)  // (2)
//!   @endcode
//!
//!   (2) calls (1) with G == 1;
//!   (1) swaps adjacent groups of elements of size G
//!
//!  **Return value**
//!
//!    Return x where groups with contiguous groups of N elements swapped
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/named_shuffles/swap_adjacent.cpp}
//! @}
//================================================================================================
struct swap_adjacent_t
{
  template<simd_value T, std::ptrdiff_t G>
  static constexpr auto pattern(eve::as<T>, eve::fixed<G>)
  requires(G < T::size())
  {
    return eve::fix_pattern<T::size() / G>(
        [](int i, int)
        {
          if( i & 1 ) return i - 1;
          else return i + 1;
        });
  }

  template<arithmetic_simd_value T, std::ptrdiff_t G>
  static constexpr std::ptrdiff_t level(eve::as<T>, eve::fixed<G> g)
  {
    if( current_api >= sve ) return 3;
    if( current_api >= vmx ) return 3;
    if( current_api >= neon ) return 2;

    const std::ptrdiff_t g_size   = sizeof(element_type_t<T>) * G;
    const std::size_t    reg_size = sizeof(element_type_t<T>) * T::size();

    if constexpr ( current_api == avx && reg_size >= 32 && g_size <= 2 )
    {
      using half_t = decltype(T {}.slice(lower_));
      std::ptrdiff_t half_l = level(eve::as<half_t>{}, g);
      // since we are adding, we need to deal with aggregation
      if (reg_size > 32) return half_l;
      return detail::idxm::add_shuffle_levels({half_l, half_l, 4});
    }

    if( current_api >= sse2 )
    {
      if( g_size >= 4 ) return 2;
      if( g_size == 2 && reg_size <= 8 ) return 2;
      if( current_api >= ssse3 ) return 3;
      if( g_size == 2 ) return 4;
      return 6;
    }

    return 2;
  }

  template<logical_simd_value T, std::ptrdiff_t G>
  static constexpr std::ptrdiff_t level(eve::as<T>, eve::fixed<G> g)
  {
    std::ptrdiff_t l = level(eve::as<decltype(T {}.mask())> {}, g);
    if( current_api >= avx512 || current_api >= sve ) l += 4;
    return l;
  }
};

inline constexpr auto swap_adjacent = detail::named_shuffle_1<swap_adjacent_t> {};

}
