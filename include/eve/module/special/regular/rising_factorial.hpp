//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup special
//! @{
//!   @var rising_factorial
//!   @brief Computes the  rising_factorial function i.e.
//!   \f$\frac{\Gamma(x+a)}{\Gamma(x)}\f$.
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
//!      auto rising_factorial(T a, U x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `a` :  [real floating argument](@ref eve::floating_real_value).
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!
//!    **Return value**
//!
//!    the value of the natural logarithm of the rising_factorial is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/rising_factorial.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::raw
//!
//!     The expression `raw(rising_factorial)(a,x)` uses the crude formula with all
//!     its limitations and inacurracies and return a Nan if `a` and `a+x` are
//!     not both positive.
//!
//!     @godbolt{doc/special/raw/rising_factorial.cpp}
//!
//!  * eve::pedantic
//!
//!     The expression `pedantic(rising_factorial)(a,x)` uses reflection tricks and computes
//!     the function for all real `a` and `x`, returning nan if the result is really undefined.
//!
//!      **Example**
//!
//!      @godbolt{doc/special/pedantic/rising_factorial.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(rising_factorial_, rising_factorial);
}

#include <eve/module/special/regular/impl/rising_factorial.hpp>
