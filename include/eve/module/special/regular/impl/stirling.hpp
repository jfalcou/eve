//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{
template<floating_real_value T, decorator D>
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
        return horn<T, 0x3daaaaab, 0x3b638e39, 0xbb2fb930, 0xb970b359>(x);
      }
      else if constexpr( std::is_same_v<elt_t, double> )
      {
        return horn<T,
                    0x3fb5555555555986ll, //   8.33333333333482257126E-2
                    0x3f6c71c71b98c5fdll, //   3.47222221605458667310E-3
                    0xbf65f72607d44fd7ll, //  -2.68132617805781232825E-3
                    0xbf2e166b27e61d7cll, //  -2.29549961613378126380E-4
                    0x3f49cc72592d7293ll  //   7.87311395793093628397E-4
                    >(x);
      }
    };
    const T Stirlingsplitlim =
        Ieee_constant<T, 0X41D628F6U, 0X4061E083BA3443D4ULL>(); // 26.77f, 143.01608
    const T Stirlinglargelim =
        Ieee_constant<T, 0X420C28F3U, 0x4065800000000000ULL>();                // 35.0399895f, 172
    const T Sqrt_2pi = Ieee_constant<T, 0X40206C99U, 0X40040D931FF62704ULL>(); // 2.50662827463100
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
#ifndef BOOST_SIMD_NO_INFINITIES
      y = if_else(a0 == inf(eve::as<T>()), a0, y);
#endif
      return if_else(a0 > Stirlinglargelim, inf(eve::as<T>()), y);
    }
    else if constexpr( scalar_value<T> )
    {
      if( is_ltz(a0) ) return nan(eve::as<T>());
#ifndef BOOST_SIMD_NO_INVALIDS
      if( is_nan(a0) ) return a0;
#endif
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

template<floating_real_value T>
EVE_FORCEINLINE constexpr T
stirling_(EVE_SUPPORTS(cpu_), T const& x) noexcept
{
  return stirling(regular_type(), x);
}
}
