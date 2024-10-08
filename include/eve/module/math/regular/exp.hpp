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
  struct exp_t : elementwise_callable<exp_t, Options, pedantic_option>
  {
    template<value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(exp_t, exp_);
  };

  //================================================================================================
  //! @addtogroup math_exp
  //! @{
  //! @var exp
  //! @brief `elementwise_callable` object computing \f$e^x\f$.
  //!
  //!   @groupheader{Header file}
  //!
  //!   @code
  //!   #include <eve/module/math.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      // Regular overload
  //!      constexpr auto exp(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto exp[conditional_expr auto c](floating_value auto x) noexcept; // 2
  //!      constexpr auto exp[logical_value auto m](floating_value auto x)    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!     * `x`: [floating value](@ref floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //! **Return value**
  //!
  //!   1.  Returns the [elementwise](@ref glossary_elementwise) natural exponential
  //!       of the input. In particular:
  //!       * If the element is \f$\pm0\f$, \f$1\f$ is returned
  //!       * If the element is \f$-\infty\f$, \f$+0\f$ is returned
  //!       * If the element is \f$\infty\f$, \f$\infty\f$ is returned
  //!       * If the element is a `NaN`, `NaN` is returned
  //!   2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{External references}
  //!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/exp)
  //!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/ExponentialFunction.html)
  //!   *  [DLMF](https://dlmf.nist.gov/4.2)
  //!   *  [Wikipedia](https://en.wikipedia.org/wiki/Exponential_function)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/math/exp.cpp}
  //================================================================================================
  inline constexpr auto exp = functor<exp_t>;
  //================================================================================================
  //!  @}
  //================================================================================================

  namespace detail
  {
    template<floating_value T, callable_options O>
    EVE_FORCEINLINE constexpr T
    exp_(EVE_REQUIRES(cpu_), O const &, T x) noexcept
    {
      auto isnan = is_nan(x);
      auto    minlogval = []() {
        if constexpr(O::contains(pedantic) && eve::platform::supports_denormals)
        return minlogdenormal(eve::as<T>());
        else
          return minlog(eve::as<T>());
      };
      if constexpr( scalar_value<T> )
      {
        if constexpr( has_emulated_abi_v<wide<T>> )
        {
          return (x <= minlogval()) ? T(0) : (x >= eve::maxlog(as(x))) ? inf(as(x)) : std::exp(x);
        }
        else
        {
          wide<T> xx(x);
          return exp(xx).get(0);
        }
      }
      else
      {
        using elt_t       = element_type_t<T>;
        const T Log_2hi   = ieee_constant<0x1.6300000p-1f, 0x1.62e42fee00000p-1>(eve::as<T>{});
        const T Log_2lo   = ieee_constant<-0x1.bd01060p-13f, 0x1.a39ef35793c76p-33>(eve::as<T>{});
        const T Invlog_2  = ieee_constant<0x1.7154760p+0f, 0x1.71547652b82fep+0>(eve::as<T>{});
        auto    xltminlog = x <= minlogval();
        auto    xgemaxlog = x >= maxlog(eve::as(x));
        if constexpr( scalar_value<T> )
        {
          if( isnan ) return x;
          if( xgemaxlog ) return inf(eve::as(x));
          if( xltminlog ) return zero(eve::as(x));
        }
        auto c = nearest(Invlog_2 * x);
        auto k = c;
        x      = fnma(c, Log_2hi, x); // x-c*L
        if constexpr( std::is_same_v<elt_t, float> )
        {
          x      = fnma(c, Log_2lo, x);
          auto y = eve::reverse_horner(x, T(0x1.000000p-1f), T(0x1.55534ap-3f), T(0x1.5552aep-5f)
                                      , T(0x1.131b16p-7f), T(0x1.6ef19ep-10f));;
          c      = inc(fma(y, sqr(x), x));
        }
        else if constexpr( std::is_same_v<elt_t, double> )
        {
          auto hi = x;
          auto lo = c * Log_2lo;
          x       = hi - lo;
          auto t  = sqr(x);
          c       = fnma(t, eve::reverse_horner(t, T(0x1.555555555553ep-3), T(-0x1.6c16c16bebd93p-9), T(0x1.1566aaf25de2cp-14)
                                               , T(-0x1.bbd41c5d26bf1p-20), T(0x1.6376972bea4d0p-25)), x); // x-h*t
          c       = oneminus((((lo - (x * c) / (T(2) - c)) - hi)));
        }
        auto z = ldexp[pedantic](c, k);
        if constexpr( simd_value<T> )
        {
          z = if_else(xltminlog, eve::zero, z);
          z = if_else(xgemaxlog, inf(eve::as(x)), z);
          z = if_else(isnan, allbits, z);
        }
        return z;
      }
    }
  }
}
