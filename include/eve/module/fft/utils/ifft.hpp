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
//!   @brief take a fft object and make provision to compute the inverse
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
//!     template< callable F, range R, value T>
//!     auto ifft(F const & fft, R & f, T fac) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!     * `fft` : direct fft method
//!     * `f`   :  range of  complex argumentsarguments.
//!     * `fac` : normalization factor.
//!
//!   **Return value**
//!
//!     f contains after call the inverse fft scaled by fac.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/fft/utils/ifft.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(ifft_, ifft);

}

#include <eve/module/fft/utils/impl/ifft.hpp>
