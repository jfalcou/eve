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
//!   @var ifft
//!   @brief take a fft object and datas and compute the inverse fft transform of the data
//!
//!   when applied to complex number ranges the inverse of a fft is simply given by applying the fft to the
//!   data where real and imaginary parts are swapped.
//!   ifft does the job by applying the chosen fft object function to the properly swapped datas.
//!
//!   The call depending of the data representation, two decorators can be
//!   used to specify that the ranges are soa or aos
//!   A separate call is provided if the datas are given in two ranges of real and imaginary parts
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
//!
//!     template< callable F, range R, value T>
//!     auto ifft(F const & fft, R & rf, R & if, T fac) noexcept;
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!     * `fft` : direct fft method
//!     * `f`   : soa range of  complex arguments.
//!     * `rf"  : range of  real parts.
//!     * `if"  : range of  imaginary parts.
//!     * `fac` : normalization factor.
//!
//!   **Return value**
//!
//!     f or (rf, if) contains after call the  fft scaled by fac of the swapped datas.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/transforms/utils/ifft.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(ifft_, ifft);

}

#include <eve/module/transforms/utils/impl/ifft.hpp>
