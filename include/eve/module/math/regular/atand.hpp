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
//! @var atand
//!
//! @brief Callable object computing arc tangent in degrees.
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
//!      T atand(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) arc cotangent of the
//! input in the range \f$[-90, 90]\f$.
//!
//! In particular:
//!
//!   * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!   * If the element is \f$\pm\infty\f$, \f$\pm\frac\pi2\f$ is returned.
//!   * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/atand.cpp}
//!  @}
//================================================================================================

EVE_MAKE_CALLABLE(atand_, atand);
}

#include <eve/module/math/regular/impl/atand.hpp>
