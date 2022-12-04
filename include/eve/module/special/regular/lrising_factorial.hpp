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
//!   @var lrising_factorial
//!   @brief Computes the natural logarithm of the Rising Factorial function i.e.
//!   \f$\log\left(\frac{\Gamma(x+a)}{\Gamma(x)}\right)\f$.
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
//!      template< eve::floating_ordered_value T, eve::floating_ordered_value U >
//!      auto lrising_factorial(T x,U y) noexcept;                                        //1
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto lrising_factorial(eve::as_complex_t<T> x, U y) noexcept;                    //2
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto lrising_factorial(T x, eve::as_complex_t<U> y) noexcept;                    //2
//!
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto lrising_factorial(eve::as_complex_t<T> x, eve::as_complex_t<U> y) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     1. `a`, `x`:  [strictly positive real floating argument](@ref eve::floating_ordered_value).
//!     2. `a`, `x`:  [real floating](@ref eve::floating_value) or [complex ](@ref eve::complex) arguments.
//!
//!   **Return value**
//!
//!     The value of the natural logarithm of the rising_factorial is returned.
//!
//!   @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/special/regular/lrising_factorial.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/lrising_factorial.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::raw
//!
//!     The expression `raw(lrising_factorial)(a,x)` uses the crude formula with all
//!     its limitations and inacurracies and return a Nan if `a` and `a+x` are
//!     not both positive.
//!
//!     @godbolt{doc/special/raw/lrising_factorial.cpp}
//!
//!  * eve::pedantic
//!
//!     The expression `pedantic(lrising_factorial)(a,x)` uses reflection tricks and computes
//!     the function for all real `a` and `x`, and in fact computes the logarithm of the absolute
//!     value of the Pochammer symbol \f$\log\left|\frac{\Gamma(x+a)}{\Gamma(x)}\right|\f$
//!     returning nan if the result is really undefined.
//!
//!      **Example**
//!
//!      @godbolt{doc/special/pedantic/lrising_factorial.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(lrising_factorial_, lrising_factorial);
}

#include <eve/module/special/regular/impl/lrising_factorial.hpp>
