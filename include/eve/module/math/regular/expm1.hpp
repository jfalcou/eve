//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var expm1
//!
//! @brief Callable object computing \f$e^x-1\f$.
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
//!      T expm1(T x) noexcept;                              //1
//!
//!      template< eve::floating_value T >
//!      as_complex_t<T> expm1(as_complex_t<T> z) noexcept;  //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   * `x`:   [floating real](@ref eve::floating_real_value)
//!   * `z`:   [complex ](@ref eve::complex) argument.
//!
//! **Return value**
//!
//!   1. Returns the [elementwise](@ref glossary_elementwise) exponential of the input minus one, with good
//!      accuracy, even for small values of `x`.
//!
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned
//!      * If the element is \f$-\infty\f$, \f$-1\f$ is returned
//!      * If the element is \f$\infty\f$, \f$\infty\f$ is returned
//!      * If the element is a `NaN`, `NaN` is returned
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the exponential of the input minus one, with good
//!      accuracy, even for small values of `eve::abs(z)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/expm1.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::expm1[mask](x)` provides a masked version of `eve::expm1` which is
//!     equivalent to `if_else (mask, expm1(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/expm1.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(expm1_, expm1);
}

#include <eve/module/math/regular/impl/expm1.hpp>
