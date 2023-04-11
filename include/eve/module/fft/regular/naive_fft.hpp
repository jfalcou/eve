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
//!     void naive_fft(R a, T fac = 1, T sign = -1) noexcept;         //1
//!
//!     template< eve::Range R, floating_ordered_value T>
//!     void naive_fft(R ar, R ai, T fac = 1, T sign = -1) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `a`   :  soa range of complex.
//!     * `ar"  :  range of real parts
//!     * `ai"  :  range of imaginary parts
//!     * `fac` : floating factor by which all elements of the range ouput are multiplied.
//!     *  sign : \f$\pm1\f$ direction of the fft
//!
//!   **Return value**
//!
//!   void. the inputs are modified to contain the fft values.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/fft/regular/naive_fft.cpp}
//!
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(naive_fft_, naive_fft);

}

#include <eve/module/fft/regular/impl/naive_fft.hpp>
