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
//!   @var round
//!   @brief Computes the integer nearest to the input.
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
//!      template< eve::value T >
//!      T round(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The largest integer not greater than `x`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/round.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::round[mask](x)` provides a masked version of `eve::round` which is
//!     equivalent to `if_else (mask, round(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/round.cpp}
//!
//!   * eve::downward
//!
//!     The expression `eve::downward(eve::round)(x)` is equivalent to `eve::floor(x)`.
//!
//!   * eve::upward
//!
//!     The expression `eve::upward(eve::round)(x)` is equivalent to `eve::ceil(x)`.
//!
//!   * eve::to_nearest
//!
//!     The expression `to_nearest(eve::round)(x)` is equivalent to `eve::nearest(x)`.
//!
//!   * eve::toward_zero
//!
//!     The expression `eve::toward_zero(eve::round)(x)` is equivalent to `eve::trunc(x)`.
//!
//!      @godbolt{doc/core/roundings/round.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(round_, round);
}

#include <eve/module/core/regular/impl/round.hpp>
