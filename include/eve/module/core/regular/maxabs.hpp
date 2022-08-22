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
//!   @var maxabs
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
//!      auto maxabs(T x, Ts ... xs) noexcept;
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `xs...` : [real](@ref eve::value) or [complex](@ref eve::complex) arguments
//!
//!    **Return value**
//!
//!    The value of the maximum of the absolute value of the arguments is returned.
//!
//!   @note
//!     * If any element of the inputs is a `Nan`, the corresponding output element
//!       is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/maxabs.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::maxabs[mask](x, ...)` provides a masked
//!     version of `maxabs` which is
//!     equivalent to `if_else(mask, maxabs(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/maxabs.cpp}
//!
//!   * eve::pedantic, eve::numeric
//!
//!     * The call `pedantic(maxabs)(x,args,...)`  ensures the conformity
//!       to the standard behaviour, that is
//!       for two parameters  (on an  [elementwise](@ref glossary_elementwise) basis)
//!       to be semanticaly equivalent to:
//!       `(|x| < |y|) ? |y| : |x|` and this behaviour is also ensured on n parameters calls
//!       as if this scheme was recursively used.
//!
//!     *  The call `numeric(maxabs)(x,args,...)`  ensures that  if any element of the
//!        inputs is not a `Nan`, the corresponding
//!        output element will not be a `Nan`.
//!
//!     **Example**
//!
//!        @godbolt{doc/core/pedantic/maxabs.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(maxabs_, maxabs);
}

#include <eve/module/core/regular/impl/maxabs.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/maxabs.hpp>
#endif
