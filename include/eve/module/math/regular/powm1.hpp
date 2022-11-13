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
//! @var powm1
//!
//! @brief Callable object computing powm1: \f$x^y-1\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto powm1(T x, U y) noexcept;                                       //1
//!
//!      template< eve::floating_value T, eve::floating_value U >           //2
//!      auto powm1(eve::as_complex_t<T> x, U y) noexcept;
//!
//!      template< eve::floating_value T, eve::floating_value U >           //2
//!      auto powm1(T x, eve::as_complex_t<U> y) noexcept;
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto powm1(eve::as_complex_t<T> x, eve::as_complex_t<U> y) noexcept; //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`, `y`:   [floating real or complex values](@ref eve::floating_real_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) power minus one, with good accuracy,
//! even when `y` is very small, or when `x` is close to 1.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/powm1.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::powm1[mask](x, y)` provides a masked version of `eve::powm1` which is
//!     equivalent to `if_else (mask, powm1(x, y), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/powm1.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(powm1_, powm1);
}

#include <eve/module/math/regular/impl/powm1.hpp>
