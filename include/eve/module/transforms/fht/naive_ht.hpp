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
//! @addtogroup fht
//! @{
//!   @var naive_fft
//!   @brief Implement the raw ht discrete transform
//!
//!   If \f$(a_i)_{0\le i\le n-1}\f$ denotes the input coefficients,  the ht naive scheme
//!   evaluates the Hartley transform coefficients of \f$p\f$ by \f$(c_i)_{0\le i\le n-1}\f$:
//!   \f$\displaystyle c_i = f\sum_{k = 0}^{k = n-1} a_k \cos{-s\frac{2i\pi k}n}+ \sin{-s\frac{2i\pi k}n}\f$,
//!   where s is \f$\pm1\f$ and f is a real factor (generally \f$\frac1{\sqrt{n}}.
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/fht.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!     template< eve::Range R, floating_ordered_value T>
//!     void naive_fft(R a, T fac = 1, T sign = -1) noexcept;           //1
//!
//!     template< eve::Range rR, floating_ordered_value T>
//!     void naive_fft(R rar, rR ai, T fac = 1, T sign = -1) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `a`   :  soa range of complex or real.
//!     * `ar"  :  range of real parts
//!     * `ai"  :  range of imaginary parts
//!     * `fac` : floating factor by which all elements of the range ouput are multiplied.
//!     *  sign : \f$\pm1\f$ direction of the fft
//!
//!   **Return value**
//!
//!   void. the inputs are modified to contain the ht values.
//!
//!   @note Never uses this algorithm it is completely inefficient.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/fft/regular/naive_ht.cpp}
//!
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(naive_ht_, naive_ht);

}

#include <eve/module/transforms/fht/impl/naive_ht.hpp>
