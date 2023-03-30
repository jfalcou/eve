//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var swap_pairs
//!   @brief swap chosen pair of elements.
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
//!      template<value T, auto I0, auto I1 >
//!      T swap_pairs(T x
//!                      , std::integral_constant<size_t, I0> const & i0>
//!                      , std::integral_constant<size_t, I1> const & i1);
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!     * `i0` : first index
//!     * `i1` : second index
//!
//!    **Return value**
//!
//!    Return x with element i0 and i1 swapped. Action on scalar is identity.
//!    Assert if i0 or i1 are out of range.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/swap_pairs.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(swap_pairs_, swap_pairs);
}

#include <eve/module/core/regular/impl/swap_pairs.hpp>
