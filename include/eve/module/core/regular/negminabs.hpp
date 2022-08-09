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
//!   @var negminabs
//!   @brief Computes the negated value of the element of  the minimal absolute value.
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
//!      eve::common_compatible_value<T, Ts ...> negminabs( T x, Ts ... xs ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,  `...xs`: [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The negated negated value of the element of the minimal  absolute value
//!    is returned.
//!
//!    @note
//!
//!     If any element of the inputs is a NaN,
//!     the corresponding output element is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/negminabs.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::negminabs[mask](x, ...)` provides a masked version of `eve::negminabs` which
//!     is equivalent to `eve::if_else (mask, negminabs(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/negminabs.cpp}
//!
//!   * eve::pedantic,  eve::numeric
//!
//!     The call `d(eve::negminabs)(...)`, where d is one of these two decorators has the
//!     same behaviour,  but internally `d(eve::min)` is used.
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(negminabs_, negminabs);
}

#include <eve/module/core/regular/impl/negminabs.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/negminabs.hpp>
#endif
