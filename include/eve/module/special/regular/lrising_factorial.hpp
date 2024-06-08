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
    template<ordered_value I, floating_ordered_value T>
    requires (same_lanes_or_scalar<I, T>)
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

  namespace detail
  {

    /////////////////////////////////////////////////////////////////////////////////////////
    //utilities

    template<typename T> constexpr EVE_FORCEINLINE auto inner_lrising_factorial(T a, T x) noexcept
    {
      // Assumes a>0 and a+x>0.
      auto ax      = eve::abs(x);
      auto notdone = is_nlez(a) && is_nlez(a + x);
      auto r       = nan(as(x));
      auto lr0     = [](auto a, auto x) { return log_abs_gamma(x + a) - log_abs_gamma(a); };

      auto lr1 = [](auto a, auto x){
        const auto xoa = x / a;
        const auto den = inc(xoa);
        const auto d2  = sqr(den);
        const auto d3  = den * d2;
        const auto d5  = d3 * d2;
        const auto d7  = d5 * d2;
        const auto c1  = -xoa / den;
        const auto c3  = -xoa * (3 + xoa * (3 + xoa)) / d3;
        const auto c5  = -xoa * (5 + xoa * (10 + xoa * (10 + xoa * (5 + xoa)))) / d5;
        const auto c7 =
        -xoa * (7 + xoa * (21 + xoa * (35 + xoa * (35 + xoa * (21 + xoa * (7 + xoa)))))) / d7;
        const auto p8    = eve::pow(inc(xoa), 8);
        const auto c8    = dec(rec[pedantic2](p8));            /* these need not   */
        const auto c9    = dec(rec[pedantic2](p8 * inc(xoa))); /* be very accurate */
        const auto a2    = sqr(a);
        const auto a4    = sqr(a2);
        const auto a6    = a4 * a2;
        const auto ser_1 = c1 + c3 / (30 * a2) + c5 / (105 * a4) + c7 / (140 * a6);
        const auto ser_2 = c8 / (99 * a6 * a2) - 691 * c9 / (a6 * a4) / 360360;
        const auto ser   = (ser_1 + ser_2) / (12 * a);
        auto       term1 = x * dec(eve::log(a)); // eve::log(a/M_E);
        auto       lg    = eve::log1p(xoa);
        auto       term2 = (x + a - half(as(x))) * lg;
        return term1 + term2 + ser;
      };

      auto lr2 = [](auto a, auto x){
        return if_else(dist(x + a, a) < 10 * a * eps(as(a)),
                       eve::log1p(x * digamma(a)),
                       log_abs_gamma(a + x) - log_abs_gamma(a));
      };

      if( eve::any(notdone) )
      {
        auto test0 = (10 * ax > a) || (10 * ax * log(eve::max(a, T(2))) > one(as(x)));
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

    template<typename I, typename T, callable_options O>
    constexpr as_wide_as_t<T, I> lrising_factorial_(EVE_REQUIRES(cpu_), O const& d, I a, T x) noexcept
    {
      // Integral first parameter
      if constexpr(integral_value<I> )
      {
        if constexpr( integral_simd_value<I> )
        {
          using elt_t = element_type_t<T>;
          using r_t   = as_wide_t<elt_t, cardinal_t<I>>;
          auto aa     = convert(a, as(elt_t()));
          return lrising_factorial[d](aa, r_t(x));
        }
        else if constexpr( integral_scalar_value<I> )
        {
          return lrising_factorial[d](T(a), x);
        }
      }
      else
      {
        if constexpr(O::contains(raw2))
        {
          // raw direct computation not matter why. nan if a+x or x is non positive
          auto notdone = is_nlez(x) && is_nlez(a + x);
          return if_else(notdone, log_abs_gamma(x + a) - log_abs_gamma(a), allbits);
        }
        else if constexpr(O::contains(pedantic2))
        {
          // pedantic computes also for negative values and even negative integer values
          auto r       = nan(as(a));
          auto notdone = is_not_nan(a) && is_not_nan(x);

          auto lr0 = []() { return zero(as(T())); };

          auto lrpos = [](auto a, auto x) { return inner_lrising_factorial(a, x); };

          auto lrnegint = [](auto a, auto x){ // a and a+x are negative integers uses reflection.
            auto r = inner_lrising_factorial(-a, -x);
            return -eve::log1p(x / a) - r;
          };

          auto lraeqmx = [](auto a, auto){  // a+x = 0
            return log_abs_gamma(inc(a));
          };

          auto lraneqmx = [](auto a, auto){ // a < 0.0 && a+x < 0.0
            return minf(as(a));
          };

          auto lrneg = [](auto a, auto x){
            // Reduce to positive case using reflection.
            auto oma      = oneminus(a);
            auto spioma   = sinpi(oma);
            auto spiomamx = sinpi(oma - x);
            auto r        = inner_lrising_factorial(oma, -x);
            auto lnterm   = eve::log(eve::abs(spioma / spiomamx));
            return if_else(is_nez(spiomamx * spioma), lnterm - r, allbits);
          };

          auto lrlast = [](auto a, auto x) { return eve::log_abs_gamma(a + x) - eve::log_abs_gamma(a); };

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
          auto lr0   = []() { return zero(as(T())); };
          auto lrpos = [](auto a, auto x) { return inner_lrising_factorial(a, x); };

          auto r       = nan(as(a));
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
