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
//!   @var naive_fft
//!   @brief Implement the raw fft
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
//!     template< eve::Range R, floating_ordered_value T>
//!     R fft(R const &a) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `a` :  [range of  arguments](@ref eve::value).
//!
//!     *  sign : \f$\pm1\f$
//!
//!     * `fac` : floating factor by which all elements of the range ouput are multiplied.
//!
//!   **Return value**
//!
//!   The  Fourier coefficients.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/fft/regular/naive_fft.cpp}
//!
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(fft_000_, fft_000);
}

#include <eve/module/fft/regular/impl/fft_000.hpp>
