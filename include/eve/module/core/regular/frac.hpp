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
//!   @var frac
//!   @brief Computes the fractional part of the input.
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
//!      T frac(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) argument.
//!
//!   **Return value**
//!
//!     Returns a value with the same type as `x`  containing the
//!     [elementwise](@ref glossary_elementwise) fractional part of `x`
//!     with the same sign as `x`.
//!
//!     In particular:
//!       * If an [element](@ref glossary_elementwise) of `x` is \f$\pm0\f$,  \f$\pm0\f$ is
//!         returned.
//!       * If an [element](@ref glossary_elementwise) of `x` is \f$\pm\infty\f$ or `Nan`, a
//!        `Nan` is returned.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/frac.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::frac[mask](x)` provides a masked version of `eve::frac` which is
//!     equivalent to `if_else (mask, frac(x), x)`.
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(frac_, frac);
}

#include <eve/module/core/impl/frac.hpp>
