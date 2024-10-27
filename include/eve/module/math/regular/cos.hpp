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
  struct cos_t : elementwise_callable<cos_t, Options, quarter_circle_option, half_circle_option, full_circle_option,
                                                      medium_option, big_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cos_t, cos_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//!   @var cos
//!   @brief `elementwise_callable` object computing the cosine.
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
//!      constexpr auto cos(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto cos[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto cos[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto cos[quarter_circle](floating_value auto x)          noexcept; // 3.a
//!      constexpr auto cos[half_circle](floating_value auto x)             noexcept; // 3.b
//!      constexpr auto cos[full_circle](floating_value auto x)             noexcept; // 3.c
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!    * `x`: [floating value](@ref eve::floating_value).
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) cosine of the input.
//!      In particular:
//!        * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!        * If the element is \f$\pm\infty\f$, Nan is returned.
//!        * If the element is a `Nan`, `Nan` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!    3. These are optimized calls providing a balance between speed and range limitation.
//!        1. assumes that the inputs elements  belong to \f$[-\pi/4,\pi/4]\f$ and return NaN outside.
//!        2. assumes that the inputs elements  belong to \f$[-\pi/2,\pi/2]\f$ and return NaN outside.
//!        3. assumes that the inputs elements  belong to \f$[-\pi,\pi]\f$ and return NaN outside.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/cos)
//!   *  [Wikipedia](https://fr.wikipedia.org/wiki/Cosinus)
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/Cosine.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/math/cos.cpp}
//================================================================================================
 inline constexpr auto cos = functor<cos_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T cos_(EVE_REQUIRES(cpu_), O const& o , T const& a0)
    {
      if constexpr(O::contains(quarter_circle))
      {
        auto x2          = sqr(a0);
        auto x2nlepi2_16 = is_not_less_equal(x2, pi2o_16[upper](as(a0)));
        if constexpr( scalar_value<T> ) return (x2nlepi2_16) ? nan(eve::as<T>()) : cos_eval(x2);
        else return if_else(x2nlepi2_16, eve::allbits, cos_eval(x2));
      }
      else if constexpr(O::contains(half_circle))
      {
        T    x         = eve::abs(a0);
        auto xnlepio2 = is_not_less_equal(x, pio_2(eve::as<T>()));
        if constexpr( scalar_value<T> )
          if( xnlepio2 ) return nan(eve::as<T>());

        auto reduce = [](auto xx){
          auto pio2_1 = ieee_constant<0x1.921f000p+0f, 0x1.921fb54400000p+0>(eve::as<T>{});
          auto pio2_2 = ieee_constant<0x1.6a88000p-17f, 0x1.0b4611a600000p-34>(eve::as<T>{});
          auto pio2_3 = ieee_constant<0x1.0b46000p-34f, 0x1.3198a2e000000p-69>(eve::as<T>{});
          auto xr     = xx - pio2_1;
          xr -= pio2_2;
          xr -= pio2_3;
          return xr;
        };
        if constexpr( scalar_value<T> )
        {
          using i_t = as_integer_t<T, signed>;
          i_t n     = x > pio_4(eve::as<T>());
          if( n )
          {
            auto xr = reduce(x);
            return bit_xor(sin_eval(sqr(xr), xr), n << (sizeof(T) * 8 - 1));
          }
          else
            return cos_eval(sqr(x));
        }
        else
        {
          auto n        = one[is_not_less_equal(x, pio_4(eve::as(x)))](eve::as(x));
          auto sign_bit   = signmask[is_nez(n)](eve::as(x));
          auto xr       = reduce(x);
          xr            = if_else(n, xr, x);
          auto z        = sqr(xr);
          auto se       = bit_xor(sin_eval(z, xr), sign_bit);
          auto ce       = cos_eval(z);
          auto z1       = if_else(n, se, ce);
          return if_else(xnlepio2, eve::allbits, z1);
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
        else
          x = if_else(xnlelim, allbits, x);
        auto [fn, xr, dxr] = rempio2[o](x);
        return cos_finalize(fn, xr, dxr);
      }
      else
      {
        auto x = abs(a0);
        if( eve::all(x <= Rempio2_limit[quarter_circle](as(a0))) )
          return cos[quarter_circle](a0);
        else if( eve::all(x <= Rempio2_limit[half_circle](as(a0))))
          return cos[half_circle](a0);
        else if( eve::all(x <= Rempio2_limit[full_circle](as(a0))))
          return cos[full_circle](a0);
        else if( eve::all(x <= Rempio2_limit[medium](as(a0))))
          return cos[medium](a0);
        else
          return cos[big](a0);
      }
    }
  }
}
