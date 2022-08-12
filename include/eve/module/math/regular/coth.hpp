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
//! @addtogroup math_hyper
//! @{
//! @var coth
//!
//! @brief Callable object computing coth: \f$\frac{e^x+e^{-x}}{e^x-e^{-x}}\f$.
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
//!      T coth(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_real_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) hyperbolic cotangent of the input.
//!
//! In particular:
//!
//!   * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!   * If the element is \f$\pm\infty\f$, \f$\pm1\f$ is returned.
//!   * If the element is a `NaN`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/coth.cpp}
//!
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(coth_, coth);
}

#include <eve/module/math/regular/impl/coth.hpp>
