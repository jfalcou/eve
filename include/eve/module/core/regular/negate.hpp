//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/arch.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_arithmetic
  //! @{
  //!   @var negate
  //!   @brief Computes the [elementwise](@ref glossary_elementwise) product of the first parameter
  //!   by the sign of the second.
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
  //!      template< eve::value T, eve::value U >
  //!      eve::common_compatible_t<T, U> negate(T x, U y) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`:  [arguments](@ref eve::value).
  //!
  //!   **Return value**
  //!
  //!      The [elementwise](@ref glossary_elementwise) product of the first parameter
  //!      by the sign of the second is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/negate.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::negate[mask](x, ...)` provides a masked
  //!     version of `negate` which is
  //!     equivalent to `if_else(mask, negate(x, ...), x)`
  //!      **Example**
  //!
  //!        @godbolt{doc/core/raw/negate.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(negate_, negate);
}

#include <eve/module/core/regular/impl/negate.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/negate.hpp>
#endif
