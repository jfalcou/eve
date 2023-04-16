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
//!   @var caos2csoa
//!   @brief take an aos vector of eve::complex and return an equivalent soa vector
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
//!     auto caos2csoa(R const & f) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!     * `f  ` : aos range of  complex arguments.
//!
//!   **Return value**
//!
//!      soa vector containing a copy of the original data
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/fft/utils/caos2csoa.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(caos2csoa_, caos2csoa);

}

#include <eve/module/fft/utils/impl/caos2csoa.hpp>
