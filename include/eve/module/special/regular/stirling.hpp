/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup special
//! @{
//!   @var stirling
//!   @brief Computes the Stirling approximation of the \f$\Gamma\f$ function.
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_real_value T >
//!      T stirling(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!
//!     * `y` :  [real floating argument](@ref eve::floating_real_value).
//!
//!   **Return value**
//!
//!   The value of an approximation of the
//!   \f$\Gamma\f$ function by \f$\displaystyle \Gamma(x) \approx \sqrt{2 \pi} x^{x-\frac12}
//!   e^{-x} \left( 1 + \frac1{x} P(\frac1{x})\right)\f$, where \f$P\f$ is a polynomial,
//!   is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/stirling.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(stirling_, stirling);
}

#include <eve/module/special/regular/impl/stirling.hpp>
