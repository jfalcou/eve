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
//! @var cos
//!
//! @brief Callable object computing the cosine.
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
//!      T cos(T x) noexcept;                              //1
//!
//!      template< eve::floating_value T >
//!      as_complex_t<T> cos(as_complex_t<T> z) noexcept;  //2
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
//!   1. Returns the [elementwise](@ref glossary_elementwise) cosine of the input.
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, Nan is returned.
//!      * If the element is a `Nan`, `Nan` is returned.
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the cosine of the input
//!      The behavior of this function is equivalent to `eve::cosh(i*z)`.
//!
//!  @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/math/cos.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/cos.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================

EVE_MAKE_CALLABLE(cos_, cos);
}

#include <eve/module/math/regular/impl/cos.hpp>
