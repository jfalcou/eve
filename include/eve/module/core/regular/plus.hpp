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
//!   @var plus
//!   @brief Computes the opposite of the parameter that must be signed.
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
//!      T plus(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!       Returns x
//!
//!    **Note**
//!       Although the operator notation with `+` is supported, the `+` operator on
//!       standard scalar type is the original one and so can lead to automatic promotion.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/plus.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::plus[mask](x)` provides a masked version of `eve::plus` which is
//!     equivalent to `if_else (mask, plus(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/plus.cpp}
//!
//!        @godbolt{doc/core/saturated/plus.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(plus_, plus);
}

#include <eve/module/core/regular/impl/plus.hpp>
