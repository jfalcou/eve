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
    if constexpr (G != N && G != 0) return (i + G) % (G * 2) + (G * 2) * (i / (G * 2));
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
