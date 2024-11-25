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
#include <eve/module/special/regular/stirling.hpp>

namespace eve
{
  template<typename Options>
  struct tgamma_t : elementwise_callable<tgamma_t, Options>
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(tgamma_t, tgamma_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var tgamma
//!   @brief `elementwise_callable` object computing \f$\displaystyle \Gamma(x)=\int_0^\infty t^{x-1}e^{-t}\mbox{d}t\f$.
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
//!      constexpr auto tgamma(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto tgamma[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto tgamma[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`: [floating real value](@ref eve::floating_value).
//!      * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!      * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!      1. The value of \f$\Gamma\f$ is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: tgamma](https://en.cppreference.com/w/cpp/numeric/math/tgamma)
//!   *  [Wikipedia: Gamma function](https://en.wikipedia.org/wiki/Gamma_function)
//!   *  [Wolfram MathWorld: Gamma Function](https://mathworld.wolfram.com/GammaFunction.html)
//!   *  [DLMF: gamma function](https://dlmf.nist.gov/5.2)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/tgamma.cpp}
//================================================================================================
  inline constexpr auto tgamma = functor<tgamma_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    T tgamma_(EVE_REQUIRES(cpu_), O const&, T a0) noexcept
    {
      using elt_t  = element_type_t<T>;
      auto tgamma1 = [](T xx){
        if constexpr( std::is_same_v<elt_t, float> )
        {
          return  eve::reverse_horner(xx, T(0x1.000000p+0f), T(0x1.b0ef32p-2f), T(0x1.a5a822p-2f), T(0x1.505468p-4f)
                                     , T(0x1.275cf8p-4f), T(0x1.23b628p-8f),  T(0x1.521932p-8f), T(0x1.a51644p-10f));
        }
        else if constexpr( std::is_same_v<elt_t, double> )
        {
          return eve::reverse_horner(xx, T(0x1.0000000000000p+0), T(0x1.fa1373993e312p-2), T(0x1.a8da9dcae7d31p-3)
                                    , T(0x1.863d918c423d3p-5), T(0x1.557cde9db14b0p-7), T(0x1.384e3e686bfabp-10)
                                    , T(0x1.4fcb839982153p-13)) /
          eve::reverse_horner(xx, T(0x1.0000000000000p+0), T(0x1.24944c9cd3c51p-4), T(-0x1.e071a9d4287c2p-3)
                             , T(0x1.25779e33fde67p-5), T(0x1.831ed5b1bb117p-7), T(-0x1.240e4e750b44ap-8)
                             , T(0x1.1ae8a29152573p-11), T(-0x1.8487a8400d3afp-16));
        }
      };

      if constexpr( scalar_value<T> )
      {
        auto inftest = [](T a)
          {
            if constexpr( std::is_same_v<elt_t, float> ) { return a > 35.4f; }
            else if constexpr( std::is_same_v<elt_t, double> ) { return a > 171.624; };
          };
        if( is_eqz(a0) ) return copysign(inf(eve::as(a0)), a0);
        if constexpr( eve::platform::supports_nans )
        {
          if( is_nan(a0) || (a0 == minf(eve::as(a0))) ) return nan(eve::as(a0));
          if( a0 == inf(eve::as(a0)) ) return a0;
        }
        auto x = a0;
        if( inftest(a0) ) return inf(eve::as(a0));
        auto q = abs(x);
        if( x < T(-33) )
        {
          T    st     = stirling(q);
          T    p      = floor(q);
          auto iseven = is_even((int32_t)p);
          if( p == q ) return nan(eve::as(a0));
          T z = q - p;
          if( z > half(eve::as(a0)) )
          {
            p += one(eve::as(a0));
            z = q - p;
          }
          z = q * sinpi(z);
          if( is_eqz(z) ) return nan(eve::as(a0));
          st = pi(eve::as(a0)) / (abs(z) * st);
          return iseven ? -st : st;
        }
        T z = one(eve::as(a0));
        while( x >= T(3) )
        {
          x -= one(eve::as(a0));
          z *= x;
        }
        while( is_ltz(x) )
        {
          z /= x;
          x += one(eve::as(a0));
        }
        while( x < T(2) )
        {
          if( is_eqz(x) ) return nan(eve::as(a0));
          z /= x;
          x += one(eve::as(a0));
        }
        if( x == T(2) ) return (z);
        x -= T(2);
        return z * tgamma1(x);
      }
      else if constexpr( simd_value<T> )
      {
        auto large_negative = [](T q){
          auto st     = stirling(q);
          auto p      = floor(q);
          auto sgngam = if_else(is_even(p), one(eve::as(q)), eve::mone);
          auto z      = q - p;
          auto test2  = is_less(z, half(eve::as(q)));
          z           = dec[test2](z);
          z           = q * sinpi(z);
          z           = abs(z);
          return sgngam * pi(eve::as(q)) / (z * st);
        };

        auto other = [tgamma1](T q, const auto& test){
          auto xx = if_else(test, T(2), q);
          if constexpr( eve::platform::supports_nans )
          {
            auto inf_result = q == inf(eve::as<T>());
            xx               = if_else(inf_result, T(2), xx);
          }
          auto z     = one(eve::as<T>());
          auto test1 = (xx >= T(3));
          while( eve::any(test1) )
          {
            xx     = dec[test1](xx);
            z     = if_else(test1, z * xx, z);
            test1 = (xx >= T(3));
          }
          // all xx are less than 3
          test1 = is_ltz(xx);
          while( eve::any(test1) )
          {
            z     = if_else(test1, z / xx, z);
            xx     = inc[test1](xx);
            test1 = is_ltz(xx);
          }
          // all xx are greater than 0 and less than 3
          auto test2 = is_less(xx, T(2));
          while( eve::any(test2) )
          {
            z     = if_else(test2, z / xx, z);
            xx     = inc[test2](xx);
            test2 = is_less(xx, T(2));
          }
          // all xx are greater equal 2 and less than 3
          xx = z * tgamma1(xx - T(2));
          if constexpr( eve::platform::supports_infinites )
          {
            auto inf_result = (q == inf(eve::as<T>()));
            return if_else(inf_result, q, xx);
          }
          else return xx;
        };

        auto nan_result = is_ltz(a0) && is_flint(a0);
        //       if constexpr(eve::platform::supports_nans) nan_result = is_nan(a0) || nan_result;
        auto        q    = abs(a0);
        auto        test = is_less(a0, T(-33.0));
        std::size_t nb   = eve::count_true(test);
        auto        r    = nan(eve::as(a0));
        if( nb > 0 )
        {
          // treat negative large with reflection
          r = large_negative(q);
          if( nb >= cardinal_v<T> ) return if_else(nan_result, eve::allbits, r);
        }
        auto r1 = other(a0, test);
        auto r2 = if_else(test, r, r1);
        return if_else(
          is_eqz(a0), copysign(inf(eve::as(a0)), a0), if_else(nan_result, eve::allbits, r2));
      }
    }
  }
}
