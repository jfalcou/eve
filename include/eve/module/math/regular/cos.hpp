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
#include <eve/module/math/decorator/trigo_tags.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/rempio2.hpp>

namespace eve
{
  template<typename Options>
  struct cos_t : elementwise_callable<cos_t, Options, quarter_circle_option, half_circle_option, full_circle_option, medium_option, big_option>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cos_t, cos_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var cos
//!
//! @brief Callable object computing the cosine.
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
//!      template< eve::floating_value T >
//!      T cos(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) cosine of the input.
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, Nan is returned.
//!      * If the element is a `Nan`, `Nan` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/cos.cpp}
//!
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================
 inline constexpr auto cos = functor<cos_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T cos_(EVE_REQUIRES(cpu_), O const& o , T const& a0)
    {
      if constexpr(O::contains(quarter_circle2))
      {
        auto x2          = sqr(a0);
        auto x2nlepi2_16 = is_not_less_equal(x2, pi2o_16[upward](as(a0)));
        if constexpr( scalar_value<T> ) return (x2nlepi2_16) ? nan(eve::as<T>()) : cos_eval(x2);
        else return if_else(x2nlepi2_16, eve::allbits, cos_eval(x2));
      }
      else if constexpr(O::contains(half_circle2))
      {
        T    x         = eve::abs(a0);
        auto xnlepio2 = is_not_less_equal(x, pio_2(eve::as<T>()));
        if constexpr( scalar_value<T> )
          if( xnlepio2 ) return nan(eve::as<T>());

        auto reduce = [](auto x){
          auto pio2_1 = ieee_constant<0x1.921f000p+0f, 0x1.921fb54400000p+0>(eve::as<T>{});
          auto pio2_2 = ieee_constant<0x1.6a88000p-17f, 0x1.0b4611a600000p-34>(eve::as<T>{});
          auto pio2_3 = ieee_constant<0x1.0b46000p-34f, 0x1.3198a2e000000p-69>(eve::as<T>{});
          auto xr     = x - pio2_1;
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
      else if constexpr(O::contains(full_circle2) || O::contains(medium2) || O::contains(big2) )
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
        if( eve::all(x <= Rempio2_limit[quarter_circle2](as(a0))) )
          return cos[quarter_circle2](a0);
        else if( eve::all(x <= Rempio2_limit[half_circle2](as(a0))))
          return cos[half_circle2](a0);
        else if( eve::all(x <= Rempio2_limit[full_circle2](as(a0))))
          return cos[full_circle2](a0);
        else if( eve::all(x <= Rempio2_limit[medium2](as(a0))))
          return cos[medium2](a0);
        else
          return cos[big2](a0);
      }
    }
  }
}
