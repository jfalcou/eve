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
  struct tan_t : elementwise_callable<tan_t, Options, quarter_circle_option, half_circle_option, full_circle_option, medium_option, big_option>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(tan_t, tan_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var tan
//!
//! @brief Callable object computing the tangent.
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
//!      T tan(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) tangent of the input.
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, Nan is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/tan.cpp}
//!
//!
//!  @godbolt{doc/math/regular/tan.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================
 inline constexpr auto tan = functor<tan_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T tan_(EVE_REQUIRES(cpu_), O const& o , T a0)
    {
      if constexpr(O::contains(quarter_circle2))
      {
        if constexpr( scalar_value<T> )
        {
          if( is_not_less_equal(eve::abs(a0), pio_4(eve::as<T>())) ) return nan(eve::as<T>());
        }
        else
        {
          auto pi2_16 =  pi2o_16[upward](as<T>());
          a0 = if_else(is_not_less_equal(sqr(a0), pi2_16), eve::allbits, a0);
        }
        return tancot_eval(a0);
      }
      else if constexpr(O::contains(half_circle2))
      {
        auto reduce = [](auto x)
          {
            auto pio2_1 = ieee_constant<0x1.921f000p+0f, 0x1.921fb54400000p+0>(eve::as<T>{});
            auto pio2_2 = ieee_constant<0x1.6a88000p-17f, 0x1.0b4611a600000p-34>(eve::as<T>{});
            auto pio2_3 = ieee_constant<0x1.0b46000p-34f, 0x1.3198a2e000000p-69>(eve::as<T>{});
            T    xr     = x - pio2_1;
            xr -= pio2_2;
            xr -= pio2_3;
            return xr;
          };
        T x = eve::abs(a0);
        if constexpr( scalar_value<T> )
        {
          if( x < eps(as<T>()) ) return a0;
          if( is_not_less_equal(x, pio_2(eve::as<T>())) ) return nan(eve::as<T>());
          int n = x > pio_4(eve::as<T>());
          if( n )
          {
            T xr = reduce(x);
            T y  = tancot_eval(xr);
            return bit_xor(bitofsign(a0), -rec[pedantic2](y));
          }
          else { return tancot_eval(a0); }
        }
        else if constexpr( simd_value<T> )
        {
          auto test = is_not_less_equal(x, pio_4(eve::as(a0)));
          T    xr   = if_else(test, reduce(x), x);
          auto y    = tancot_eval(xr);
          y         = if_else(is_not_finite(a0), eve::allbits, if_else(test, -rec[pedantic2](y), y));
          return if_else(x <= eps(as<T>()), a0, bit_xor(bitofsign(a0), y));
        }
      }
      else if constexpr(O::contains(full_circle2) || O::contains(medium2) || O::contains(big2) )
      {
        auto x       = abs(a0);
        auto xnlelim = is_not_less_equal(x, Rempio2_limit[o](as(a0)));
        if constexpr( scalar_value<T> )
        {
          if( xnlelim ) return nan(eve::as<T>());
          if( is_eqz(a0) ) return a0;
        }
        else x = if_else(xnlelim, allbits, x);
        auto [fn, xr, dxr] = rempio2[o](x);
        return tan_finalize(a0, fn, xr, dxr);
      }
      else
      {
        auto x = abs(a0);
        if( eve::all(x <= Rempio2_limit[quarter_circle2](as(a0))) )
          return tan[quarter_circle2](a0);
        else if( eve::all(x <= Rempio2_limit[half_circle2](as(a0))))
          return tan[half_circle2](a0);
        else if( eve::all(x <= Rempio2_limit[full_circle2](as(a0))))
          return tan[full_circle2](a0);
        else if( eve::all(x <= Rempio2_limit[medium2](as(a0))))
          return tan[medium2](a0);
        else
          return tan[big2](a0);
      }
    }
  }
}
