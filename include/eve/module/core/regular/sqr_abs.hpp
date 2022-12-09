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
//! @addtogroup core_arithmetic
//! @{
//!   @var sqr_abs
//!   @brief Computes the square of the absolute value of the parameter.
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
//!      T sqr_abs(T x) noexcept;                   //1
//!
//!      template< eve::value T >
//!      T sqr_abs(eve::as_complex<T> z) noexcept;  //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real](@ref eve::ordered_value) argument.
//!     * `z` :  [complex](@ref eve::complex) argument.
//!
//!    **Return value**
//!
//!    1.  value containing the [elementwise](@ref glossary_elementwise)
//!        square of `eve::abs(x)`.
//!
//!    2.  square of the modulus of the complex argument,
//!        i.e `eve::sqr(eve::real(z)+ eve::sqr(eve::imag(z)))`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/sqr_abs.cpp}
//!
//! @}
//================================================================================================

EVE_MAKE_CALLABLE(sqr_abs_, sqr_abs);
}

#include <eve/module/core/regular/impl/sqr_abs.hpp>
