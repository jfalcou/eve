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
  //!   @var abs
  //!   @brief Computes the absolute value of the parameter.
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
  //!      T abs(T x) noexcept;
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
  //!    absolute value of `x` if it is representable in this type.
  //!
  //!  **Notes**
  //!
  //!    * More specifically, for signed integers : the absolute value of eve::valmin
  //!      is not representable and the result is undefined.
  //!
  //!    * abs is also a standard library function name and there possibly
  //!      exists a C macro version which may be called instead of the EVE version.
  //!      To avoid confusion, use the eve::abs notation.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/abs.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve;::abs[mask](x)` provides a masked version of `eve::abs` which is
  //!     equivalent to `if_else (mask, abs(x), x)`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/abs.cpp}
  //!
  //!   * eve::saturated
  //!
  //!     The call `eve::saturated(eve::abs)(x)` computes a saturated version of eve::abs.
  //!
  //!     More specifically, for any signed integer value `x`, the expression
  //!     `eve::saturated(eve::abs)(eve::valmin(as(x)))` evaluates to `eve::valmax(as(x))`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/saturated/abs.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(abs_, abs);
}

#include <eve/module/core/regular/impl/abs.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/abs.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/abs.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/abs.hpp>
#endif
