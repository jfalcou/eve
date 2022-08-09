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
//!   @var beta
//!   @brief Computes the beta function. \f$\displaystyle \mathbb{B}(x,y) =
//!   \int_0^1 t^{x-1}(1-t)^{y-1}\mbox{d}t\f$
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
//!      template< eve::floating_real_value T, eve::floating_real_value U >
//!      eve:common_compatible_value<T,U>  beta(T x,U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [strictly positive real floating argument](@ref eve::floating_real_value).
//!
//!     * `y` :  [strictly positive real floating argument](@ref eve::floating_real_value).
//!
//!   **Return value**
//!
//!   The value of \f$\displaystyle \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}\f$ is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/beta.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(beta_, beta);
}

#include <eve/module/special/regular/impl/beta.hpp>
