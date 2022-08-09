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
//!   @var rsqrt
//!   @brief Computes the inverse of the square root of the parameter.
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
//!      template< eve::floating_value T >
//!      T rsqrt(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::floating_value).
//!
//!    **Return value**
//!
//!    value containing the [elementwise](@ref glossary_elementwise)
//!    inverse of the square root of `x`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/rsqrt.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::rsqrt[mask](x)` provides a masked version of `eve::rsqrt` which is
//!     equivalent to `if_else (mask, rsqrt(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/rsqrt.cpp}
//!
//!   * eve::raw
//!
//!     The call `raw(rsqrt)(x)`, call a proper system intrinsic if one exists, but with possibly
//!     very poor accuracy in return. Otherwise it uses the non-decorated call.
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(rsqrt_, rsqrt);
}

#include <eve/module/core/regular/impl/rsqrt.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/rsqrt.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/rsqrt.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/rsqrt.hpp>
#endif
