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
//! @addtogroup math_trig
//! @{
//! @var secpi
//!
//! @brief Callable object computing secant from an input in \f$\pi\f$ multiples.
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
//!      template< eve::floating_value T >
//!      T secpi(T x) noexcept;                              //1
//!
//!      template< eve::floating_value T >
//!      as_complex_t<T> secpi(as_complex_t<T> z) noexcept;  //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!   *  `z`:   [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   1. Returns the [elementwise](@ref glossary_elementwise) secant of the input
//!      expressed in \f$\pi\f$ multiples.
//!
//!      The call `secpi(x)` is semantically equivalent to \f$\sec(\pi x)\f$.
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, Nan is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the secant of the input
//!      i.e. \f$\1/cos(z)\f$ expressed in \f$\pi\f$ multiples.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/secpi.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================

EVE_MAKE_CALLABLE(secpi_, secpi);
}

#include <eve/module/math/regular/impl/secpi.hpp>
