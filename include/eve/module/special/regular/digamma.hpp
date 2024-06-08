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
  template<eve::floating_ordered_value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(digamma_t, digamma_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var digamma
//!   @brief Computes the Digamma function i.e. the logarithmic derivative of the \f$\Gamma\f$
//!   function.
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
//!      template< eve::floating_ordered_value T >
//!      T digamma(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!
//!   **Return value**
//!
//!   The value of the Digamma function: \f$\frac{\Gamma'(x)}{\Gamma(x)}\f$ is returned.
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/regular/digamma.cpp}
//!
//!
//! @}
//================================================================================================
inline constexpr auto digamma = functor<digamma_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T  digamma_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
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
        result += rec[pedantic2](x + x);
        auto z = rec[pedantic2](sqr(x));
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
        auto result = zero(as(x));
        if( x == 0 ) return copysign(inf(as(x)), x);
        if( x < 0 )
        {
          if( 0 && (x > -1) ) result = -x;
          else
          {
            x      = oneminus(x);
            result = x - floor(x);
          }
          if( result > 0.5 ) result -= 1;
          if( result == 0.5 ) result = zero(as(x));
          else if( result ) result = pi(as(x)) * cotpi(result);
          else result = nan(as(x));
          // we are ready to increment result that was
          // Pi<A0>()/tanpi(remainder) if a0 < 0  and remainder != 0
          // Nan<A0>                   if a0 < 0  and remainder == 0
          // 0                         in any other cases
        }
        if( x >= dlarge )
        { // If we're above the lower-limit for the asymptotic expansion then use it:
          return br_large(x, result);
        }
        // If x > 2 reduce to the interval [1,2]:
        while( x > 2 )
        {
          x -= 1;
          result += 1 / x;
        }
        // If x < 1 use shift to > 1:
        if( x < 1 )
        {
          result = -1 / x;
          x += 1;
        }
        return br_1_2(x, result);
      }
      else // simd
      {
        x            = if_else(is_ltz(x) && is_flint(x), allbits, x);
        auto notdone = is_not_nan(x);
        auto result  = zero(as(x));
        auto test    = is_lez(x);
        if( eve::any(test) )
        {
          auto a         = x;
          x              = oneminus[test](x);
          auto remainder = frac[raw](x);
          remainder      = dec[remainder > 0.5](remainder);
          remainder      = if_else(is_eqz(remainder), nan(as(x)), remainder);
          remainder      = if_else(remainder == T(0.5), zero, pi(as(x)) * cotpi(remainder));
          result         = if_else(is_eqz(a), copysign(inf(as(x)), a), remainder);
          result         = if_else(test, result, zero);
        }
        auto r = nan(as<T>());
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_large, notdone, x >= dlarge, r, x, result);
          if( eve::any(notdone) )
          {
            // If x > 2 reduce to the interval [1,2]:
            x         = if_else(x > dlarge, one, x);
            auto cond = x > T(2);
            while( eve::any(cond) )
            {
              x      = dec[cond](x);
              result = add[cond](result, rec[pedantic2](x));
              cond   = x > T(2);
            }
            cond = x < T(1);
            while( eve::any(cond) )
            {
              result = add[cond](result, -rec[pedantic2](x));
              x      = inc[cond](x);
              cond   = x < T(1);
            }
            notdone = last_interval(br_1_2, notdone, r, x, result);
          }
        }
        return r;
      }
    }
  }
}
