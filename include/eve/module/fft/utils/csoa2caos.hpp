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
//!   @var csoa2caos
//!   @brief take a soa vector of eve::complex and return an aos std;:vector.
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
//!     auto csoa2caos(R const & f) noexcept;
//!
//!   @endcode
//!
//!   **Parameters**
//!     * `f  ` : soa  range of  complex arguments.
//!
//!   **Return value**
//!
//!     a std::vector containing a copy of the original data
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/fft/utils/soac2ri.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(csoa2caos_, csoa2caos);

}

#include <eve/module/fft/utils/impl/csoa2caos.hpp>
