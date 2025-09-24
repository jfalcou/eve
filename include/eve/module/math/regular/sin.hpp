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
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/constant/pi2o_16.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/constant/pio_4.hpp>

#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/rempio2.hpp>

namespace eve
{
  template<typename Options>
  struct sin_t : elementwise_callable<sin_t, Options, quarter_circle_option, half_circle_option,
                                      full_circle_option, medium_option, big_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sin_t, sin_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var sin
//!
//! @brief `elementwise_callable` object computing the sine.
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
//!      constexpr auto sin(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sin[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto sin[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto sin[quarter_circle](floating_value auto x)          noexcept; // 3.a
//!      constexpr auto sin[half_circle](floating_value auto x)             noexcept; // 3.b
//!      constexpr auto sin[full_circle](floating_value auto x)             noexcept; // 3.c
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!      * `x`: [floating value](@ref eve::floating_value).
//!      * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!      * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) sine of the input. In particular:
//!       * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!       * If the element is \f$\pm\infty\f$, Nan is returned.
//!       * If the element is a `Nan`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!    3. These are optimized calls providing a balance between speed and range limitation.
//!        1. assumes that the inputs elements  belong to \f$[-\pi/4,\pi/4]\f$ and return NaN outside.
//!        2. assumes that the inputs elements  belong to \f$[-\pi/2,\pi/2]\f$ and return NaN outside.
//!        3. assumes that the inputs elements  belong to \f$[-\pi,\pi]\f$ and return NaN outside.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/sin)
//!   *  [Wikipedia](https://fr.wikipedia.org/wiki/Sinus)
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/Sine.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/sin.cpp}
//================================================================================================
  inline constexpr auto sin = functor<sin_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T sin_(EVE_REQUIRES(cpu_), O const& o , T const& a0)
    {
      if constexpr(O::contains(quarter_circle))
      {
        auto pi2_16 = pi2o_16[upper](as<T>());
        auto x2 = sqr(a0);
        if constexpr( scalar_value<T> )
          if( is_not_less_equal(x2, pi2_16) ) return nan(eve::as<T>());
        auto x = eve::abs(a0);
        auto r = bit_xor(sin_eval(x2, x), bitofsign(a0));
        if constexpr( scalar_value<T> ) return r;
        else return if_else(is_not_less_equal(x2, pi2_16), eve::allbits, r);
      }
      else if constexpr(O::contains(half_circle))
      {
        auto reduce = [](auto xx)
          {
            auto pio2_1 = ieee_constant<0x1.921fb54400000p+0 , 0x1.921f000p+0f >(eve::as<T>{});
            auto pio2_2 = ieee_constant<0x1.0b4611a600000p-34, 0x1.6a88000p-17f>(eve::as<T>{});
            auto pio2_3 = ieee_constant<0x1.3198a2e000000p-69, 0x1.0b46000p-34f>(eve::as<T>{});
            T    xr     = xx - pio2_1;
            xr -= pio2_2;
            xr -= pio2_3;
            return xr;
          };
        auto x = eve::abs(a0);
        if constexpr( scalar_value<T> )
        {
          using i_t = as_integer_t<T, signed>;
          if( is_less_equal(x, eps(as<T>())) ) return a0;
          if( is_not_less_equal(x, pio_2(eve::as<T>())) ) return nan(eve::as<T>());
          i_t n = x > pio_4(eve::as<T>());
          if( n )
          {
            auto xr = reduce(x);
            return bit_xor(bitofsign(a0), cos_eval(sqr(xr)));
          }
          else return sin_eval(sqr(x), a0);
        }
        else
        {
          auto n     = is_not_less_equal(x, pio_4(eve::as<T>()));
          auto xr    = reduce(x);
          xr         = if_else(n, xr, x);
          const T z  = sqr(xr);
          const T se = sin_eval(z, xr);
          const T ce = cos_eval(z);
          const T z1 = bit_xor(bitofsign(a0), if_else(n, ce, se));
          return if_else(is_not_less_equal(x, pio_2(eve::as<T>())), nan(eve::as<T>()), z1);
        }
      }
      else if constexpr(O::contains(full_circle) || O::contains(medium) || O::contains(big) )
      {
        auto x       = abs(a0);
        auto xnlelim = is_not_less_equal(x, Rempio2_limit[o](as(a0)));
        if constexpr( scalar_value<T> )
        {
          if( xnlelim ) return nan(eve::as<T>());
        }
        else x = if_else(xnlelim, allbits, x);
        auto [fn, xr, dxr] = rempio2[o](x);
        return sin_finalize(a0, fn, xr, dxr);
      }
       else
      {
        auto x = abs(a0);
        if( eve::all(x <= Rempio2_limit[quarter_circle](as(a0))) )
          return sin[quarter_circle](a0);
        else if( eve::all(x <= Rempio2_limit[half_circle](as(a0))))
          return sin[half_circle](a0);
        else if( eve::all(x <= Rempio2_limit[full_circle](as(a0))))
          return sin[full_circle](a0);
        else if( eve::all(x <= Rempio2_limit[medium](as(a0))))
          return sin[medium](a0);
        else
          return sin[big](a0);
      }
    }
  }
}
