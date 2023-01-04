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
//! @addtogroup math_log
//! @{
//! @var log1p
//!
//! @brief Callable object computing the natural logarithm of \f$1+x\f$: \f$\log(1+x)\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      T log1p(T x) noexcept;                                 //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> log1p(eve::complex<T> z) noexcept;     //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!   *  `z`:   [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   1. Returns the [elementwise](@ref glossary_elementwise) the natural logarithm of `1+x`
//!      This function is more precise than the expression `log(1+x)` if  `x` is close to zero.
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$-\infty\f$ is returned.
//!      * If the element is \f$\pm0\f$, \f$+0\f$ is returned.
//!      * If the element is \f$\infty\f$, \f$\infty\f$ is returned.
//!      * If the element is less than -1, `NaN` is returned.
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the natural logarithm of `1+z`.
//!      The behavior of this function is equivalent to `eve::log(1+z),  with better precision when
//!      `z` is   close to zero.
//!
//!  @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/math/regular/log1p.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/regular/log1p.cpp}
//!
//!   * Masked Call
//!
//!     The call `eve::log1p[mask](x)` provides a masked version of `eve::log1p` which is
//!     equivalent to `if_else (mask, log1p(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/log1p.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(log1p_, log1p);
}

#include <eve/module/math/regular/impl/log1p.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/math/regular/impl/simd/x86/log1p.hpp>
#endif
