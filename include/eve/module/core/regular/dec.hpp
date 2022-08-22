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
//!   @var dec
//!   @brief return the input decremented by 1.
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
//!      T dec(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) or [complex](@ref eve::complex) argument.
//!
//!    **Return value**
//!
//!    The value of `x - 1` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/dec.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::dec[mask](x, ...)` provides a masked
//!     version of `dec` which is
//!     equivalent to `if_else(mask, dec(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/dec.cpp}
//!
//!   * eve::saturated
//!
//!       The call `saturated(dec)(x)` computes the saturated decrement of `x`.
//!       The only interest of this behaviour is that
//!       for integral type T  the call `saturated(dec)(Valmin<T>())` returns `Valmin<T>()`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/saturated/dec.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(dec_, dec);
}

#include <eve/module/core/regular/impl/dec.hpp>
