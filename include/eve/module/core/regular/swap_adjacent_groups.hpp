//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/shuffle_v2/named_shuffle.hpp>
#include <eve/module/core/regular/shuffle_v2.hpp>

namespace eve
{

//================================================================================================
//! @addtogroup core
//! @{
//!   @var swap_adjacent
//!   @brief goes through all pairs of elements and them: [0, 1, 2, 3] => [1,0,3, 2]
//!   Can do that for group sizes instead of elements.
//!   If group size is equal to the register size - that's a noop.
//!
//!   @code
//!   template<simd_value T, std::ptrdiff_t G>
//!   T swap_adjacent(T x, fixed<G> const &) noexcept;  // (1)
//!
//!   template<simd_value T>
//!   T swap_adjacent(T x) noexcept;  // (2)
//!   @endcode
//!
//!   (2) calls (1) with G == 1;
//!   (1) swaps adjacent groups of elements of size G
//!
//!  **Return value**
//!
//!    Return x where groups with contiguous groups of N elements swapped
//!    for N =  0 or cardinal_v<T> acts as noop.
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/swap_adjacent_groups.cpp}
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
      return 2 * half_l + 4;
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

//================================================================================================
//! @addtogroup core
//! @{
//!   @var swap_adjacent_groups
//!   @brief swap adjacent groups of elements of chosen number.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template<simd_value T, std::ptrdiff_t N>
//!      T swap_adjacent groups(T x, fixed<N> const &) noexcept;
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` : [argument](@ref eve::integral_value).
//!     * `N` : number of elements in group
//!
//!    **Return value**
//!
//!    Return x where groups with contiguous groups of N elements swapped
//!    for N =  0 or cardinal_v<T> acts as noop.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/swap_adjacent_groups.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(swap_adjacent_groups_, swap_adjacent_groups);

template<std::ptrdiff_t G, std::ptrdiff_t N>
inline constexpr auto swap_adjacent_groups_pattern = fix_pattern<N>(
    [](auto i, auto)
    {
      if constexpr( G != N && G != 0 ) return (i + G) % (G * 2) + (G * 2) * (i / (G * 2));
      else return i;
    });
}

#include <eve/module/core/regular/impl/swap_adjacent_groups.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/swap_adjacent_groups.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/swap_adjacent_groups.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/swap_adjacent_groups.hpp>
#endif
