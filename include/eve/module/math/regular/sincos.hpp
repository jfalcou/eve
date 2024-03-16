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
  struct sincos_t : elementwise_callable<sincos_t, Options, quarter_circle_option, half_circle_option, full_circle_option, medium_option, big_option>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE kumi::tuple<T, T> operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sincos_t, sincos_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var sincos
//!
//! @brief Callable object computing the simultaneous  computation of sine an cosine.
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
//!      kumi::tuple<T, T> sincos(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//! The computation returns a pair and is semantically equivalent to `{sin(x), cos(x)}`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sincos.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================
 inline constexpr auto sincos = functor<sincos_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE kumi::tuple<T, T>
    sincos_(EVE_REQUIRES(cpu_), O const& o , T const& a0)
    {
      auto x       = abs(a0);
      if constexpr(O::contains(quarter_circle2))
      {
        if constexpr( has_native_abi_v<T> )
        {
          auto pi2_16 = pi2o_16[upward](as<T>());
          auto x2          = sqr(a0);
          auto x2nlepi2_16 = is_not_less_equal(x2, pi2_16);
          if constexpr( scalar_value<T> )
          {
            return (x2nlepi2_16) ? kumi::tuple<T, T> {nan(eve::as<T>()), nan(eve::as<T>())}
            : kumi::tuple<T, T> {sin_eval(x2, a0), cos_eval(x2)};
          }
          else
          {
            x2 = if_else(x2nlepi2_16, eve::allbits, x2);
            return {sin_eval(x2, a0), cos_eval(x2)};
          }
        }
        else return apply_over2(sincos[quarter_circle2], a0);
      }
      else if constexpr(O::contains(half_circle2))
      {
        if constexpr( has_native_abi_v<T> )
        {
          auto reduce = [](auto x){
            auto pio2_1 = ieee_constant<0x1.921f000p+0f, 0x1.921fb54400000p+0>(eve::as<T>{});
            auto pio2_2 = ieee_constant<0x1.6a88000p-17f, 0x1.0b4611a600000p-34>(eve::as<T>{});
            auto pio2_3 = ieee_constant<0x1.0b46000p-34f, 0x1.3198a2e000000p-69>(eve::as<T>{});

            T xr = x - pio2_1;
            xr -= pio2_2;
            xr -= pio2_3;

            return xr;
          };

          if constexpr( scalar_value<T> )
          {
            using i_t = as_integer_t<T, signed>;

            if( is_less_equal(x, eps(as<T>())) ) return {a0, one(eve::as<T>())};
            if( is_not_less_equal(x, pio_2(eve::as<T>())) ) return {nan(eve::as<T>()), nan(eve::as<T>())};

            i_t n = x > pio_4(eve::as<T>());

            if( n )
            {
              auto xr = reduce(x);
              return {bit_xor(bitofsign(a0), cos_eval(sqr(xr))),
                  bit_xor(sin_eval(sqr(xr), xr), n << (sizeof(T) * 8 - 1))};
            }
            else { return {sin_eval(sqr(x), a0), cos_eval(sqr(x))}; }
          }
          else
          {
            x           = if_else(is_not_less_equal(x, pio_2(eve::as<T>())), eve::allbits, x);
            auto test   = is_not_less_equal(x, pio_4(eve::as<T>()));
            auto n      = binarize(test);
            auto xr     = if_else(test, reduce(x), x);
            auto [s, c] = sincos_finalize(a0, n, xr, T(0));
            return {s, c};
          }
        }
        else { return apply_over2(sincos[half_circle2], a0); }
      }
      else if constexpr(O::contains(full_circle2) || O::contains(medium2) || O::contains(big2) )
      {
        if constexpr( has_native_abi_v<T> )
        {
          auto xnlelim = is_not_less_equal(x, Rempio2_limit[o](as(a0)));
          if constexpr( scalar_value<T> )
          {
            if( xnlelim ) return {nan(eve::as<T>()), nan(eve::as<T>())};
          }
          else x = if_else(xnlelim, allbits, x);
          auto [fn, xr, dxr] = rempio2[o](x);
          auto [s, c]        = sincos_finalize(bitofsign(a0), fn, xr, dxr);
          return {s, c};
        }
        else { return apply_over2(sincos[o], a0); }
      }
      else
      {
        if constexpr( has_native_abi_v<T> )
        {
         if( eve::all(x <= Rempio2_limit[quarter_circle2](as(a0))) )
          return sincos[quarter_circle2](a0);
        else if( eve::all(x <= Rempio2_limit[half_circle2](as(a0))))
          return sincos[half_circle2](a0);
        else if( eve::all(x <= Rempio2_limit[full_circle2](as(a0))))
          return sincos[full_circle2](a0);
        else if( eve::all(x <= Rempio2_limit[medium2](as(a0))))
          return sincos[medium2](a0);
        else
          return sincos[big2](a0);
        }
        else return apply_over2(sincos, a0);
      }
    }
  }
}
