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
//! @var cosh
//!
//! @brief Callable object computing \f$\frac{e^x+e^{-x}}2\f$.
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
//!      T cosh(T x) noexcept;                                    //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> cosh(eve::complex<T> z) noexcept;        //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!   *  `z`:   [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   1. Returns the [elementwise](@ref glossary_elementwise) hyperbolic cosine of the input.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, 1 is returned.
//!      * If the element is \f$\pm\infty\f$, \f$+\infty\f$ is returned.
//!      * If the element is a `NaN`, `NaN` is returned.
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the complex value
//!      of the hyperbolic cosine of the input.
//!
//!      * for every z: `eve::cosh(eve::conj(z)) == eve::conj(std::cosh(z))`
//!      * for every z: `eve::cosh(-z)           == eve::cosh(z)`
//!      *  If z is \f$0\f$, the result is \f$1\f$
//!      *  If z is \f$i \infty\f$, the result is \f$NaN\f$
//!      *  If z is \f$i NaN\f$, the result is \f$NaN\f$
//!      *  If z is \f$x+i \infty\f$ (for any finite non-zero x), the result is \f$NaN+i NaN\f$
//!      *  If z is \f$x+i NaN\f$ (for any finite non-zero x), the result is \f$NaN+i NaN\f$
//!      *  If z is \f$\infty+i 0\f$, the result is \f$\infty+i 0\f$
//!      *  If z is \f$\infty,y\f$ (for any finite non-zero y), the result is \f$\infty \mathrm{cis}\times(y)\f$
//!      *  If z is \f$\infty+i \infty\f$, the result is \f$\pm \infty+i NaN\f$  (the sign of the real part is unspecified)
//!      *  If z is \f$\infty+i NaN\f$, the result is \f$\infty+i NaN\f$
//!      *  If z is \f$NaN\f$, the result is \f$NaN\f$
//!      *  If z is \f$NaN+i y\f$ (for any finite non-zero y), the result is \f$NaN+i NaN\f$
//!      *  If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!      where \f$\mathrm{cis}(y) =  \cos(y)+i\sin(y)\f$
//!
//!  @groupheader{Example}
//!
//!    **Real version**
//!
//!  @godbolt{doc/math/regular/cosh.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/regular/cosh.cpp}
//!
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(cosh_, cosh);
}

#include <eve/module/math/regular/impl/cosh.hpp>
