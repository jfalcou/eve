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
//! @var atan
//!
//! @brief Callable object computing the arc tangent.
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
//!      T atan(T x) noexcept;                                   //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> atan(eve::complex<T> z) noexcept;       //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   * `x`:   [floating real value](@ref eve::floating_ordered_value).
//!   * `z`:   [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   1. Returns the [elementwise](@ref glossary_elementwise) arc cotangent of the
//!      input in the range \f$[-\frac\pi2, \frac\pi2]\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm\frac\pi2\f$ is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!   2. Returns the [elementwise](@ref glossary_elementwise) the complex principal value
//!      of the arc tangent of the input in the range of a strip unbounded along the imaginary axis
//!      and in the interval \f$[-\pi/2, \pi/2]\f$ along the real axis.
//!
//!      special cases are handled as if the operation was implemented by \f$-i \mathrm{atanh}(i z)\f$
//!
//!  @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/math/regular/atan.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/regular/atan.cpp}
//!  @}
//================================================================================================


EVE_MAKE_CALLABLE(atan_, atan);
}

#include <eve/module/math/regular/impl/atan.hpp>
