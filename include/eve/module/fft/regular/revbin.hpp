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
//! @addtogroup polynomial
//! @{
//!   @var revbint
//!   @brief Implement the revbin permutation of a wide
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
//!     template< value x>
//!     auto revbin(T x) noexcept;
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [range of  arguments](@ref eve::value).
//!
//!   **Return value**
//!
//!     x submitted to a permutation that swaps elements whose binary indices are mutual reversals.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/fft/regular/naive_fft.cpp}
//!
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(revbin_, revbin);

}

#include <eve/module/fft/regular/impl/revbin.hpp>
