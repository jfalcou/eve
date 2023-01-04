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
//! @addtogroup math_invtrig
//! @{
//! @var acscpi
//!
//! @brief Callable object computing he arc cosecant in \f$\pi\f$ multiples.
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
//!      T acscpi(T x) noexcept;                                   //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> acscpi(eve::complex<T> z) noexcept;       //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!   *  `z`:   [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   1.  Returns the [elementwise](@ref glossary_elementwise) arc cosecant of the
//!       input in the range \f$[-\frac12, \frac12]\f$.
//!
//!       In particular:
//!
//!        * If the element is \f$\pm1\f$, \f$\pm\frac12\f$ is returned.
//!        * If the element \f$|x| < 1\f$, `NaN` is returned.
//!        * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
//!        * If the element is a `Nan`, `NaN` is returned.
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the complex value in
//!     \f$\pi\f$ multiples of the arc cosecant of the input.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/acscpi.cpp}
//!  @}
//================================================================================================

EVE_MAKE_CALLABLE(acscpi_, acscpi);
}

#include <eve/module/math/regular/impl/acscpi.hpp>
