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
//! @var geommean
//!
//! @brief Callable object computing the geometric mean of the inputs.\f$ \left(\prod_{i = 1}^n
//! x_i\right)^{1/n} \f$.
//!
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
//!      template<fvalue T, value ... Ts>
//!      auto geommean( T x, Ts ... args ) const noexcept
//!   }
//!   @endcode
//!
//!
//! **Parameters**
//!
//!   ``x`, `... args`:   [floating real or complex values](@ref eve::floating_value)
//!
//! **Return value**
//!
//!   *  The geometric mean of the inputs is returned
//!
//!   *  The result type is the [common value type](@ref common_value) of the parameters.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/geommean.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::geommean[mask](x, ...)` provides a masked version of `eve::geommean` which is
//!     equivalent to `if_else (mask, geommean(x, ...), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/geommean.cpp}
//!  @}
//================================================================================================

EVE_MAKE_CALLABLE(geommean_, geommean);
}

#include <eve/module/math/regular/impl/geommean.hpp>
