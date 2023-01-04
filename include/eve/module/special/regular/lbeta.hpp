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
//!   @var lbeta
//!   @brief Computes the natural logarithm of the beta function.
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
//!      template< eve::floating_ordered_value T, eve::floating_ordered_value U >
//!      auto lbeta(T x,U y) noexcept;                                        //1
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto lbeta(eve::as_complex_t<T> x, U y) noexcept;                    //2
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      autol beta(T x, eve::as_complex_t<U> y) noexcept;                    //2
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto lbeta(eve::as_complex_t<T> x, eve::as_complex_t<U> y) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     1. `x`, `y`:  [strictly positive real floating argument](@ref eve::floating_ordered_value).
//!     2. `x`, `y`:  [real floating](@ref eve::floating_value) or [complex ](@ref eve::complex) arguments.
//!
//!   **Return value**
//!
//!   **Real version**
//!
//!  @godbolt{doc/special/regular/lbeta.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/regular/lbeta.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(lbeta_, lbeta);
}

#include <eve/module/special/regular/impl/lbeta.hpp>
