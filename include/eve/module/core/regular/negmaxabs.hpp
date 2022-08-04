//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var negmaxabs
//!   @brief Computes the negated value of the element of  the maximal absolute value.
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
//!      template< eve::value T,  eve::value Ts ...>
//!      eve::common_compatible_value<T, Ts ...> negmaxabs( T x, Ts ... xs ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,  `...xs`: [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The negated negated value of the element of the maximal  absolute value
//!    is returned.
//!
//!    **Note**
//!
//!     If any element of the inputs is a NaN,
//!     the corresponding output element is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/negmaxabs.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::negmaxabs[mask](x, ...)` provides a masked version of `eve::negmaxabs` which
//!     is equivalent to `eve::if_else (mask, negmaxabs(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/negmaxabs.cpp}
//!
//!   * eve::pedantic,  eve::numeric
//!
//!     The call `d(eve::negmaxabs)(...)`, where d is one of these two decorators has the
//!     same behaviour,  but internaly `d(eve::max)` is used.
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(negmaxabs_, negmaxabs);
}

#include <eve/module/core/regular/impl/negmaxabs.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/negmaxabs.hpp>
#endif
