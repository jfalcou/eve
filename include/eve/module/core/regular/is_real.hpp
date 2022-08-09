//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_real
//!   @brief Returns a logical true  if and only if the element value is real.
//!
//!   For real entries always return true.
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
//!      eve::as_logical<T> is_real(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    Returns [elementwise](@ref glossary_elementwise) true for real entries.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_real.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_real[mask](x)` provides a masked version of `eve::is_real` which is
//!     equivalent to `if_else (mask, is_real(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_real.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_real_, is_real);
}

#include <eve/module/core/regular/impl/is_real.hpp>
