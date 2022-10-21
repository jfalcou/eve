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
//! @addtogroup math_exp
//! @{
//!   @var significants
//!   @brief Computes the rounding to n significants digits of the first input.
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
//!      template< eve::value T, eve::integral_value N >
//!      eve::common_compatible_t<T, N> significants(T x, N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [floating argument](@ref eve::floating_value).
//!
//!     * `n` :  [integral value argument](@ref eve::integral_value).
//!
//!    **Return value**
//!
//!      Computes  [elementwise](@ref glossary_elementwise) the rounding to n
//!      significants digits of `x`.
//!      With null n the result is a NaN.
//!
//! @warning
//!   Floating numbers are not stored in decimal form. So if you try significants with
//!   a not exactly representable number the result can be not exactly what you expect.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/significants.cpp}
//! @}
EVE_MAKE_CALLABLE(significants_, significants);
}

#include <eve/module/math/regular/impl/significants.hpp>
