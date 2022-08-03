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
  //!   @var nearest
  //!   @brief Computes the nearest integer to the input.
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
  //!      T nearest(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [argument](@ref eve::value).
  //!
  //!    **Return value**
  //!
  //!      Computes  [elementwise](@ref glossary_elementwise) the integer nearest to `x`.
  //!
  //!      If `x` is an exact half-integer the rouding is made to the nearest even integer.
  //!
  //!      The standard proposes 4 rounding modes namely: `FE_TONEAREST`, `FE_DOWNWARD`, `FE_UPWARD`, `FE_TOWARDZERO`.
  //!      This function object implements the `FE_TONEAREST` version.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/nearest.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve;::nearest[mask](x)` provides a masked version of `eve::nearest` which is
  //!     equivalent to `if_else (mask, nearest(x), x)`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/nearest.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(nearest_, nearest);
}

#include <eve/module/core/regular/impl/nearest.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/nearest.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/nearest.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/nearest.hpp>
#endif
