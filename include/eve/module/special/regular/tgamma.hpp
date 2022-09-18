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
//!   @var tgamma
//!   @brief Computes \f$\displaystyle \Gamma(x)=\int_0^\infty t^{x-1}e^{-t}\mbox{d}t\f$ or
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
//!      template< eve::floating_value T >
//!      T tgamma(T x) noexcept;                                    //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> tgamma(eve::complex<T> z) noexcept;        //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_real_value).
//!   *  `z`:   [complex ](@ref eve::complex) value.
//!
//!   **Return value**
//!
//!   The value of \f$\Gamma\f$ is returned.
//!
//!   @groupheader{Example}
//!
//!   **Real version**
//!
//!   @godbolt{doc/special/regular/tgamma.cpp}
//!
//!   **Complex version**
//!
//!   @godbolt{doc/complex/tgamma.cpp}
//!
//! @}
//================================================================================================

EVE_MAKE_CALLABLE(tgamma_, tgamma);
}

#include <eve/module/special/regular/impl/tgamma.hpp>
