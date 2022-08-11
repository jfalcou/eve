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
//!   @var sign_alternate
//!   @brief Computes \f$(-1)^n\f$.
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
//!      template< eve::signed_value T >
//!      T sign_alternate(T n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [argument](@ref eve::value). Must be signed integral or flint.
//!
//!    **Return value**
//!
//!      \f$(-1)^n\f$ is returned.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/sign_alternate.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::sign_alternate[mask](x)` provides a masked version of `eve::sign_alternate`
//!     which is equivalent to `if_else (mask, sign_alternate(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/sign_alternate.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(sign_alternate_, sign_alternate);
}

#include <eve/module/core/regular/impl/sign_alternate.hpp>
