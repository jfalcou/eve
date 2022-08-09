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
//!   @var oneminus
//!   @brief \f$ x \rightarrow 1-x\f$.
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
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of 1-`x` is returned.
//!
//!    @note
//!
//!      If an  [element](@ref glossary_elementwise) of the expected result is not representable in
//!      the result type, the corresponding result [element](@ref glossary_elementwise) is
//!      undefined.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/oneminus.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::oneminus[mask](x, ...)` provides a masked
//!     version of `oneminus` which is
//!     equivalent to `if_else(mask, oneminus(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/oneminus.cpp}
//!
//!   * eve::saturated
//!
//!      The call `saturated(oneminus)(x)` is semantically equivalent to `eve::saturated(eve::sub)(
//!      eve::one (as(x)), x)` and is never undefined.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/saturated/oneminus.cpp}
//! @}
//================================================================================================

EVE_MAKE_CALLABLE(oneminus_, oneminus);
}

#include <eve/module/core/regular/impl/oneminus.hpp>
