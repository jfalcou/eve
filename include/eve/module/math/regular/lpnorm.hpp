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
//! @var lpnorm
//!
//! @brief Callable object computing the lpnorm operation \f$ \left(\sum_{i = 0}^n
//! |x_i|^p\right)^{\frac1p} \f$.
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
//!      template< floating_value P, floating_value T, floating_value ... Ts>
//!      auto operator()(P p, T x,Ts ... args ) const noexcept
//!   }
//!   @endcode
//!
//!
//! **Parameters**
//!
//!   *  `p`            :   [floating values](@ref eve::floating_value)
//!   *  `x`, `... args`:   [floating real or complex values](@ref eve::floating_value)
//!
//! **Return value**
//!
//!   The result type is the [common value type](@ref common_value) of the absolute
//!   values of the  parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/lpnorm.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::lpnorm[mask](x, ...)` provides a masked version of `eve::lpnorm` which is
//!     equivalent to `if_else (mask, lpnorm(x, ...), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/lpnorm.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(lpnorm_, lpnorm);
}

#include <eve/module/math/regular/impl/lpnorm.hpp>
