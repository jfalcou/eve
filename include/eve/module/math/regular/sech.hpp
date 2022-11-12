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
//! @addtogroup math_hyper
//! @{
//! @var sech
//!
//! @brief Callable object computing \f$\frac2{e^x-e^{-x}}\f$.
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
//!      T sech(T x) noexcept;                              //1
//!
//!      template< eve::floating_value T >
//!      as_complex_t<T> csch(as_complex_t<T> x) noexcept;  //2
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
//!   1. Returns the [elementwise](@ref glossary_elementwise) hyperbolic secant of the input.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, 1 is returned.
//!      * If the element is \f$\pm\infty\f$, \f$+0\f$ is returned.
//!      * If the element is a `NaN`, `NaN` is returned.
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the hyperbolic secant of the input
//!      The behavior of this function is equivalent to `eve::rec(eve::cosh(z))`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/sech.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(sech_, sech);
}

#include <eve/module/math/regular/impl/sech.hpp>
