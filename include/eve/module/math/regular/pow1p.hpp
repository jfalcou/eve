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
//! @addtogroup math_exp
//! @{
//! @var pow1p
//!
//! @brief Callable object computing pow1p: \f$(1+x)^y\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto pow1p(T x, U y) noexcept;                                       //1
//!
//!      template< eve::floating_value T, eve::floating_value U >           //2
//!      auto pow1p(eve::as_complex_t<T> x, U y) noexcept;
//!
//!      template< eve::floating_value T, eve::floating_value U >           //2
//!      auto pow1p(T x, eve::as_complex_t<U> y) noexcept;
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto pow1p(eve::as_complex_t<T> x, eve::as_complex_t<U> y) noexcept; //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!    `x`, `y`:   [real floating](@ref eve::floating_value) or [complex ](@ref eve::complex) arguments.
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) \f$(1+x)^y\f$, with good accuracy,
//! even when `x` is  small.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/pow1p.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::pow1p[mask](x, y)` provides a masked version of `eve::pow1p` which is
//!     equivalent to `if_else (mask, pow1p(x, y), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/pow1p.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(pow1p_, pow1p);
}

#include <eve/module/math/regular/impl/pow1p.hpp>
