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
#include <eve/module/math/decorator/trigo_tags.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/constant/pio_4.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>
#include <eve/module/math/regular/rempio2.hpp>

namespace eve
{
  template<typename Options>
  struct cot_t : elementwise_callable<cot_t, Options, quarter_circle_option, half_circle_option,
                                      full_circle_option, medium_option, big_option>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cot_t, cot_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var cot
//!
//! @brief Callable object computing th cotangent.
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
//!      T cot(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) cotangent of the input.
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, Nan is returned.
//!      * If the element is a `NaN`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/cot.cpp}
//!
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================
 inline constexpr auto cot = functor<cot_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T cot_(EVE_REQUIRES(cpu_), O const& o , T const& a0)
    {
      auto x =  eve::abs(a0);
      if constexpr(O::contains(quarter_circle2))
      {
        auto aa0nlepio4 = is_not_less_equal(x, pio_4(eve::as<T>()));
        if constexpr( scalar_value<T> )
        {
          return (aa0nlepio4) ? nan(eve::as<T>()) : rec[pedantic2](tancot_eval(a0));
        }
        else { return if_else(aa0nlepio4, eve::allbits, rec[pedantic2](tancot_eval(a0))); }
      }
      else if constexpr(O::contains(half_circle2))
      {
        auto xleeps = x <= eps(as<T>());
        auto reduce = [](auto x)
          {
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
          if( xleeps ) return rec[pedantic2](a0);
          if( is_not_less_equal(x, pio_2(eve::as<T>())) ) return nan(eve::as<T>());
          i_t n = x > pio_4(eve::as<T>());
          if( n )
          {
            auto xr = reduce(x);
            T    y  = tancot_eval(xr);
            return bit_xor(bitofsign(a0), -y);
          }
          else { return rec[pedantic2](tancot_eval(a0)); }
        }
        else
        {
          auto xnlepio4 = is_not_less_equal(x, pio_4(eve::as(x)));
          auto fn       = one[xnlepio4](eve::as(x));
          auto xr       = if_else(fn, reduce(x), x);
          auto y        = tancot_eval(xr);
          y             = if_else(is_not_finite(a0), eve::allbits, if_else(xnlepio4, -y, rec[pedantic2](y)));
          return if_else(xleeps, rec[pedantic2](a0), bit_xor(bitofsign(a0), y));
        }
      }
      else if constexpr(O::contains(full_circle2) || O::contains(medium2) || O::contains(big2) )
      {
        auto xnlelim = is_not_less_equal(x, Rempio2_limit[o](as(a0)));
        if constexpr( scalar_value<T> )
        {
          if( xnlelim ) return nan(eve::as<T>());
        }
        else x = if_else(xnlelim, allbits, x);
        auto [fn, xr, dxr] = rempio2[o](x);
        return cot_finalize(a0, fn, xr, dxr);
      }
      else
      {
        if( eve::all(x <= Rempio2_limit[quarter_circle2](as(a0))) )
          return cot[quarter_circle2](a0);
        else if( eve::all(x <= Rempio2_limit[half_circle2](as(a0))))
          return cot[half_circle2](a0);
        else if( eve::all(x <= Rempio2_limit[full_circle2](as(a0))))
          return cot[full_circle2](a0);
        else if( eve::all(x <= Rempio2_limit[medium2](as(a0))))
          return cot[medium2](a0);
        else
          return cot[big2](a0);
      }
    }
  }
}
