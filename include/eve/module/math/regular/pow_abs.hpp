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
#include <eve/module/core.hpp>

namespace eve
{
  template<typename Options>
  struct pow_abs_t : elementwise_callable<pow_abs_t, Options, raw_option>
  {
    template<eve::floating_scalar_value T, eve::integral_scalar_value U>
    EVE_FORCEINLINE constexpr T operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    template<eve::floating_value T, eve::floating_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    EVE_CALLABLE_OBJECT(pow_abs_t, pow_abs_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var pow_abs
//!
//! @brief Callable object computing the pow_abs function \f$|x|^y\f$.
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
//!      constexpr auto pow_abs(floating_value auto x, floating_value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto pow_abs[conditional_expr auto c](floating_value auto x, floating_value auto y) noexcept; // 2
//!      constexpr auto pow_abs[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto pow_abs[raw](floating_value auto x, floating_value auto y)                     noexcept; // 3
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!    * `x`, `y`: [floating_value](@ref eve::floating_value) arguments.
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//! Returns [elementwise](@ref glossary_elementwise) \f$|x|^y\f$.
//!
//!   1. The result type is the [common type](@ref common_value_t) of the two parameters.
//!      In particular we have (IEC 60559) for floating entries:
//!
//!      *  pow_abs(\f$\pm0\f$, y), where y is a negative odd integer, returns \f$+\infty\f$.
//!      *  pow_abs(\f$\pm0\f$, y), where y is negative, finite, and is an even integer or a
//!      non-integer, returns \f$+\infty\f$.
//!      *  pow_abs(\f$\pm0\f$, \f$-\infty\f$) returns \f$+\infty\f$.
//!      *  pow_abs(\f$\pm0\f$, y), where y is a positive odd integer, returns \f$+0\f$.
//!      *  pow_abs(\f$\pm0\f$, y), where y is positive non-integer or a positive even integer, returns
//!      \f$+0\f$.
//!      *  pow_abs(-1, \f$\pm\infty\f$) returns 1.
//!      *  pow_abs(\f$\pm1\f$, y) returns 1 for any y, even when y is NaN.
//!      *  pow_abs(x, \f$\pm0\f$) returns 1 for any x, even when x is NaN.
//!      *  pow_abs(x, \f$-\infty\f$) returns \f$+\infty\f$ for any |x| `<` 1.
//!      *  pow_abs(x, \f$-\infty\f$) returns \f$+0\f$ for any |x| `>` 1.
//!      *  pow_abs(x, \f$+\infty\f$) returns \f$+0\f$ for any |x| `<` 1.
//!      *  pow_abs(x, \f$+\infty\f$) returns \f$+\infty\f$ for any |x| `>` 1.
//!      *  pow_abs(\f$+\infty\f$, y) returns \f$+0\f$ for any negative y.
//!      *  pow_abs(\f$+\infty\f$, y) returns \f$+\infty\f$ for any positive y.
//!      *  except where specified above, if any argument is NaN, NaN is returned.
//!   2. [The operation is performed conditionnaly](@ref conditional)
//!   3. faster but less accurate call.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/pow_abs.cpp}
//================================================================================================
  inline constexpr auto pow_abs = functor<pow_abs_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {

    template<floating_scalar_value T,  integral_scalar_value U, callable_options O>
    EVE_FORCEINLINE constexpr T
    pow_abs_(EVE_REQUIRES(cpu_), O const & o, T a0, U a1) noexcept
    {
      return pow_abs[o](a0, T(a1));
    }

    template<typename T,  typename U, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T, U>
    pow_abs_(EVE_REQUIRES(cpu_), O const &, T a, U b) noexcept
    {
      using r_t = common_value_t<T, U>;
      auto x =  r_t(a);
      auto y =  r_t(b);
      if constexpr( scalar_value<r_t> )
        return std::pow(eve::abs(x), y);
      else
      {
        using i_t              = as_integer_t<r_t, unsigned>;
        using eli_t            = element_type_t<i_t>;
        auto        iseqzx     = is_eqz(x);
        auto        ylt0       = y < zero(as(y));
        auto        ax         = eve::abs(x);
        auto        ax_is1     = ax == eve::one(as(x));
        eli_t const largelimit = (sizeof(eli_t) == 4 ? 31 : 63);
        auto [yf, yi]          = eve::modf(eve::abs(y));
        auto test              = yf > r_t(0.5);
        yf                     = dec[test](yf);
        auto z                 = eve::exp(yf*eve::log(ax));
        yi                     = inc[test](yi);
        yi                     = if_else(ax_is1, eve::one, yi);
        auto large             = (yi > r_t(largelimit));
        yi                     = if_else(large, eve::one, yi);

        auto russian = [](auto base, auto expo){
          r_t result(1);
          while( eve::any(is_nez(expo)) )
          {
            result *= if_else(is_odd(expo), base, T(1));
            expo = (expo >> 1);
            base = sqr(base);
          }
          return result;
        };
        z *= russian(ax, convert(yi, uint_from<T>()));
        z = if_else(large, if_else(ax < one(as(x)), zero, inf(as(x))), z);
        z = if_else(iseqzx && ylt0, zero, z);
        z = if_else(is_infinite(ax), inf(as(x)), z);
        z = if_else(ylt0, rec[pedantic](z), z);
        z = if_else(ax_is1 || is_eqz(y), one, z);
        z = if_else(iseqzx && is_gtz(y), zero, z);
        z = if_else(is_nan(x) && is_nan(y), allbits, z);
        return z;
      }
    }
  }
}
