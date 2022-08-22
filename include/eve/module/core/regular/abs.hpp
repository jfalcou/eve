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
//!      T abs(T x) noexcept;                  //1
//!
//!      template< eve::floating_value T >
//!      T abs(eve::as_complex<T> z) noexcept; //2
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real argument](@ref eve::value).
//!     * `z` :  [complex argument ](@ref eve::complex).
//!
//!    **Return value**
//!
//!    1.  value containing the [elementwise](@ref glossary_elementwise)
//!        absolute value of `x` if it is representable in this type.
//!
//!        More specifically, for signed integers : the absolute value of eve::valmin
//!        is not representable and the result is undefined.
//!
//!
//!    2.  modulus of the complex argument,  i.e `eve::hypot(eve::real(z), eve::imag(z))`
//!
//!  @warning
//!        abs is also a standard library function name and there possibly
//!        exists a C macro version which may be called instead of the EVE version.
//!        To avoid confusion, use the eve::abs notation.
//!
//!  @groupheader{Example}
//!
//!    **Real version**
//!
//!  @godbolt{doc/core/regular/abs.cpp}
//!
//!    **Complex version**
//!
//!  @godbolt{doc/complex/abs.cpp}
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
//!   * eve::pedantic
//!
//!     The call `eve::pedantic(eve::abs)(z)` computes a pedantic version of the modulus.
//!
//!     More specifically, `pedantic(eve::hypot)` is used in place of `eve::hypot)`
//!     for complex inputs
//!
//!      **Example**
//!
//!        @godbolt{doc/complex/pedantic/abs.cpp}
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
