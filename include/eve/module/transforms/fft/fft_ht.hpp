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
//! @addtogroup transforms
//! @{
//!   @var fft_ht
//!   @brief Implement the fast fourier transform using hartley transform.
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
//!     void fft_ht(R a, T fac = 1) noexcept;         //1
//!
//!     template< eve::Range R, floating_ordered_value T>
//!     void fft_ht(R ar, R ai, T fac = 1) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `a`   :  soa range of complex.
//!     * `ar"  :  range of real parts
//!     * `ai"  :  range of imaginary parts
//!     * `fac` : floating factor by which all elements of the range ouput are multiplied.
//!
//!   **Return value**
//!
//!   void. the inputs are modified to contain the fft values after call.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/fft/regular/naive_fft.cpp}
//!
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(fft_ht_, fft_ht);

}

#include <eve/module/transforms/fft/impl/fft_ht.hpp>
