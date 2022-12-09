//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup special
//! @{
//!   @var log_gamma
//!   @brief Computes the natural logarithm of the \f$\Gamma\f$ function.
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
//!      template< eve::floating_ordered_value T >
//!      T log_gamma(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :   [real](@ref eve::value) or [complex](@ref eve::complex) argument.
//!
//!   **Return value**
//!
//!   The value of the  logarithm of the \f$\Gamma\f$ function is returned.
//!
//!   @warning
//!       For real floating inputs this callable returns NaN if `eve::gamma(x)` is less than zero
//!
//!   @groupheader{Example}
//!
//!    **Real version**
//!
//!  @godbolt{doc/special/regular/log_gamma.cpp}
//!
//!    **Complex version**
//!
//!  @godbolt{doc/complex/log_gamma.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(log_gamma_, log_gamma);
}

#include <eve/module/special/regular/impl/log_gamma.hpp>
