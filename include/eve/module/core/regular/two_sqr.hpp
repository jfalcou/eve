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
//! @addtogroup core_accuracy
//! @{
//!   @var two_sqr
//!   @brief Computes the [elementwise](@ref glossary_elementwise)
//!   pair of  sqruct and error,
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
//!      template< eve::floating_value T, eve::floating_value U  >
//!      auto two_sqr(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     Computes [elementwise](@ref glossary_elementwise) a pair of values `[a,e]` such that:
//!
//!     * `a` is `x*x`
//!     * `e` is a value such that `a`\f$\oplus\f$`e` is equal to `x`\f$\otimes\f$`x`
//!
//!    where \f$\oplus\f$ (resp. \f$\otimes\f$) adds (resp. multiplies) its two parameters with
//!    infinite precision.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/two_sqr.cpp}
//!
//! @}
//================================================================================================

EVE_MAKE_CALLABLE(two_sqr_, two_sqr);
}

#include <eve/module/core/regular/impl/two_sqr.hpp>
