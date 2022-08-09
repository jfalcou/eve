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
//! @addtogroup core_arithmetic
//! @{
//!   @var lerp
//!   @brief Computes the  linear interpolation.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T, eve::floating_value U, eve::floating_value V >
//!      eve::common_compatible_t<T, U> lerp(T x, U y, V t) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `t`:  [floating arguments](@ref eve::floating_value).
//!
//!    **Return value**
//!
//!    The value of the interpolation (or extrapolation)  between `x` and `y` is returned.
//!    The call is semantically equivalent to `x+t*(y-x)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/lerp.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::lerp[mask](x, ...)` provides a masked
//!     version of `lerp` which is
//!     equivalent to `if_else(mask, lerp(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/lerp.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(lerp_, lerp);
}

#include <eve/module/core/regular/impl/lerp.hpp>
