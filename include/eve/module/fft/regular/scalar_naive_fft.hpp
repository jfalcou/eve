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
//!   @var naive_fft
//!   @brief Implement the raw fft
//!
//!   If \f$(a_i)_{0\le i\le n-1}\f$ denotes the coefficients of the trigonometric polynomial by increasing
//!   order,  the fft naive scheme evaluates the fourier transform coefficients of \f$p\f$ by \f$(c_i)_{0\le i\le n-1}\f$:
//!   \f$\displaystyle c_i = \sum_{k = 0}^{k = n-1} a_k e^{-s\frac{2i\pi k}n}\f$,  where s is \f$\pm1\f$.
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
//!     template< eve::Range R, floating_ordered_value T>
//!     auto fft(R a, T sign = 1, T fac = 1) noexcept;                                   //1
//!
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
//!   The Range contained of the transformed Fourier coefficients.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/fft/regular/naive_fft.cpp}
//!
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(naive_fft_, naive_fft);
  EVE_MAKE_CALLABLE(totally_naive_fft_, totally_naive_fft);
  
}

#include <eve/module/fft/regular/impl/naive_fft.hpp>
