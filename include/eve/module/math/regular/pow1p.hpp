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
//! @addtogroup math_exp
//! @{
//! @var pow1p
//!
//! @brief Callable object computing pow1p: \f$(1+x)^y\f$.
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
//!      template< eve::floating_value T, eve::floating_value U >
//!      T pow1p(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`, `y`:   [floating real value](@ref eve::floating_real_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) power(1+x, y), with good accuracy,
//! even when `x` is  small.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/pow1p.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::pow1p[mask](x, y)` provides a masked version of `eve::pow1p` which is
//!     equivalent to `if_else (mask, pow1p(x, y), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/pow1p.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(pow1p_, pow1p);
}

#include <eve/module/math/regular/impl/pow1p.hpp>
