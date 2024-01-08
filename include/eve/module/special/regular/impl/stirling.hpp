//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{
  template<floating_ordered_value T, decorator D>
  EVE_FORCEINLINE constexpr T
  stirling_(EVE_SUPPORTS(cpu_), D const&, T a0) noexcept
  requires(is_one_of<D>(types<regular_type, pedantic_type> {}))
  {
    using elt_t = element_type_t<T>;
    if constexpr( has_native_abi_v<T> )
    {
      auto stirling1 = [](const T& x)
        {
          if constexpr( std::is_same_v<elt_t, float> )
          {
            return
            eve::reverse_horner(x, T(0x1.555556p-4f), T(0x1.c71c72p-9f)
                               , T(-0x1.5f7260p-9f), T(-0x1.e166b2p-13f))
            ;
          }
          else if constexpr( std::is_same_v<elt_t, double> )
          {
            return
            eve::reverse_horner(x, T(0x1.5555555555986p-4), T(0x1.c71c71b98c5fdp-9), T(-0x1.5f72607d44fd7p-9)
                               , T(-0x1.e166b27e61d7cp-13), T(0x1.9cc72592d7293p-11))
            ;
          }
        };
      const T Stirlingsplitlim =
        ieee_constant<T>(0x1.ac51ec0p+4f, 0x1.1e083ba3443d4p+7);
      const T Stirlinglargelim =
        ieee_constant<T>(0x1.1851e60p+5f, 0x1.5800000000000p+7);
      const T Sqrt_2pi = ieee_constant<T>(0x1.40d9320p+1f, 0x1.40d931ff62704p+1);
      if constexpr( simd_value<T> )
      {
        a0        = if_else(is_gez(a0), a0, eve::allbits);
        T w       = rec(a0);
        w         = fma(w, stirling1(w), one(eve::as<T>()));
        T    y    = exp(-a0);
        auto test = is_less(a0, Stirlingsplitlim);
        T    z    = a0 - half(eve::as<T>());
        z         = if_else(test, z, half(eve::as<T>()) * z);
        T v       = pow_abs(a0, z);
        y *= v;
        y = if_else(test, y, y * v); /* Avoid overflow in pow() */
        y *= Sqrt_2pi * w;
        y = if_else(a0 == inf(eve::as<T>()), a0, y);
        return if_else(a0 > Stirlinglargelim, inf(eve::as<T>()), y);
      }
      else if constexpr( scalar_value<T> )
      {
        if( is_ltz(a0) ) return nan(eve::as<T>());
        if( is_nan(a0) ) return a0;
        if( a0 > Stirlinglargelim ) return inf(eve::as<T>());
        T w = rec(a0);
        w   = fma(w, stirling1(w), one(eve::as<T>()));
        T y = exp(-a0);
        if( is_eqz(y) ) return inf(eve::as<T>());
        T z = a0 - half(eve::as<T>());
        if( a0 >= Stirlingsplitlim )
        { /* Avoid overflow in pow() */
          const T v = pow_abs(a0, z * half(eve::as<T>()));
          y *= v;
          y *= v;
        }
        else { y *= pow_abs(a0, z); }
        y *= Sqrt_2pi * w;
        return y;
      }
    }
    else return apply_over(stirling, a0);
  }

  template<floating_ordered_value T>
  EVE_FORCEINLINE constexpr T
  stirling_(EVE_SUPPORTS(cpu_), T const& x) noexcept
  {
    return stirling(regular_type(), x);
  }

// -----------------------------------------------------------------------------------------------
// Masked cases
  template<conditional_expr C, typename ... Ts>
  EVE_FORCEINLINE auto
  stirling_(EVE_SUPPORTS(cpu_), C const& cond, Ts ... ts) noexcept
  {
    return mask_op(cond, eve::stirling, ts ...);
  }

  template<conditional_expr C, decorator D, typename  ... Ts>
  EVE_FORCEINLINE auto
  stirling_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, Ts ... ts) noexcept
  {
    return mask_op(cond, d(eve::stirling), ts ...);
  }
}
