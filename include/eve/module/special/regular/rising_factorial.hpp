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
    template<value I, floating_value T>
    constexpr EVE_FORCEINLINE as_wide_as_t<T, I> operator()(I a, T b) const noexcept
      requires (same_lanes_or_scalar<I, T>)
    {
      return this->behavior(as<as_wide_as_t<T, I>>{}, eve::current_api, this->options(), a, b);
    }

    EVE_CALLABLE_OBJECT(rising_factorial_t, rising_factorial_);
  };

  //================================================================================================
  //! @addtogroup special
  //! @{
  //!   @var rising_factorial
  //!   @brief  `elementwise_callable` object computing the rising Factorial function i.e. \f$\frac{\Gamma(x+a)}{\Gamma(x)}\f$.
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
  //!      // Regular overload
  //!      template<typename I, typename T> constexpr as_wide_as_t<T, I> rising_factorial(I a, T x) noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto rising_factorial[conditional_expr auto c](/*any of the above overloads*/) noexcept; // 2
  //!      constexpr auto rising_factorial[logical_value auto m](/*any of the above overloads*/)    noexcept; // 2
  //!
  //!      // Semantic options
  //!      constexpr auto rising_factoriale[raw]/*any of the above overloads*/)                     noexcept; // 3
  //!      constexpr auto rising_factorialee[pedantic](/*any of the above overloads*/)              noexcept; // 4
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `a`: [value](@ref eve::floating_value).
  //!     * `x`: [floating value](@ref eve::floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. The value of the  rising_factorial is returned( `a` and `x` must be strictly positive).
  //!     2. [The operation is performed conditionnaly](@ref conditional).
  //!     3. The `raw` option  uses the crude formula with all its limitations and inacurracies and return a Nan if `a` and `a+x` are
  //!        not both positive.
  //!     4. The `pedantic` option  uses reflection tricks and computes
  //!        the function for all real `a` and `x`, returning nan if the result is really undefined.
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: Rising Factorial](https://mathworld.wolfram.com/RisingFactorial.html)
  //!   *  [Wikipedia: Falling and rising factorials](https://en.wikipedia.org/wiki/Falling_and_rising_factorials
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/special/rising_factorial.cpp}
  //================================================================================================
  inline constexpr auto rising_factorial = functor<rising_factorial_t>;
  //================================================================================================
  //! @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, typename I, typename T>
    constexpr EVE_FORCEINLINE as_wide_as_t<T, I> rising_factorial_(EVE_REQUIRES(cpu_), O const& o, I a, T x) noexcept
    {
      // Integral first parameter
      if constexpr (integral_value<I>)
      {
        if constexpr (integral_simd_value<I>)
        {
          using elt_t = element_type_t<T>;
          using r_t   = as_wide_t<elt_t, cardinal_t<I>>;
          auto aa     = convert(a, as{elt_t{}});
          return rising_factorial[o](aa, r_t{x});
        }
        else if constexpr (integral_scalar_value<I>)
        {
          return rising_factorial[o](T{a}, x);
        }
      }
      else
      {
        if constexpr (O::contains(raw))
        {
          // raw direct computation not matter why. nan if a+x or x is non positive
          return eve::tgamma(x + a) / tgamma(a);
        }
        else if constexpr(O::contains(pedantic))
        {
          auto sga   = if_else(is_flint[pedantic](a), one, signgam(a));
          auto sgapx = if_else(is_flint[pedantic](a + x), one, signgam(a + x));
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
