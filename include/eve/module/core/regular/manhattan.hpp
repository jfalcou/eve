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
//!   @var manhattan
//!   @brief Computes the manhattan norm (\f$l_1\f$)  of its arguments.
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
//!      template< eve::value... Ts >
//!      auto manhattan(Ts ... xs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs ...` :   [real](@ref eve::value) or [complex](@ref eve::complex) arguments.
//!
//!    **Return value**
//!
//!    The value of the sum of the absolute value of the arguments is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/manhattan.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::manhattan[mask](x, ...)` provides a masked
//!     version of `manhattan` which is
//!     equivalent to `if_else(mask, eve::manhattan(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/manhattan.cpp}
//!
//!   * eve::pedantic
//!
//!     The call `eve::pedantic(eve::manhattan)(...)` computes
//!     a pedantic version of `eve::manhattan`.
//!     returning \f$\infty\f$ as soon as one of its parameter is infinite,
//!     regardless of possible `Nan` values.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/pedantic/manhattan.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(manhattan_, manhattan);
}

#include <eve/module/core/regular/impl/manhattan.hpp>
