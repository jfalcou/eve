//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct rising_factorial_t : elementwise_callable<rising_factorial_t, Options, raw_option, pedantic_option, regular_option>
  {
    template<eve::value I, eve::floating_ordered_value T>
    EVE_FORCEINLINE
    auto operator()(I a, T b) const noexcept { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(rising_factorial_t, rising_factorial_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var rising_factorial
//!   @brief Computes the Rising Factorial function i.e. \f$\frac{\Gamma(x+a)}{\Gamma(x)}\f$.
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
//!      auto rising_factorial(T x,U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     `a`, `x`:  [strictly positive real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of the natural logarithm of the rising_factorial is returned.
//!
//!   @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/rising_factorial.cpp}
//!
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   @groupheader{Semantic Modifiers}
//!
//!   * eve::raw
//!
//!     The expression `raw(rising_factorial)(a,x)` uses the crude formula with all
//!     its limitations and innacuracies and return a Nan if `a` and `a+x` are
//!     not both positive.
//!
//!      **Example**
//!
//!     @godbolt{doc/special/raw/rising_factorial.cpp}
//!
//!   * eve::pedantic
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
  inline constexpr auto rising_factorial = functor<rising_factorial_t>;
}

#include <eve/module/special/regular/impl/rising_factorial.hpp>
