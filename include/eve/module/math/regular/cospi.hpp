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
//! @var cospi
//!
//! @brief Callable object computing the cosine from an input in \f$\pi\f$ multiples.
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
//!      T cospi(T x) noexcept;                              //1
//!
//!      template< eve::floating_value T >
//!      as_complex_t<T> cospi(as_complex_t<T> x) noexcept;  //2
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
//!   1.  Returns the [elementwise](@ref glossary_elementwise) cosine of the input.
//!       The call `cospi(x)` is semantically equivalent to \f$\cos(\pi x)\f$.
//!       In particular:
//!
//!          * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!          * If the element is \f$\pm\1/2, \f$0\f$ is returned.
//!          * If the element is \f$\pm\infty\f$, Nan is returned.
//!          * If the element is a `Nan`, `Nan` is returned.
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the cosine of the input
//!      in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/math/cospi.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/cospi.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================

EVE_MAKE_CALLABLE(cospi_, cospi);
}

#include <eve/module/math/regular/impl/cospi.hpp>
