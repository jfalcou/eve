//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var floor
//!   @brief Computes the largest integer not greater than the input.
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
//!      T floor(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::value) or [complex](@ref eve::complex) argument.
//!
//!   **Return value**
//!
//!       The largest integer not greater than `x`.
//!
//!       The standard proposes 4 rounding modes namely: `FE_TONEAREST`, `FE_DOWNWARD`, `FE_UPWARD`,
//!       `FE_TOWARDZERO`. This function object implements the `FE_DOWNWARD` version.
//!
//!       For complex inputs the floor operation is applied to both real and imaginary parts.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/floor.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::floor[mask](x)` provides a masked version of `eve::floor` which is
//!     equivalent to `if_else (mask, floor(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/floor.cpp}
//!
//!   * eve::tolerant
//!
//!     The expression `tolerant(floor)(x, tol)` computes a tolerant floor value for `x`,
//!     where `x` must be a floating value.
//!
//!      * If `tol` is a floating value, computes the floor with
//!        a tolerance `tol` using Hagerty's FL5 function.
//!      * If `tol` is an integral value n, computes the floor of
//!        the next nth representable value in the `x` type.
//!      * If `tol` is omitted, the tolerance is taken to 3 times
//!        the machine \f$\epsilon\f$ in the `x` type (`3*eps(as(x))`).
//!
//!      @godbolt{doc/core/fuzzy/floor.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(floor_, floor);
}

#include <eve/module/core/regular/impl/floor.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/floor.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/floor.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/floor.hpp>
#endif
