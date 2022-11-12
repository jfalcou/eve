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
//! @var agd
//!
//! @brief Callable object computing the inverse gudermanian.
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
//!      T agd(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_real_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) inverse
//! [gudermanian](@ref eve::gd) of the input.
//!
//! In particular:
//!
//!   * If the element is \f$\pm0\f$, 0 is returned.
//!   * If the element is \f$\pm\pi/2\f$, \f$\infty\f$ is returned.
//!   * If the element is not in a  \f$[-\pi/2, \pi/2] \f$, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/agd.cpp}
//!
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(agd_, agd);
}

#include <eve/module/math/regular/impl/agd.hpp>
