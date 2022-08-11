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
//! @addtogroup core_predicates
//! @{
//!   @var is_not_real
//!   @brief Returns a logical true  if and only if the element value is not real.
//!
//!   For real entries always return false.
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
//!      template< eve::floating_value T >
//!      eve::as_logical<T> is_not_real(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    Returns [elementwise](@ref glossary_elementwise) false for real entries.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_not_real.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_not_real[mask](x)` provides a masked version of `eve::is_not_real` which
//!     is equivalent to `if_else (mask, is_not_real(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_not_real.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_not_real_, is_not_real);
}

#include <eve/module/core/regular/impl/is_not_real.hpp>
