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
//! @addtogroup special
//! @{
//!   @var digamma
//!   @brief Computes the Digamma function i.e. the logarithmic derivative of the \f$\Gamma\f$
//!   function.
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
//!      T digamma(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    `x`:   [real](@ref eve::value) or [complex](@ref eve::complex) argument.
//!
//!   **Return value**
//!
//!   The value of the Digamma function: \f$\frac{\Gamma'(x)}{\Gamma(x)}\f$ is returned.
//!
//!   @groupheader{Example}
//!    **Real version**
//!
//!   @godbolt{doc/special/regular/digamma.cpp}
//!
//!    **Complex version**
//!
//!   @godbolt{doc/complex/regular/digamma.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(digamma_, digamma);
}

#include <eve/module/special/regular/impl/digamma.hpp>
