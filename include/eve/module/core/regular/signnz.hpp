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
//!   @var signnz
//!   @brief Computes the never zero sign of the parameter.
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
//!      T signnz(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!      * Computes  [elementwise](@ref glossary_elementwise) the never zero sign of `x`.
//!
//!      * For [real](@ref eve::value) `x`,  the call is semantically equivalent to:
//!        * If x is [positive](@ref eve::positive), 1 is returned.
//!        * If x is [negative](@ref eve::negative), -1 is returned.
//!
//!      *  Moreover for  [floating real value](@ref eve::floating_value)
//!         if x is `Nan`, the result is `Nan`
//!
//!    value containing the [elementwise](@ref glossary_elementwise)
//!    never zero sign of `x` 
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/signnz.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::signnz[mask](x)` provides a masked version of `eve::signnz` which is
//!     equivalent to `if_else (mask, signnz(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/signnz.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(signnz_, signnz);
}

#include <eve/module/core/regular/impl/signnz.hpp>
