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
//!   @var inc
//!   @brief return the input incremented by one.
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
//!      T inc(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of `x+1` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/inc.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::inc[mask](x, ...)` provides a masked
//!     version of `inc` which is
//!     equivalent to `if_else(mask, inc(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/inc.cpp}
//!
//!   * eve::saturated
//!
//!       The call `saturated(inc)(x)` computes the saturated increment of `x`.
//!       The only interest of this behaviour is that
//!       for integral type T the call  `saturated(inc)(Valmax<T>())` returns `Valmax<T>()`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/saturated/inc.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(inc_, inc);
}

#include <eve/module/core/regular/impl/inc.hpp>
