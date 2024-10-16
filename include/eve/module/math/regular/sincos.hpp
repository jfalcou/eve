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
  struct sincos_t : elementwise_callable<sincos_t, Options
                                        , quarter_circle_option, half_circle_option
                                        , full_circle_option, medium_option, big_option
                                        >
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE zipped<T,T> operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sincos_t, sincos_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var sincos
//!
//! @brief `elementwise_callable` object computing the simultaneous  computation of sine an cosine.
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
//!      constexpr auto sincos(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sincos[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto sincos[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto sincos[quarter_circle](floating_value auto x)          noexcept; // 3.a
//!      constexpr auto sincos[half_circle](floating_value auto x)             noexcept; // 3.b
//!      constexpr auto sincos[full_circle](floating_value auto x)             noexcept; // 3.c
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!      * `x`: [floating value](@ref floating_value).
//!      * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!      * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!   1 .The computation returns a tuple-like whose elements are `sin(x)` and `cos(x)`
//!   2. [The operation is performed conditionnaly](@ref conditional).
//!   3. These are optimized calls providing a balance between speed and range limitation.
//!        1. assumes that the inputs elements  belong to \f$[-\pi/4,\pi/4]\f$ and return NaN outside.
//!        2. assumes that the inputs elements  belong to \f$[-\pi/2,\pi/2]\f$ and return NaN outside.
//!        3. assumes that the inputs elements  belong to \f$[-\pi,\pi]\f$ and return NaN outside.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/sincos.cpp}
//================================================================================================
 inline constexpr auto sincos = functor<sincos_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE auto sincos_(EVE_REQUIRES(cpu_), O const& o , T const& a0)
    {
      auto x       = abs(a0);
      if constexpr(O::contains(quarter_circle))
      {
        auto pi2_16 = pi2o_16[upper](as<T>());
        auto x2          = sqr(a0);
        auto x2nlepi2_16 = is_not_less_equal(x2, pi2_16);
        if constexpr( scalar_value<T> )
        {
          return  (x2nlepi2_16) ? eve::zip(nan(eve::as<T>()), nan(eve::as<T>()))
                                : eve::zip(sin_eval(x2, a0), cos_eval(x2));
        }
        else
        {
          x2 = if_else(x2nlepi2_16, eve::allbits, x2);
          return eve::zip(sin_eval(x2, a0), cos_eval(x2));
        }
      }
      else if constexpr(O::contains(half_circle))
      {
        auto reduce = [](auto xx)
        {
          auto pio2_1 = ieee_constant<0x1.921f000p+0f, 0x1.921fb54400000p+0>(eve::as<T>{});
          auto pio2_2 = ieee_constant<0x1.6a88000p-17f, 0x1.0b4611a600000p-34>(eve::as<T>{});
          auto pio2_3 = ieee_constant<0x1.0b46000p-34f, 0x1.3198a2e000000p-69>(eve::as<T>{});

          T xr = xx - pio2_1;
          xr -= pio2_2;
          xr -= pio2_3;

          return xr;
        };

        if constexpr( scalar_value<T> )
        {
          using i_t = as_integer_t<T, signed>;

          if( is_less_equal(x, eps(as<T>())) ) return eve::zip(a0, one(eve::as<T>()));
          if( is_not_less_equal(x, pio_2(eve::as<T>())) ) return eve::zip(nan(eve::as<T>()), nan(eve::as<T>()));

          i_t n = x > pio_4(eve::as<T>());

          if( n )
          {
            auto xr = reduce(x);
            return eve::zip ( bit_xor(bitofsign(a0), cos_eval(sqr(xr)))
                            , bit_xor(sin_eval(sqr(xr), xr), n << (sizeof(T) * 8 - 1))
                            );
          }
          else return eve::zip(sin_eval(sqr(x), a0), cos_eval(sqr(x)));
        }
        else
        {
          x           = if_else(is_not_less_equal(x, pio_2(eve::as<T>())), eve::allbits, x);
          auto test   = is_not_less_equal(x, pio_4(eve::as<T>()));
          auto n      = one[test](eve::as(x));
          auto xr     = if_else(test, reduce(x), x);
          auto [s, c] = sincos_finalize(a0, n, xr, T(0));
          return eve::zip(s, c);
        }
      }
      else if constexpr(O::contains(full_circle) || O::contains(medium) || O::contains(big) )
      {
        auto xnlelim = is_not_less_equal(x, Rempio2_limit[o](as(a0)));
        if constexpr( scalar_value<T> )
        {
          if( xnlelim ) return eve::zip(nan(eve::as<T>()), nan(eve::as<T>()));
        }
        else x = if_else(xnlelim, allbits, x);
        auto [fn, xr, dxr] = rempio2[o](x);
        auto [s, c]        = sincos_finalize(bitofsign(a0), fn, xr, dxr);
        return eve::zip(s, c);
      }
      else
      {
        if( eve::all(x <= Rempio2_limit[quarter_circle](as(a0))) )   return sincos[quarter_circle](a0);
        else if( eve::all(x <= Rempio2_limit[half_circle](as(a0))))  return sincos[half_circle](a0);
        else if( eve::all(x <= Rempio2_limit[full_circle](as(a0))))  return sincos[full_circle](a0);
        else if( eve::all(x <= Rempio2_limit[medium](as(a0))))       return sincos[medium](a0);
        else                                                          return sincos[big](a0);
      }
    }
  }
}
