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
//!   @var conj
//!   @brief Computes the the conjugate value.
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
//!      T conj(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     for real inputs the call reduces to identity.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/conj.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::conj[mask](x)` provides a masked version of `eve::conj` which is
//!     equivalent to `if_else (mask, conj(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/conj.cpp}
//!
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(conj_, conj);
}

#include <eve/module/core/regular/impl/conj.hpp>
