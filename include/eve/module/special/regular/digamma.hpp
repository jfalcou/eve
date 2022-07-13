//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
//!      template< eve::floating_real_value T >
//!      T digamma(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!
//!    **Return value**
//!
//!    the value of the Digamma function \f$\frac{\Gamma'(x)}{\Gamma(x)}\f$ is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/digamma.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(digamma_, digamma);
}

#include <eve/module/special/regular/impl/digamma.hpp>
