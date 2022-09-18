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
//! @addtogroup special
//! @{
//!   @var erf
//!   @brief Computes the error function: \f$ \displaystyle
//!   \mbox{erf}(x)=\frac{2}{\sqrt\pi}\int_0^{x} e^{-t^2}\mbox{d}t\f$ or
//!   its analytic continuation in the complex plane
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_real_value T >
//!      T erf(T x) noexcept;                                  //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> erf(eve::complex<T> z) noexcept;      //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!     * `z`:  [complex ](@ref eve::complex) value.
//!
//!    **Return value**
//!
//!    The value of the error function is returned. In particular:
//!
//!      * If the argument is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the argument is \f$\pm\infty\f$, \f$\pm1\f$ is returned.
//!      * If the argument is Nan, nan returned.
//!
//!   @groupheader{Example}
//!
//!   **Real version**
//!
//!   @godbolt{doc/special/regular/erf.cpp}
//!
//!   **Complex version**
//!
//!   @godbolt{doc/complex/erf.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(erf_, erf);
}

#include <eve/module/special/regular/impl/erf.hpp>
