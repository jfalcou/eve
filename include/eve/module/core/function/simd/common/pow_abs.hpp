//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_POW_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_POW_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/binarize.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_gtz.hpp>   
#include <eve/function/is_less.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>  
#include <eve/function/fnma.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/log.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/shl.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/module/core/detail/generic/pow_kernel.hpp>
#include <eve/platform.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T, typename U>
  EVE_FORCEINLINE auto pow_abs_(EVE_SUPPORTS(cpu_)
                               , T const &a, U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>, T, U>,
            detail::either<is_vectorized_v<T>, is_vectorized_v<U>>,
            behave_as<floating_point,T>,
            floating_point<value_type_t<U>>)
  {
    if constexpr(!is_vectorized_v<U>)
    {
      return pow_abs(a, T{b});
    }
    else if constexpr(!is_vectorized_v<T>)
    {
      return pow_abs(U{a}, b);
    }
    else
    {
      if constexpr(std::is_same_v<T, U>)
      {
        const T Oneo_16 = T(0.0625); 
//        using i_t = as_integer_t<T>;
        T ax = eve::abs(a);
        auto [xm, e] = pedantic_(ifrexp)(ax);
        auto [x, i] = detail::kernel_select(xm);
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
        T ya = reduc(b);
        T yb = b - ya;
        T W = fma(z, b, w*yb);
        T Wa = reduc(W);
        T Wb = W - Wa;
        W = fma(w, ya, Wa);
        Wa = reduc(W);
        T u = W - Wa;
        W = Wb + u;
        Wb = reduc(W);
        w = T(16)*(Wa + Wb);
        // Test the power of 2 for over/underflow
        const T Powlargelim = Ieee_constant <T, 0x44ffe000U, 0x40cfff8000000000ULL>();
        const T Powlowlim   = Ieee_constant <T, 0xc5160000U, 0xc0d0c7c000000000ULL>();
        auto inf_ret = is_greater(w, Powlargelim);
        auto zer_ret = is_less(w, Powlowlim);
        e = toint(w);
        Wb = W - Wb;
        auto test = is_gtz(Wb);
        e = inc[test](e);
        Wb = sub[test](Wb,Oneo_16);
        z = detail::kernel_pow2(Wb)*Wb;
        i = inc[is_gtz(e)](e/16); //is_gtz ?
        e = i*16-e; 
        w =  detail::twomio16(e);
        z = fma(w, z, w);
        z = pedantic_(ldexp)( z, i );
        if constexpr(eve::platform::supports_infinites)
        {
          auto gtax1 = is_greater(ax,One<T>());
          z =  if_else(is_equal(b,  Inf<T>()),if_else(gtax1, Inf<T>(), eve::zero_), z);
          z =  if_else(is_equal(b, Minf<T>()),if_else(gtax1, eve::zero_, Inf<T>()), z);
          z =  if_else(is_equal(ax, Inf<T>()),
                       if_else(is_gtz(b),
                               Inf<T>(),
                               binarize(is_gez(b))),
                       z);
        }
        z = if_else(zer_ret, eve::zero_, z);
        z = if_else(inf_ret, Inf<T>(), z);
        z = if_else(is_equal(ax, One<T>()), ax, z);
        
        z = if_else(is_eqz(a),
                    if_else(is_ltz(b), eve::Inf<T>(),
                            binarize(is_eqz(b))
                           ),
                    z
                   );
        if constexpr(eve::platform::supports_invalids)
        {
          z = if_else(is_nan(a),
                      if_else(is_eqz(b), One<T>(), eve::allbits_),
                      z
                     );
        }
        return z;
      }
    }
  }  


  template<typename T, typename U>
  EVE_FORCEINLINE auto pow_abs_(EVE_SUPPORTS(cpu_)
                               , raw_type const &
                               , T const &a, U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>, T, U>,
            detail::either<is_vectorized_v<T>, is_vectorized_v<U>>,
            behave_as<floating_point,T>,
            floating_point<value_type_t<U>>)
  {
    if constexpr(!is_vectorized_v<U>)
    {
      return pow_abs(a, T{b});
    }
    else if constexpr(!is_vectorized_v<T>)
    {
      return pow_abs(U{a}, b);
    }
    else
    {
      if constexpr(std::is_same_v<T, U>)
      {
        return exp(b*log(eve::abs(a))); 
      }
    }
  }
  
}

#endif
