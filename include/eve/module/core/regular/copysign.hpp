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
//!   @var copysign
//!   @brief Computes the [elementwise](@ref glossary_elementwise) composition of a value
//!   with the magnitude of the first parameter  and the bit of sign of the second one.
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
//!      template< eve::real_value T, eve::real_value T >
//!      T copysign(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [real](@ref eve::real_value) arguments.
//!
//!    **Return value**
//!
//!      The value of the [elementwise](@ref glossary_elementwise) composition of a
//!      value with the magnitude of `x` and the bit of sign of `y`
//!      is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/copysign.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::copysign[mask](x, ...)` provides a masked
//!     version of `copysign` which is
//!     equivalent to `if_else(mask, copysign(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/copysign.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(copysign_, copysign);
}

#include <eve/module/core/regular/impl/copysign.hpp>
