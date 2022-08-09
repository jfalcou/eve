//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_simd
//! @{
//!   @var deinterleave_groups
//!   @brief deinterleaves values in n wides
//!
//!    This is a generalization of deinterleave_groups_shuffle for n wides.
//!
//!    The different name comes from for 2 wides - this returns a tuple of
//!    2 wides and a shuffle returns an aggregate
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
//!         TO DO
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `...xs` :  arguments to deinterleave.
//!
//!    **Return value**
//!
//!    TO DO
//!
//!  @groupheader{Example}
//!
//!        @godbolt{doc/core/regular/deinterleave_groups.cpp}
//! @}
//================================================================================================

//================================================================================================
//! @addtogroup core
//! @{
//!    @var deinterleave_groups
//!
//!    @brief Callabe object that deinterleaves values in n wides
//!
//!    This is a generalization of deinterleave_groups_shuffle for n wides.
//!
//!    The different name comes from for 2 wides - this returns a tuple of 2 wides and a shuffle
//!    returns an aggregate
//!
//!    First parameter is fixed<N> group_size - how many elements we consider one element
//!    After that you pass n simd values.
//!    Together those n simd values have interleaved values.
//!    We return a tuple of wides, where all values are separated between individual wides.
//!
//!    NOTE: you can think of this function as AoS to SoA, where all fields have the same size.
//!          group is the size of the field in wide elements.
//!
//!    Examples (one letter is a group - first parameter, group order is preserved):
//!      ABAB'ABAB ABAB'ABAB  => [AAAA'AAAA BBBB'BBBB]
//!      ABCA BCAB CABC       => [AAAA BBBB CCCC]
//!      ABCD'EABC DEAB'CDEA BCDE'ABCD EABC'DEA BCDE'ABCD => [Ax8 Bx8 Cx8 Dx8 Ex8]
//!
//!    **Required header:** `#include <eve/module/core.hpp>`
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(deinterleave_groups_, deinterleave_groups);
}

#include <eve/detail/function/simd/common/deinterleave_groups.hpp>
