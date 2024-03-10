//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{

  template<typename Options>
  struct exp_t : elementwise_callable<exp_t, Options, pedantic_option>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(exp_t, exp_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var exp
//!
//! @brief Callable object computing \f$e^x\f$.
//!
//!   **Defined in Header**
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
//!      template< eve::floating_value T >
//!      T exp(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) exponential of the input.
//!
//!     In particular:
//!
//!     * If the element is \f$\pm0\f$, \f$1\f$ is returned
//!     * If the element is \f$-\infty\f$, \f$+0\f$ is returned
//!     * If the element is \f$\infty\f$, \f$\infty\f$ is returned
//!     * If the element is a `NaN`, `NaN` is returned
//!
//!      * for every z: eve::exp(eve::conj(z)) == eve::conj(std::exp(z))
//!      * If z is \f$\pm0\f$, the result is \f$1\f$
//!      * If z is \f$x+i \infty\f$ (for any finite x), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$x+i NaN\f$ (for any finite x), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$+\infty+i 0\f$, the result is \f$+\infty\f$
//!      * If z is \f$-\infty+i y\f$ (for any finite y), the result is \f$+0 \mathrm{cis}(y)\f$.
//!      * If z is \f$+\infty+i y\f$ (for any finite nonzero y), the result is \f$+\infty \mathrm{cis}(y)\f$.
//!      * If z is \f$-\infty+i \infty\f$, the result is \f$\pm 0+i \pm 0\f$ (signs are unspecified)
//!      * If z is \f$+\infty+i \pm\infty\f$, the result is \f$\pm \infty+i NaN\f$ (the sign of the real part is unspecified).
//!      * If z is \f$-\infty+i NaN\f$, the result is \f$\pm 0+i \pm 0\f$ (signs are unspecified).
//!      * If z is \f$\pm\infty+i NaN\f$, the result is \f$\pm \infty+i NaN\f$ (the sign of the real part is unspecified).
//!      * If z is \f$NaN\f$, the result is \f$NaN\f$.
//!      * If z is \f$NaN+i y\f$ (for any nonzero y), the result is \f$NaN+i NaN\f$.
//!      * If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$.
//!
//!      where \f$\mathrm{cis}(y) = \cos(y)+i \sin(y)\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/exp.cpp}
//!
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::exp[mask](x)` provides a masked version of `eve::exp` which is
//!     equivalent to `if_else (mask, exp(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/exp.cpp}
//!  @}
//================================================================================================
  inline constexpr auto exp = functor<exp_t>;

  namespace detail
  {
    template<floating_ordered_value T, callable_options O>
    EVE_FORCEINLINE constexpr T
    exp_(EVE_REQUIRES(cpu_), O const & o, T x) noexcept
    {
      auto isnan = is_nan(x);
      if constexpr( scalar_value<T> )
      {
        if constexpr( has_emulated_abi_v<wide<T>> )
        {
          return (x <= eve::minlog(as(x))) ? T(0)
            : ((x >= eve::maxlog(as(x))) ? inf(as(x)) : std::exp(x));
        }
        else
        {
          wide<T> xx(x);
          return exp(xx).get(0);
        }
      }
      else if constexpr( has_native_abi_v<T> )
      {
        using elt_t       = element_type_t<T>;
        auto    minlogval = []() {
          if constexpr(O::contains(pedantic2) && eve::platform::supports_denormals)
            return minlogdenormal(eve::as<T>());
          else
            return minlog(eve::as<T>());
        };
        const T Log_2hi   = ieee_constant<0x1.6300000p-1f, 0x1.62e42fee00000p-1>(eve::as<T>{});
        const T Log_2lo   = ieee_constant<-0x1.bd01060p-13f, 0x1.a39ef35793c76p-33>(eve::as<T>{});
        const T Invlog_2  = ieee_constant<0x1.7154760p+0f, 0x1.71547652b82fep+0>(eve::as<T>{});
        auto    xltminlog = x <= minlogval();
        auto    xgemaxlog = x >= maxlog(eve::as(x));
        if constexpr( scalar_value<T> )
        {
          if( isnan ) return nan(as(x));
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
      else return apply_over(exp[o], x);
    }
  }
}
