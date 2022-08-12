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
//! @var acoth
//!
//! @brief Callable object computing acoth: \f$\frac{1}{2}\log((x+1)/(x-1))\f$.
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
//!      T acoth(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_real_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cotangent of the input.
//! The inverse hyperbolic sine is semantically equivalent to \f$\frac{1}{2}\log((x+1)/(x-1))\f$.
//!
//! In particular:
//!
//!   * If the element is \f$\pm1\f$, \f$\pm0\f$ is returned.
//!   * If the element is \f$\pm\infty\f$, \f$\pm1\f$ is returned.
//!   * If the element is less than one or a `NaN`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/acoth.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(acoth_, acoth);
}

#include <eve/module/math/regular/impl/acoth.hpp>
