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
//! @addtogroup math_invhyper
//! @{
//! @var acsch
//!
//! @brief Callable object computing \f$\log(1/x+\sqrt{1/x^2+1})\f$.
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
//!      T acsch(T x) noexcept;                                    //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> acsch(eve::complex<T> z) noexcept;        //2
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
//!   1. Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cosine of the input.
//!      The inverse hyperbolic sine is semantically equivalent to  \f$\log(1/x+\sqrt{1/x^2+1})\f$.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm\infty\f$, \f$\pm0\f$ returned.
//!      * If the element is \f$\pm1\f$, \f$\pm\infty\f$ is returned.
//!      * If the element does not belong \f$]0,1[\f$, `NaN` is returned.
//!
//!   2. Returns the complex arc hyperbolic cosecant of z, computed as \f$\mathop{\mathrm{asinh}}(1/z)\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/acsch.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(acsch_, acsch);
}

#include <eve/module/math/regular/impl/acsch.hpp>
