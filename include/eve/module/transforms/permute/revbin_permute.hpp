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
//! @addtogroup fft
//! @{
//!   @var revbin_permute
//!   @brief Implement the revbin_permute permutation of a range of 2^n elements
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/fft.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!     template< range r>
//!     auto revbin_permutet(T r) noexcept;
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `r` :  [range of  arguments](@ref eve::value).
//!
//!   **Return value**
//!
//!     r submitted to a permutation that swaps elements whose binary indices are mutual reversals.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/fft/utils/revbin_permute.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(revbin_permute_, revbin_permute);

}

#include <eve/module/transforms/permute/impl/revbin_permute.hpp>
