//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
//!      template< eve::floating_real_value T, eve::floating_real_value U >
//!      eve:common_compatible_value<T,U>  lrising_factorial(T a,U x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `a` :  [real floating argument](@ref eve::floating_real_value).
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!
//!   **Return value**
//!
//!   The value of the natural logarithm of the rising_factorial is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/lrising_factorial.cpp}
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
