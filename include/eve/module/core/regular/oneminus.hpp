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
//!   @var oneminus
//!   @brief Computes the value of one minus the input.
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
//!      T oneminus(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) argument.
//!
//!    **Return value**
//!
//!    The value of `1-x` is returned.
//!
//!    @note
//!      If an  [element](@ref glossary_elementwise) of the expected result is not representable in
//!      the result type, the corresponding result [element](@ref glossary_elementwise) is
//!      undefined.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/oneminus.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::oneminus[mask](x, ...)` provides a masked
//!     version of `oneminus` which is
//!     equivalent to `if_else(mask, oneminus(x, ...), x)`
//!
//!   * eve::saturated
//!
//!      The call `saturated(oneminus)(x)` is semantically equivalent to `eve::saturated(eve::sub)(
//!      eve::one (as(x)), x)` and is never undefined.
//!
//! @}
//================================================================================================

EVE_MAKE_CALLABLE(oneminus_, oneminus);
}

#include <eve/module/core/impl/oneminus.hpp>
