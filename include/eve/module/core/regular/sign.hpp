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
//!   @var sign
//!   @brief Computes the sign of the parameter.
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
//!      T sign(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!      * Computes  [elementwise](@ref glossary_elementwise) the sign of `x`.
//!
//!      * For [real](@ref eve::value) `x`,  the call is semantically equivalent to:
//!        * If x is greater than 0, 1 is returned.
//!        * If x is less than 0,  -1 is returned.
//!        * If x is zero, x is returned.
//!
//!      *  Moreover for  [floating real value](@ref eve::floating_value)
//!         if x is `Nan`, the result is `Nan`
//!
//!    value containing the [elementwise](@ref glossary_elementwise)
//!    sign of `x` if it is representable in this type.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/sign.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::sign[mask](x)` provides a masked version of `eve::sign` which is
//!     equivalent to `if_else (mask, sign(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/sign.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(sign_, sign);
}

#include <eve/arch.hpp>
#include <eve/module/core/regular/impl/sign.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/sign.hpp>
#endif
