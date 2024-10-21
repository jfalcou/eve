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
#include <eve/module/math.hpp>
#include <eve/module/special/regular/log_abs_gamma.hpp>
#include <eve/traits/common_value.hpp>

namespace eve
{
  template<typename Options>
  struct lrising_factorial_t : strict_elementwise_callable < lrising_factorial_t, Options
                                                            , raw_option, pedantic_option
                                                            >
  {
    template<value I, floating_value T>
    constexpr EVE_FORCEINLINE as_wide_as_t<T, I> operator()(I a, T b) const noexcept
      requires (same_lanes_or_scalar<I, T>)
    {
      return this->behavior(as<as_wide_as_t<T, I>>{}, eve::current_api, this->options(), a, b);
    }

    EVE_CALLABLE_OBJECT(lrising_factorial_t, lrising_factorial_);
  };

  //================================================================================================
  //! @addtogroup special
  //! @{
  //!   @var lrising_factorial
  //!   @brief `elementwise_callable` object computing the natural logarithm of the rising Factorial function i.e.
  //!   \f$\log\left(\frac{\Gamma(x+a)}{\Gamma(x)}\right)\f$.
  //!
  //!   @groupheader{Header file}
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
  //!      template<typename I, typename T> constexpr as_wide_as_t<T, I> lrising_factorial(I a, T x) noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto lrising_factorial[conditional_expr auto c](/*any of the above overloads*/) noexcept; // 2
  //!      constexpr auto lrising_factorial[logical_value auto m](/*any of the above overloads*/)    noexcept; // 2
  //!
  //!      // Semantic options
  //!      constexpr auto lrising_factoriale[raw]/*any of the above overloads*/)                     noexcept; // 3
  //!      constexpr auto lrising_factorialee[pedantic](/*any of the above overloads*/)              noexcept; // 4
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
  //!     1. The value of the natural logarithm of the rising_factorial is returned( `a` and `x` must be strictly positive).
  //!     2. [The operation is performed conditionnaly](@ref conditional).
  //!     3. The `raw` option  uses the crude formula with all its limitations and inacurracies and return a Nan if `a` and `a+x` are
  //!        not both positive.
  //!     4. The `pedantic` option  uses reflection tricks and computes
  //!        the function for all real `a` and `x`, and in fact computes the logarithm of the absolute
  //!        value of the Pochammer symbol \f$\log\left|\frac{\Gamma(x+a)}{\Gamma(x)}\right|\f$
  //!        returning nan only if the result is really undefined.
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: Rising Factorial](https://mathworld.wolfram.com/RisingFactorial.html)
  //!   *  [Wikipedia: Falling and rising factorials](https://en.wikipedia.org/wiki/Falling_and_rising_factorials
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/special/regular/lrising_factorial.cpp}
  //================================================================================================
  inline constexpr auto lrising_factorial = functor<lrising_factorial_t>;
  //================================================================================================
  //! @}
  //================================================================================================

  namespace detail
  {

    /////////////////////////////////////////////////////////////////////////////////////////
    //utilities

    template<typename T>
    constexpr EVE_FORCEINLINE auto inner_lrising_factorial(T a, T x) noexcept
    {
      // Assumes a>0 and a+x>0.
      auto ax      = eve::abs(x);
      auto notdone = is_nlez(a) && is_nlez(a + x);
      auto r       = nan(as(x));
      auto lr0     = [](auto aa, auto xx) { return log_abs_gamma(xx + aa) - log_abs_gamma(aa); };

      auto lr1 = [](auto aa, auto xx){
        const auto xxoaa = xx / aa;
        const auto den = inc(xxoaa);
        const auto d2  = sqr(den);
        const auto d3  = den * d2;
        const auto d5  = d3 * d2;
        const auto d7  = d5 * d2;
        const auto c1  = -xxoaa / den;
        const auto c3  = -xxoaa * (3 + xxoaa * (3 + xxoaa)) / d3;
        const auto c5  = -xxoaa * (5 + xxoaa * (10 + xxoaa * (10 + xxoaa * (5 + xxoaa)))) / d5;
        const auto c7 =
        -xxoaa * (7 + xxoaa * (21 + xxoaa * (35 + xxoaa * (35 + xxoaa * (21 + xxoaa * (7 + xxoaa)))))) / d7;
        const auto p8    = eve::pow(inc(xxoaa), 8);
        const auto c8    = dec(rec[pedantic](p8));            /* these need not   */
        const auto c9    = dec(rec[pedantic](p8 * inc(xxoaa))); /* be very accurate */
        const auto a2    = sqr(aa);
        const auto a4    = sqr(a2);
        const auto a6    = a4 * a2;
        const auto ser_1 = c1 + c3 / (30 * a2) + c5 / (105 * a4) + c7 / (140 * a6);
        const auto ser_2 = c8 / (99 * a6 * a2) - 691 * c9 / (a6 * a4) / 360360;
        const auto ser   = (ser_1 + ser_2) / (12 * aa);
        auto       term1 = xx * dec(eve::log(aa)); // eve::log(aa/M_E);
        auto       lg    = eve::log1p(xxoaa);
        auto       term2 = (xx + aa - half(as(xx))) * lg;
        return term1 + term2 + ser;
      };

      auto lr2 = [](auto aa, auto xx){
        return if_else(dist(xx + aa, aa) < 10 * aa * eps(as{aa}),
                       eve::log1p(xx * digamma(aa)),
                       log_abs_gamma(aa + xx) - log_abs_gamma(aa));
      };

      if( eve::any(notdone) )
      {
        auto test0 = (10 * ax > a) || (10 * ax * log(eve::max(a, T(2))) > one(as{x}));
        notdone    = next_interval(lr0, notdone, test0, r, a, x);
        if( eve::any(notdone) )
        {
          auto test1 = (10 * ax <= a) && (a > T(15));
          notdone    = next_interval(lr1, notdone, test1, r, a, x);
          if( eve::any(notdone) ) { notdone = last_interval(lr2, notdone, r, a, x); }
        }
      }
      return r;
    }
    // end utilities
    /////////////////////////////////////////////////////////////////////////////////////////

    template<callable_options O, typename I, typename T>
    constexpr as_wide_as_t<T, I> lrising_factorial_(EVE_REQUIRES(cpu_), O const& o, I a, T x) noexcept
    {
      // Integral first parameter
      if constexpr(integral_value<I> )
      {
        if constexpr( integral_simd_value<I> )
        {
          using elt_t = element_type_t<T>;
          using r_t   = as_wide_t<elt_t, cardinal_t<I>>;
          auto aa     = convert(a, as<elt_t>{});
          return lrising_factorial[o](aa, r_t(x));
        }
        else if constexpr( integral_scalar_value<I> )
        {
          return lrising_factorial[o](T(a), x);
        }
      }
      else
      {
        if constexpr(O::contains(raw))
        {
          // raw direct computation not matter why. nan if a+x or x is non positive
          auto notdone = is_nlez(x) && is_nlez(a + x);
          return if_else(notdone, log_abs_gamma(x + a) - log_abs_gamma(a), allbits);
        }
        else if constexpr(O::contains(pedantic))
        {
          // pedantic computes also for negative values and even negative integer values
          auto r       = nan(as{a});
          auto notdone = is_not_nan(a) && is_not_nan(x);

          auto lr0 = []() { return zero(as<T>{}); };

          auto lrpos = [](auto aa, auto xx) { return inner_lrising_factorial(aa, xx); };

          auto lrnegint = [](auto aa, auto xx){ // a and a+x are negative integers uses reflection.
            auto rr = inner_lrising_factorial(-aa, -xx);
            return -eve::log1p(xx / aa) - rr;
          };

          auto lraeqmx = [](auto aa, auto){  // a+x = 0
            return log_abs_gamma(inc(aa));
          };

          auto lraneqmx = [](auto aa, auto){ // a < 0.0 && a+x < 0.0
            return minf(as{aa});
          };

          auto lrneg = [](auto aa, auto xx){
            // Reduce to positive case using reflection.
            auto oma      = oneminus(aa);
            auto spioma   = sinpi(oma);
            auto spiomamx = sinpi(oma - xx);
            auto rr       = inner_lrising_factorial(oma, -xx);
            auto lnterm   = eve::log(eve::abs(spioma / spiomamx));
            return if_else(is_nez(spiomamx * spioma), lnterm - rr, allbits);
          };

          auto lrlast = [](auto aa, auto xx) { return eve::log_abs_gamma(aa + xx) - eve::log_abs_gamma(aa); };

          if( eve::any(notdone) )
          {
            notdone = next_interval(lr0, notdone, is_eqz(x), r);
            if( eve::any(notdone) )
            {
              auto testpos = is_nlez(a) && is_nlez(a + x);
              notdone      = next_interval(lrpos, notdone, testpos, r, a, x);
              if( eve::any(notdone) )
              {
                // from here a+x <= 0 ||  x <= 0
                auto aneg       = is_ltz(a);
                auto aflint     = is_flint(a);
                auto testnegint = aflint && is_flint(a + x) && aneg && is_ltz(a + x);
                notdone         = next_interval(lrnegint, notdone, testnegint, r, a, x);
                if( eve::any(notdone) )
                {
                  notdone = next_interval(lraeqmx, notdone, is_eqz(a + x), r, a, x);
                  if( eve::any(notdone) )
                  {
                    notdone = next_interval(lraneqmx, notdone, aflint && !is_eqz(a + x), r, a, x);
                    if( eve::any(notdone) )
                    {
                      notdone = next_interval(lrneg, notdone, aneg && is_ltz(a + x), r, a, x);
                      if( eve::any(notdone) ) { notdone = last_interval(lrlast, notdone, r, a, x); }
                    }
                  }
                }
              }
            }
          }
          return r;
        }
        else
        {
          // regular  nan if a+x or x is negative,  better computation than raw
          auto lr0   = []() { return zero(as<T>{}); };
          auto lrpos = [](auto aa, auto xx) { return inner_lrising_factorial(aa, xx); };

          auto r       = nan(as{a});
          auto notdone = is_nltz(x) || is_nltz(a + x);
          if( eve::any(notdone) )
          {
            notdone = next_interval(lr0, notdone, is_eqz(x), r);
            if( eve::any(notdone) ) { notdone = last_interval(lrpos, notdone, r, a, x); }
          }
          return r;
        }
      }
    }
  }
}
