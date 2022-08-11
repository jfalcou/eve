//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
//!   @var rec
//!   @brief Computes the inverse of the parameter.
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
//!      T rec(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    value containing the [elementwise](@ref glossary_elementwise)
//!    inverse value of `x`.
//!
//!  @note
//!     For [real integral value](@ref eve::value) `x` is semantically equivalent to:
//!       * If x==1 or x==-1, x is returned.
//!       * If x==0,  [the greatest representable positive value](@ref eve::valmax) is returned.
//!       * Otherwise 0 is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/rec.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::rec[mask](x)` provides a masked version of `eve::rec` which is
//!     equivalent to `if_else (mask, rec(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/rec.cpp}
//!
//!   * eve::raw
//!
//!     The call `raw(rec)(x)`, call a proper system intrinsic if one exists, but with possibly
//!     very poor accuracy in return. Otherwise it uses the non decorated call.
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(rec_, rec);
}

#include <eve/module/core/regular/impl/rec.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/rec.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/rec.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/rec.hpp>
#endif
