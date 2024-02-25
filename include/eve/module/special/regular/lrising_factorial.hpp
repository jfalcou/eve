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
  struct lrising_factorial_t : elementwise_callable < lrising_factorial_t, Options
                                                    , raw_option, pedantic_option
                                                    >
  {
    template<ordered_value I, floating_ordered_value T>
    constexpr EVE_FORCEINLINE as_wide_as_t<T, I> operator()(I a, T b) const noexcept { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(lrising_factorial_t, lrising_factorial_);
  };

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
//!      auto lrising_factorial(T x,U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     `a`, `x`:  [strictly positive real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!     The value of the natural logarithm of the rising_factorial is returned.
//!
//!   @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/lrising_factorial.cpp}
//!
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
  inline constexpr auto lrising_factorial = functor<lrising_factorial_t>;
}

#include <eve/module/special/regular/impl/lrising_factorial.hpp>
