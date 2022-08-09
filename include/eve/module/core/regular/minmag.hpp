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
//!   @var minmag
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
//!      eve::common_compatible_t<T, Ts...> minmag(T x, Ts ... xs) noexcept;
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `xs...` :  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!      The [elementwise](@ref glossary_elementwise) element of greatest absolute value is
//!      returned.
//!
//!      For instance for two elements:
//!
//!        * If `|x| <   |y|`,  `x` is returned.
//!        * If `|x| >   |y|`,  `y` is returned.
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
//!  @godbolt{doc/core/regular/minmag.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::minmag[mask](x, ...)` provides a masked
//!     version of `minmag` which is
//!     equivalent to `if_else(mask, minmag(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/minmag.cpp}
//!
//!   * eve::pedantic, eve::numeric
//!
//!     The behaviour of d(eve::minmag)(x, y) (where d is one of these two decorators
//!     is identical except that if  `|x| == |y|`, `d(max)` is used.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/pedantic/minmag.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(minmag_, minmag);
}

#include <eve/module/core/regular/impl/minmag.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/minmag.hpp>
#endif
