//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/constant/minlogdenormal.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_greater_equal.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/pedantic/ldexp.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/sqr.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T exp_(EVE_SUPPORTS(cpu_), pedantic_type const &
                                  , T x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t       = element_type_t<T>;
      auto minlogval = [](){
        if constexpr((!eve::platform::supports_denormals) )
        {
          return  minlog(eve::as<T>());
        }
        else
        {
          return minlogdenormal(eve::as<T>());
        }
      };
      const T Log_2hi   = Ieee_constant<T, 0x3f318000U, 0x3fe62e42fee00000ULL>();
      const T Log_2lo   = Ieee_constant<T, 0xb95e8083U, 0x3dea39ef35793c76ULL>();
      const T Invlog_2  = Ieee_constant<T, 0x3fb8aa3bU, 0x3ff71547652b82feULL>();
      auto    xltminlog = x <= minlogval();
      auto    xgemaxlog = x >= maxlog(eve::as(x));
      if constexpr( scalar_value<T> )
      {
        if( xgemaxlog ) return inf(eve::as(x));
        if( xltminlog ) return zero(eve::as(x));
      }
      auto c = nearest(Invlog_2 * x);
      auto k = c;
      x      = fnma(c, Log_2hi, x); // x-c*L
      if constexpr( std::is_same_v<elt_t, float> )
      {
        x      = fnma(c, Log_2lo, x);
        auto y = horn<T, 0x3f000000, 0x3e2aa9a5, 0x3d2aa957, 0x3c098d8b, 0x3ab778cf>(x);
        c      = inc(fma(y, sqr(x), x));
      }
      else if constexpr( std::is_same_v<elt_t, double> )
      {
        auto hi = x;
        auto lo = c * Log_2lo;
        x       = hi - lo;
        auto t  = sqr(x);
        c       = fnma(t,
                 horn<T,
                      0x3fc555555555553eull,
                      0xbf66c16c16bebd93ull,
                      0x3f11566aaf25de2cull,
                      0xbebbbd41c5d26bf1ull,
                      0x3e66376972bea4d0ull>(t),
                 x); // x-h*t
        c       = oneminus((((lo - (x * c) / (T(2) - c)) - hi)));
      }
      auto z = pedantic(ldexp)(c, k);
      if constexpr( simd_value<T> )
      {
        z = if_else(xltminlog, eve::zero, z);
        z = if_else(xgemaxlog, inf(eve::as(x)), z);
      }
      return z;
    }
    else
      return apply_over(pedantic(exp), x);
  }
}
