//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var fdim
//!   @brief Computes the positive difference between the two parameters.
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
//!      template< eve::value T, eve::value U >
//!      T fdim(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [arguments](@ref eve::value).
//!
//!   **Return value**
//!
//!     Returns the  [elementwise](@ref glossary_elementwise) positive difference
//!     between `x` and `y`:
//!       * if `x>y`,   `x-y` is returned,
//!       * if `x<=y`,  `+0` is returned,
//!       * otherwise a `Nan` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/fdim.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::fdim[mask](x)` provides a masked version of `eve::fdim` which is
//!     equivalent to `if_else (mask, fdim(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/fdim.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(fdim_, fdim);
}

#include <eve/module/core/regular/impl/fdim.hpp>
