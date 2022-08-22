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
//!   @var maxmag
//!   @brief Computes the  maximum  of the absolute value of its arguments.
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
//!      template< eve::value T, eve::value... Ts >
//!      eve::common_compatible_t<T, Ts...> maxmag(T x, Ts ... xs) noexcept;
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `xs...` :  [real](@ref eve::value) or [complex](@ref eve::complex) arguments.
//!
//!    **Return value**
//!
//!      The [elementwise](@ref glossary_elementwise) element of greatest absolute value is
//!      returned.
//!
//!      For instance for two elements:
//!
//!        * If `|x| >  |y|`,  `x` is returned.
//!        * If `|x| <  |y|`,  `y` is returned.
//!        * Otherwise `max(x, y)` is returned.
//!
//!      For n parameters the result is computed as if this scheme was recursively used.
//!
//!   @note
//!     * If any element of the inputs is a `Nan`, the corresponding output element
//!       is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/maxmag.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::maxmag[mask](x, ...)` provides a masked
//!     version of `maxmag` which is
//!     equivalent to `if_else(mask, maxmag(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/maxmag.cpp}
//!
//!   * eve::pedantic, eve::numeric
//!
//!     The behaviour of d(eve::maxmag)(x, y) (where d is one of these two decorators
//!     is identical except that if  `|x| == |y|`, `d(max)` is used.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/pedantic/maxmag.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(maxmag_, maxmag);
}

#include <eve/module/core/regular/impl/maxmag.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/maxmag.hpp>
#endif
