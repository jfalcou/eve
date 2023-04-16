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
//!   @var soac2ri
//!   @brief take a soa vector of eve::complex and issue refs to two ranges of the real and imaginary parts.
//!
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
//!     template< range R>
//!     auto soac2ri(R & f) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!     * `f  ` : soa range of  complex arguments.
//!
//!   **Return value**
//!
//!     a hummi pair of floating pont ranges referencing the f real and imaginary parts of f
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/fft/utils/soac2ri.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(soac2ri_, soac2ri);

}

#include <eve/module/fft/utils/impl/soac2ri.hpp>
