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
//!   @var idx_swap
//!   @brief given a relaxed_range an two indexes swap the corresponding range elements of the range
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
//!     template< relaxed_range R, integral_value I>
//!     void idx_swap(R & f, I const& idx1, I const & idx2) noexcept;
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`             : [contiguous range of  arguments](@ref eve::value).
//!     * ``idx1`, `idx2` : indexes of the values to be swapped
//!
//!   **Return value**
//!
//!     f is submitted to a permutation that swaps f[idx1] and f[idx2].
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/fft/utils/idx_swap.cpp}
//!
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(idx_swap_, idx_swap);

}

#include <eve/module/fft/utils/impl/idx_swap.hpp>
