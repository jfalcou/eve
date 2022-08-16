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
//! @var sinh
//!
//! @brief Callable object computing \f$\frac{e^x-e^{-x}}2\f$.
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
//!      T sinh(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) hyperbolic sine of the input.
//!
//! In particular:
//!
//!   * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!   * If the element is \f$\pm\infty\f$, \f$\pm\infty\f$ returned.
//!   * If the element is a `NaN`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/sinh.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(sinh_, sinh);
}

#include <eve/module/math/regular/impl/sinh.hpp>
