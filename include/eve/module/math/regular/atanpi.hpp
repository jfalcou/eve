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
//! @var atanpi
//!
//! @brief Callable object computing arc tangent in \f$\pi\f$ multiples.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      T atanpi(T x) noexcept;                                  //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> acospi(eve::complex<T> z) noexcept;      //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_real_value).
//!   *  `z`:   [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   1. Returns the [elementwise](@ref glossary_elementwise) arc cotangent of the
//!      input in the range \f$[-\frac12, \frac12]\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm\frac\pi2\f$ is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the complex principal value
//!      of the arc tangent of the input in \f$\pi\f$ multiples.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/atanpi.cpp}
//!  @}
//================================================================================================


EVE_MAKE_CALLABLE(atanpi_, atanpi);
}

#include <eve/module/math/regular/impl/atanpi.hpp>
