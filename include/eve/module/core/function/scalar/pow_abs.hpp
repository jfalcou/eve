//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_POW_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_POW_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>  
#include <eve/function/fnma.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/log.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/tofloat.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/module/core/detail/generic/pow_kernel.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  pow_abs_(EVE_SUPPORTS(cpu_)
          , T const &a0, T const &a1) noexcept
  requires std::floating_point<T>
  {
    const T Oneo_16 = T(0.0625); 
    using i_t = as_integer_t<T>;
    T xx =  eve::abs(a0);
    if (xx == One<T>()) return xx;
    if (is_eqz(xx)) return is_eqz(a1) ? One<T>() : is_ltz(a1) ? Inf<T>() : Zero<T>();
    if constexpr(eve::platform::supports_infinites)
    {
      if(xx == a1 && a1 == Inf<T>())  return Inf<T>();
      if(xx == Inf<T>() && a1 == Minf<T>()) return Zero<T>();
      if(a1 == Inf<T>()) return (xx < One<T>()) ? Zero<T>() : Inf<T>();
      if(a1 == Minf<T>()) return (xx >  One<T>()) ? Zero<T>() : Inf<T>();
      if(xx == Inf<T>()) return (a1 < Zero<T>()) ? Zero<T>() : ((a1 == Zero<T>()) ? One<T>() : Inf<T>());
    }
    if constexpr(eve::platform::supports_invalids)
    {
      if(is_nan(a0)) return is_eqz(a1) ? One<T>() : a0;
      if(is_nan(a1)) return Nan<T>();
    }
    auto [xm, e] = pedantic_(eve::ifrexp)(xx);
    auto [x, i]  = detail::kernel_select(xm);
    T z = sqr(x);
    T w = detail::kernel_pow1(x, z);
    w = fma(Mhalf<T>(), z, w);
    const T Log2_em1 = T(0.44269504088896340735992468100189); 
    w = fma(Log2_em1, w, w);
    z = fma(Log2_em1, x, w);
    z += x;
    w =  fnma(tofloat(i), Oneo_16, tofloat(e));
    auto reduc = [](T x) {
      // Find a multiple of 1/16 that is within 1/16 of x.
      return T(0.0625)*floor(T(16)*x);
    };      
    T ya = reduc(a1);
    T yb = a1 - ya;
    T W = fma(z, a1, w*yb);
    T Wa = reduc(W);
    T Wb = W - Wa;
    W = fma(w, ya, Wa);
    Wa = reduc(W);
    T u = W - Wa;
    W = Wb + u;
    Wb = reduc(W);
    w = T(16)*(Wa + Wb);
    
    // Test the power of 2 for overflow
    const T Powlargelim = Ieee_constant <T, 0x44ffe000U, 0x40cfff8000000000ULL>();
    const T Powlowlim   = Ieee_constant <T, 0xc5160000U, 0xc0d0c7c000000000ULL>();
    if( w > Powlargelim) return Inf<T>();
    if( w < Powlowlim  ) return Zero<T>();
    e = w;
    Wb = W - Wb;  //
    if( Wb > 0.0f ) //
    {
      ++e;
      Wb -= Oneo_16; //
    }
    z = detail::kernel_pow2(Wb)*Wb; //
    i = (e/16) + (e>=0);
    e = fms(i, i_t(16), e);
    w =  detail::twomio16(e);
    z = fma(w, z, w);
    z = pedantic_(ldexp)( z, i );
    return z;
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto
  pow_abs_(EVE_SUPPORTS(cpu_)
          , raw_type const &
          , T const &a0, T const &a1) noexcept
  requires std::floating_point<T>
  {
    return exp(a1*log(eve::abs(a0)));
  }
 
}

#endif
