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
#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/lrising_factorial.hpp>
#include <eve/module/special/regular/signgam.hpp>
#include <eve/module/special/regular/tgamma.hpp>
#include <eve/traits/common_value.hpp>

namespace eve
{
  template<typename Options>
  struct rising_factorial_t : strict_elementwise_callable<rising_factorial_t, Options, raw_option, pedantic_option>
  {
    template<ordered_value I, floating_ordered_value T>
    constexpr EVE_FORCEINLINE as_wide_as_t<T, I> operator()(I a, T b) const noexcept { return EVE_DISPATCH_CALL(a, b); }

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

  namespace detail
  {
    template<typename I, typename T, callable_options O>
    constexpr EVE_FORCEINLINE as_wide_as_t<T, I>
    rising_factorial_(EVE_REQUIRES(cpu_), O const& o, I a, T x) noexcept
    {
      // Integral first parameter
      if constexpr(integral_value<I> )
      {
        if constexpr( integral_simd_value<I> )
        {
          using elt_t = element_type_t<T>;
          using r_t   = as_wide_t<elt_t, cardinal_t<I>>;
          auto aa     = convert(a, as(elt_t()));
          return rising_factorial[o](aa, r_t(x));
        }
        else if constexpr( integral_scalar_value<I> )
        {
          return rising_factorial[o](T(a), x);
        }
      }
      else
      {
        if constexpr(O::contains(raw2))
        {
          // raw direct computation not matter why. nan if a+x or x is non positive
          return eve::tgamma(x + a) / tgamma(a);
        }
        else if constexpr(O::contains(pedantic2))
        {
          auto sga   = if_else(is_flint(a), one, signgam(a));
           auto sgapx = if_else(is_flint(a + x), one, signgam(a + x));
          return eve::exp(lrising_factorial[pedantic](a, x))*(sga * sgapx);
        }
        else
        {
          // regular  nan if a+x or x is nnegative,  better computation than raw
          return eve::exp(lrising_factorial(a, x));
        }
      }
    }
  }
}
