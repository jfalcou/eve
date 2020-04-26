//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_EXP2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_EXP2_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/maxlog2.hpp>
#include <eve/constant/minlog2.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta/traits.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/sqr.hpp>
#include <eve/module/core/detail/generic/horn.hpp>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr T exp2_(EVE_SUPPORTS(cpu_), D const &, T x) noexcept
      requires(contains<D>(types<regular_type, pedantic_type> {}))
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t     = element_type_t<T>;
      auto xltminlog2 = x < Minlog2(as(x));
      auto xgemaxlog2 = x >= Maxlog2(as(x));
      if constexpr( scalar_value<T> )
      {
        if( xgemaxlog2 )
          return Inf(as(x));
        if( xltminlog2 )
          return Zero(as(x));
      }
      auto k = nearest(x);
      x      = x - k;
      if constexpr( std::is_same_v<elt_t, float> )
      {
        T y = horn<T, 0x3e75fdf1, 0x3d6356eb, 0x3c1d9422, 0x3ab01218, 0x3922c8c4>(x);
        x   = inc(fma(y, sqr(x), x * Log_2<T>()));
      }
      else if constexpr( std::is_same_v<elt_t, double> )
      {
        x *= Log_2<T>();
        T    t = sqr(x);
        auto h = horn<T,
                      0x3fc555555555553eull,
                      0xbf66c16c16bebd93ull,
                      0x3f11566aaf25de2cull,
                      0xbebbbd41c5d26bf1ull,
                      0x3e66376972bea4d0ull>(t);
        T    c = fnma(t, h, x); // x-h*t
        x      = oneminus(((-(x * c) / (T(2) - c)) - x));
      }
      auto z = D()(ldexp)(x, k);
      if constexpr( simd_value<T> )
      {
        z = if_else(xltminlog2, eve::zero_, z);
        z = if_else(xgemaxlog2, Inf(as(x)), z);
      }
      return z;
    }
    else
      return apply_over(exp2, x);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T exp2_(EVE_SUPPORTS(cpu_), T const &x) noexcept
  {
    return exp2(regular_type(), x);
  }
}

#endif
