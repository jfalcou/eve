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
//!   @var beta
//!   @brief Computes the beta function: \f$\displaystyle \mathbf{B}(x, y) = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}\f$ is returned.
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
//!      auto beta(T x,U y) noexcept;                                        //1
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto beta(eve::as_complex_t<T> x, U y) noexcept;                    //2
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto beta(T x, eve::as_complex_t<U> y) noexcept;                    //2
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto beta(eve::as_complex_t<T> x, eve::as_complex_t<U> y) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     1. `x`, `y`:  [strictly positive real floating argument](@ref eve::floating_real_value).
//!     2. `x`, `y`:  [real floating](@ref eve::floating_value) or [complex ](@ref eve::complex) arguments.
//!
//!   **Return value**
//!
//!     1.  \f$\displaystyle \mathbf{B}(x,y) = \int_0^1 t^{x-1}(1-t)^{y-1}\mbox{d}t\f$
//!     2.  The complex \f$\displaystyle  \mathbb{B}(x,y) = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}\f$ is returned.
//!
//!   @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/special/regular/beta.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/beta.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(beta_, beta);
}

#include <eve/module/special/regular/impl/beta.hpp>
