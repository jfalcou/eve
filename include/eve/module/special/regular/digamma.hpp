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
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/log_abs_gamma.hpp>

namespace eve
{
  template<typename Options>
  struct digamma_t : elementwise_callable<digamma_t, Options>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(digamma_t, digamma_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var digamma
//!   @brief `elementwise_callable` object computing the Digamma function i.e.
//!   the logarithmic derivative of the \f$\Gamma\f$  function.
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
//!      constexpr auto digamma(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto digamma[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto digamma[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating_value](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of the Digamma function: \f$\psi(x) = \frac{\Gamma'(x)}{\Gamma(x)}\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [DLMF: Gamma and Psi Functions](https://dlmf.nist.gov/5.2#i)
//!   *  [Wolfram MathWorld: Digamma Function](https://mathworld.wolfram.com/DigammaFunction.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/digamma.cpp}
//================================================================================================
  inline constexpr auto digamma = functor<digamma_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T  digamma_(EVE_REQUIRES(cpu_), O const&, T a) noexcept
    {
      using elt_t  = element_type_t<T>;
      auto dlarge = (std::is_same_v<elt_t, double>) ? 20 : 10;
      auto br_1_2 = [](auto x, auto result){
        // computes digamma(a0)/a0 for double or double vectors
        // xx is sqr(a0) and 0 <= abs(a0) <= 3.25
        T y(0.99558162689208984);
        T root1(1569415565.0 / 1073741824uL);
        T root2((381566830.0 / 1073741824uL) / 1073741824uL);
        T root3(0.9016312093258695918615325266959189453125e-19);

        auto g = x - root1;
        g -= root2;
        g -= root3;
        x = dec(x);
        if constexpr( std::is_same_v<elt_t, double> )
        {
          auto r = eve::reverse_horner(x, T(0x1.04e9e69894978p-2), T(-0x1.4d5d0f9ab412fp-2), T(-0x1.4cf68d26e295ap-1)
                                      , T(-0x1.2821c13c5e2bfp-2), T(-0x1.72b2e63723c78p-5), T(-0x1.0f7e5f66c2537p-9))/
            eve::reverse_horner(x, T(0x1.0000000000000p+0), T(0x1.09d1b06674d41p+1), T(0x1.75eb79397c930p+0)
                               , T(0x1.be65d28de361cp-2), T(0x1.bb9c8cc612ca3p-5), T(0x1.16fc90a0a1908p-9)
                               , T(-0x1.2b84f95bbf448p-21));
          return fma(g, y, g * r) + result;
        }
        else
        {
          auto r =
          eve::reverse_horner(x, T(0x1.04e9e6p-2f), T(-0x1.4d5d10p-2f), T(-0x1.4cf68ep-1f), T(-0x1.2821c2p-2f)
                             , T(-0x1.72b2e6p-5f), T(-0x1.0f7e60p-9f))/
          eve::reverse_horner(x, T(0x1.000000p+0f), T(0x1.09d1b0p+1f), T(0x1.75eb7ap+0f), T(0x1.be65d2p-2f)
                             , T(0x1.bb9c8cp-5f), T(0x1.16fc90p-9f), T(-0x1.2b84fap-21f));
          return fma(g, y, g * r) + result;
        }
      };

      auto br_large = [](auto x, auto result){
        // if we're above the lower-limit for the asymptotic expansion then use it:
        x = dec(x);
        result += log(x);
        result += rec[pedantic](x + x);
        auto z = rec[pedantic](sqr(x));
        T    y(0);
        if constexpr( std::is_same_v<elt_t, double> )
        {
          y =
            eve::reverse_horner(z, T(0x1.5555555555555p-4), T(-0x1.1111111111111p-7), T(0x1.0410410410410p-8)
                               , T(-0x1.1111111111111p-8), T(0x1.f07c1f07c1f08p-8), T(-0x1.5995995995996p-6)
                               , T(0x1.5555555555555p-4), T(-0x1.c5e5e5e5e5e5ep-2));
        }
        else
        {
          y =
          eve::reverse_horner(z, T(0x1.555556p-4f), T(-0x1.111112p-7f), T(0x1.041042p-8f), T(-0x1.111112p-8f)
                             , T(0x1.f07c20p-8f), T(-0x1.59959ap-6f), T(0x1.555556p-4f), T(-0x1.c5e5e6p-2f));
        }
        result -= z * y;
        return result;
      };

      if constexpr( scalar_value<T> )
      {
        auto result = zero(as(a));
        if( a == 0 ) return copysign(inf(as(a)), a);
        if( a < 0 )
        {
          if( 0 && (a > -1) ) result = -a;
          else
          {
            a      = oneminus(a);
            result = a - floor(a);
          }
          if( result > 0.5 ) result -= 1;
          if( result == 0.5 ) result = zero(as(a));
          else if( result ) result = pi(as(a)) * cotpi(result);
          else result = nan(as(a));
          // we are ready to increment result that was
          // Pi<A0>()/tanpi(remainder) if a0 < 0  and remainder != 0
          // Nan<A0>                   if a0 < 0  and remainder == 0
          // 0                         in any other cases
        }
        if( a >= dlarge )
        { // If we're above the lower-limit for the asymptotic eapansion then use it:
          return br_large(a, result);
        }
        // If a > 2 reduce to the interval [1,2]:
        while( a > 2 )
        {
          a -= 1;
          result += 1 / a;
        }
        // If a < 1 use shift to > 1:
        if( a < 1 )
        {
          result = -1 / a;
          a += 1;
        }
        return br_1_2(a, result);
      }
      else // simd
      {
        a            = if_else(is_ltz(a) && is_flint(a), allbits, a);
        auto notdone = is_not_nan(a);
        auto result  = zero(as(a));
        auto test    = is_lez(a);
        if( eve::any(test) )
        {
          auto va        = a;
          a              = oneminus[test](a);
          auto remainder = frac[raw](a);
          remainder      = dec[remainder > 0.5](remainder);
          remainder      = if_else(is_eqz(remainder), nan(as(a)), remainder);
          remainder      = if_else(remainder == T(0.5), zero, pi(as(a)) * cotpi(remainder));
          result         = if_else(is_eqz(va), copysign(inf(as(a)), va), remainder);
          result         = if_else(test, result, zero);
        }
        auto r = nan(as<T>());
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_large, notdone, a >= dlarge, r, a, result);
          if( eve::any(notdone) )
          {
            // If a > 2 reduce to the interval [1,2]:
            a         = if_else(a > dlarge, one, a);
            auto cond = a > T(2);
            while( eve::any(cond) )
            {
              a      = dec[cond](a);
              result = add[cond](result, rec[pedantic](a));
              cond   = a > T(2);
            }
            cond = a < T(1);
            while( eve::any(cond) )
            {
              result = add[cond](result, -rec[pedantic](a));
              a      = inc[cond](a);
              cond   = a < T(1);
            }
            notdone = last_interval(br_1_2, notdone, r, a, result);
          }
        }
        return r;
      }
    }
  }
}
