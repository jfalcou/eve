//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var minmax
//!   @brief Computes the minimum and maximum of its arguments.
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
//!      template<eve::value T, eve::value... Ts >
//!      auto minmax(T x, Ts ... xs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `xs...` :  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    A tuple containing the value of the minimum and the maximum of the arguments.
//!
//!   @note
//!     * If any element of the inputs is a `Nan`, the corresponding output element
//!       is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/minmax.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::minmax[mask](x, ...)` provides a masked version of `minmax` which is
//!     equivalent to `if_else(mask, minmax(x, ...), x)`
//!
//!     **Example**
//!
//!       @godbolt{doc/core/masked/minmax.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(minmax_, minmax);
}

#include <eve/module/core/regular/impl/minmax.hpp>
