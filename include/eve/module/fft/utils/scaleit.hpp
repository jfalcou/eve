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
//!   @var scaleit
//!   @brief take a range and scale it by a factor
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
//!     template<D decorator, range R, value T>
//!     auto scaleit(R & f, T fac) noexcept;
//!
//!     template<D decorator, range R, value T>
//!     auto scaleit(R & fr, R &fi, T fac) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!     * `f`   : range of  complex or real arguments.
//!     * `fr   : range of  real arguments
//!     * `fi   : range of  real arguments (of same size as fr)
//!     * `fac` : scale factor.
//!
//!   **Return value**
//!
//!     all elements of f or (rf, if) are scaled by fac.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/fft/utils/scaleit.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(scaleit_, scaleit);

}

#include <eve/module/fft/utils/impl/scaleit.hpp>