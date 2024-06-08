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
#include <eve/module/math/regular/log.hpp>
#include <eve/module/math/regular/exp.hpp>
#include <eve/module/math/regular/pow_abs.hpp>

namespace eve
{
  template<typename Options>
  struct pow_t : strict_elementwise_callable<pow_t, Options, raw_option>
  {
    template<eve::floating_scalar_value T, eve::integral_scalar_value U>
    EVE_FORCEINLINE constexpr T operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    template<eve::floating_value T, eve::floating_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    template<integral_value T,  integral_scalar_value U>
    EVE_FORCEINLINE constexpr common_value_t<T, U> operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    template<floating_simd_value T,  integral_scalar_value U>
    EVE_FORCEINLINE constexpr T operator()(T v, U w) const noexcept
    {  return EVE_DISPATCH_CALL(v, w); }

    template<floating_value T,  integral_simd_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    EVE_FORCEINLINE constexpr  as_wide_as_t<T, U > operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    template<integral_simd_value T,  integral_simd_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    EVE_FORCEINLINE constexpr common_value_t<T, U > operator()(T v, U w) const noexcept
    { return EVE_DISPATCH_CALL(v, w); }

    EVE_CALLABLE_OBJECT(pow_t, pow_);
  };

//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var pow
//!
//! @brief Callable object computing the pow operation \f$x^y\f$.
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
//!      template< eve::floating_value T, eve::floating_value U >
//!      auto pow(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!
//! **Return value**
//!
//!   Returns [elementwise](@ref glossary_elementwise) \f$x^y\f$.
//!
//!   *  The result type is the [common value type](@ref common_value_t) of the two parameters.
//!      In particular we have (IEC 60559):
//!
//!       * pow(+0, y), where y is a negative odd integer, returns \f$+\infty\f$
//!       * pow(-0, y), where y is a negative odd integer, returns \f$-\infty\f$
//!       * pow(\f$\pm0\f$, y), where y is negative, finite, and is an even integer or a non-integer,
//!         returns \f$+\infty\f$
//!       * pow(\f$\pm0\f$, \f$-\infty\f$) returns \f$+\infty\f$
//!       * pow(+0, y), where y is a positive odd integer, returns +0
//!       * pow(-0, y), where y is a positive odd integer, returns -0
//!       * pow(\f$\pm0\f$, y), where y is positive non-integer or a positive even integer, returns +0
//!       * pow(-1,\f$\pm\infty\f$) returns 1
//!       * pow(+1, y) returns 1 for any y, even when y is NaN
//!       * pow(x, \f$\pm0\f$) returns 1 for any x, even when x is NaN
//!       * pow(x, y) returns NaN if x is finite and less than 0 and y is finite and non-integer.
//!       * pow(x, \f$-\infty\f$) returns \f$+\infty\f$ for any |x|<1
//!       * pow(x, \f$-\infty\f$) returns +0 for any |x|>1
//!       * pow(x, \f$+\infty\f$) returns +0 for any |x|<1
//!       * pow(x, \f$+\infty\f$) returns \f$+\infty\f$ for any |x|>1
//!       * pow(\f$-\infty\f$, y) returns -0 if y is a negative odd integer
//!       * pow(\f$-\infty\f$, y) returns +0 if y is a negative non-integer or even integer
//!       * pow(\f$-\infty\f$, y) returns \f$-\infty\f$ if y is a positive odd integer
//!       * pow(\f$-\infty\f$, y) returns \f$+\infty\f$ if y is a positive non-integer or even integer
//!       * pow(\f$+\infty\f$, y) returns +0 for any y less than 0
//!       * pow(\f$+\infty\f$, y) returns \f$+\infty\f$ for any y greater than 0
//!       * except where specified above, if any argument is NaN, NaN is returned
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/pow.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::pow[mask](x, y)` provides a masked version of `eve::pow` which is
//!     equivalent to `if_else (mask, pow(x, y), x)`.
//!
//!     **Example**
//!
//!     @godbolt{doc/math/masked/pow.cpp}
//!  @}
//================================================================================================
  inline constexpr auto pow = functor<pow_t>;

  namespace detail
  {
    template<floating_scalar_value T,  integral_scalar_value U, callable_options O>
    EVE_FORCEINLINE constexpr T
    pow_(EVE_REQUIRES(cpu_), O const&, T a0, U a1) noexcept
    {
      if constexpr( std::is_unsigned_v<U> ) // U unsigned
      {
        T base = a0;
        U expo = a1;

        auto result = one(as(a0));
        while( expo )
        {
          if( is_odd(expo) ) result *= base;
          expo >>= 1;
          base = sqr(base);
        }
        return result;
      }
      else //U integral signed scalar
      {
        using u_t = as_integer_t<U, unsigned>;
        T tmp   = pow(a0, u_t(eve::abs(a1)));
        return a1<0 ? rec[pedantic2](tmp) : tmp;
      }
    }

    template<floating_value T,  floating_value U, callable_options O> //3
    EVE_FORCEINLINE constexpr common_value_t<T, U>
    pow_(EVE_REQUIRES(cpu_), O const &, T a0, U a1) noexcept
    {
      using r_t =  common_value_t<T, U>;
      if constexpr(O::contains(raw2))
      {
        return exp(a1*log(a0));
      }
      else
      {
        if constexpr( scalar_value<T> )
        {
          if( a0 == mone(as(a0)) && is_infinite(a1) ) return one(as<r_t>());
        }
        auto nega = is_negative(r_t(a0));
        r_t  z  = eve::pow_abs(a0, a1);
        return minus[is_odd(a1) && nega](z);
      }
    }

    template<integral_scalar_value T,  integral_scalar_value U, callable_options O> //4
    EVE_FORCEINLINE constexpr common_value_t<T, U>
    pow_(EVE_REQUIRES(cpu_), O const &, T a0, U a1) noexcept
    {
      using r_t = common_value_t<T, U>;
      if( a0 == r_t(1)) return r_t(a0);
      if( a1 >= U(sizeof(r_t) * 8 - 1 - (std::is_signed_v<r_t>)) || a1 < 0 ) return r_t(0);
      constexpr uint8_t highest_bit_set[] = {
        0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
        6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}; // anything past 63 is a guaranteed overflow with  a0 > 1
      r_t result(1);
      auto step =  [&](){if ( a1 & 1 ) result *= a0; a1 >>= 1; a0 *= a0; };
      switch( highest_bit_set[a1] ) {
      case 6: step(); [[fallthrough]];
      case 5: step(); [[fallthrough]];
      case 4: step(); [[fallthrough]];
      case 3: step(); [[fallthrough]];
      case 2: step(); [[fallthrough]];
      case 1: step(); [[fallthrough]];
      default: return result;
      }
    }

    template<floating_simd_value T, integral_scalar_value U, callable_options O>  //5
    EVE_FORCEINLINE constexpr T
    pow_(EVE_REQUIRES(cpu_), O const&, T a0, U a1) noexcept
    {
      using r_t =  common_value_t<T, U>;
      if constexpr( std::is_unsigned_v<U> ) // U unsigned
      {
        r_t base = a0;
        U expo = a1;

        auto result = one(as(a0));
        while( expo )
        {
          if( is_odd(expo) ) result *= base;
          expo >>= 1;
          base = sqr(base);
        }
        return result;
      }
      else //U integral signed scalar
      {
        using u_t = as_integer_t<U, unsigned>;
        r_t tmp   = pow(r_t(a0), u_t(eve::abs(a1)));
        return rec[pedantic2][is_ltz(a1)](tmp);
      }
    }

    template<floating_value T,  integral_simd_value U, callable_options O>  //6
    EVE_FORCEINLINE constexpr as_wide_as_t<T, U >
    pow_(EVE_REQUIRES(cpu_), O const &, T a0, U a1) noexcept
    {
      using r_t =   as_wide_as_t<T, U >;
      if constexpr( unsigned_value<U> )
      {
        r_t base = a0;
        U expo = a1;

        r_t result = one(as<r_t>());
        while( eve::any(to_logical(expo)) )
        {
          result *= if_else(is_odd(expo), base, one);
          expo = (expo >> 1);
          base = sqr(base);
        }
        return result;
      }
      else
      {
        using u_t = as_integer_t<U, unsigned>;
        r_t tmp     = pow(a0, bit_cast(eve::abs(a1), as<u_t>()));
        return if_else(is_ltz(a1), rec[pedantic2](tmp), tmp);
      }
    }

    template<integral_simd_value T,  integral_value U, callable_options O>  //7
    EVE_FORCEINLINE constexpr common_value_t<T, U >
    pow_(EVE_REQUIRES(cpu_), O const &, T a0, U a1) noexcept
    {
      using r_t =  common_value_t<T, U>;
      if constexpr( unsigned_value<U> )
      {
        r_t base = a0;
        U expo = a1;

        r_t result = one(as<r_t>());
        while( eve::any(to_logical(expo)) )
        {
          result *= if_else(is_odd(expo), base, one);
          expo = (expo >> 1);
          base = sqr(base);
        }
        return result;
      }
      else
      {
        using u_t = as_integer_t<U, unsigned>;
        r_t tmp     = pow(a0, bit_cast(eve::abs(a1), as<u_t>()));
        return if_else(is_ltz(a1), rec[pedantic2](tmp), tmp);
      }
    }
  }
}
