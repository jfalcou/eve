//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
//!   @var trunc
//!   @brief Computes  the integral part of `x` with the same sign as  `x`.
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
//!      T trunc(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The integral part of `x` with the same sign as  `x`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/trunc.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::trunc[mask](x)` provides a masked version of `eve::trunc` which is
//!     equivalent to `if_else (mask, trunc(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/trunc.cpp}
//!
//!   * eve::tolerant
//!
//!     The expression `tolerant(trunc)(x, tol)` computes a tolerant truncated
//!     value for `x`, where `x` must be a floating value.
//!
//!        * If `tol` is a floating_value computes the truncation with
//!          a tolerance `tol` using Hagerty's FL5 function.
//!        * If `tol` is an integral_value n compute the truncation of
//!          the next or previous nth representable value in the `x` type.
//!        * If `tol` is omitted the tolerance is taken to 3 times
//!          the machine \f$\epsilon\f$ in the `x` type (`3*eps(as(x))`).
//!
//!      **Example**
//!
//!        @godbolt{doc/core/fuzzy/trunc.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(trunc_, trunc);
}

#include <eve/module/core/regular/impl/trunc.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/trunc.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/trunc.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/trunc.hpp>
#endif
