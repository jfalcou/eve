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
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   Can apply an opteration for group of elements instead of elements.
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
//!   **Parameters**
//!
//!    * x - simd_value to shuffle
//!    * G - (optional) - number of elements to treat as one.
//!
//!  **Return value**
//!
//!    Return x where groups of contiguous G elements are swapped.
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

  template<simd_value T, std::ptrdiff_t G>
  static constexpr std::ptrdiff_t level(eve::as<T> tgt, eve::fixed<G> g)
  {
    const std::ptrdiff_t g_size   = sizeof(element_type_t<T>) * G;
    const std::size_t    reg_size = sizeof(element_type_t<T>) * T::size();
    const std::size_t fund_size = eve::fundamental_cardinal_v<std::uint8_t>;

    if( current_api >= sve )
    {
      if( arithmetic_simd_value<T> )
      {
        if (g_size <= 4 || g_size == fund_size / 2) return 2;
        return 3;
      }
      else
      {
        if( g_size == 8 && fund_size == 16 ) return 2;
        return level(detail::mask_type(tgt), g) + 4;
      }
    }
    if( current_api >= vmx ) return 3;
    if( current_api >= neon ) return 2;

    if( eve::current_api == avx512 && logical_simd_value<T> )
    {
      return level(detail::mask_type(tgt), g) + 4;
    }

    if constexpr( current_api == avx && reg_size >= 32 && g_size <= 2 )
    {
      using half_t          = decltype(T {}.slice(lower_));
      std::ptrdiff_t half_l = level(eve::as<half_t> {}, g);
      // since we are adding, we need to deal with aggregation
      if( reg_size > 32 ) return half_l;
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
};

inline constexpr auto swap_adjacent = detail::named_shuffle_1<swap_adjacent_t> {};

}
