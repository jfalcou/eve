//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/add.hpp>
#include <eve/function/any.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/log.hpp>
#include <eve/function/maximum.hpp>
#include <eve/function/pow.hpp>
#include <eve/function/tgamma.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/halfeps.hpp>
#include <eve/constant/maxlog.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE T exp_int_(EVE_SUPPORTS(cpu_), T x) noexcept
  {

    return exp_int(T(1), x);
  }

  template<integral_scalar_value I, floating_real_scalar_value T>
  EVE_FORCEINLINE T exp_int_(EVE_SUPPORTS(cpu_), I in, T x) noexcept
  {
    if( in == 0 )  return exp(-x)/x;
    if( in < 0  )  return nan(as<T>());
    return exp_int(T(in), x);
  }

  template<integral_simd_value I, floating_real_simd_value T>
  EVE_FORCEINLINE T exp_int_(EVE_SUPPORTS(cpu_), I in, T x) noexcept
  requires compatible_values<T, I>
  {
    using elt_t =  element_type_t<T>;
    return exp_int(convert(in, as<elt_t>()), x);
  }

  template<integral_simd_value I, floating_real_scalar_value T>
  EVE_FORCEINLINE T exp_int_(EVE_SUPPORTS(cpu_), I in, T x) noexcept
  requires compatible_values<T, I>
  {
    using elt_t =  element_type_t<T>;
    using w_t = wide<elt_t, cardinal_t<I>>;
    using i_t = as_integer_t<elt_t>;
    return exp_int(convert(in, as<i_t>()), w_t(x));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T exp_int_(EVE_SUPPORTS(cpu_), T n, T x) noexcept
  {
   using elt_t =  element_type_t<T>;
   if constexpr( has_native_abi_v<T> )
   {
     auto notdone = is_gez(x) && is_flint(n) && is_gez(n);
     T r = nan(as(x)); //if_else(notdone, zero, nan(as(x)));
     auto br_zeron = []  (auto x){ //n == 0
       return exp(-x)/x;
     };
     notdone = next_interval(br_zeron, notdone, is_eqz(n), r, x);
     if (any(notdone))
     {
       auto br_largen = [](auto n,  auto x){ //n >  5000
         T xk = x + n;
         T yk = rec(sqr(xk));
         T t = n;
         T ans = fma(T(-8), x, t);
         ans = t*fma(yk, 6*sqr(x), ans);
         ans = yk*fma(t, fma(T(-2), x, t), ans);
         ans = fma(yk, (ans+t), T(1));
         return ans*exp(-x)/xk;
       };
       notdone = next_interval(br_largen, notdone, n > 5000, r, n, x);
       if (any(notdone))
       {
         auto br_xlt1 = [](auto n,  auto x){ // here x is always le 1
           auto eqzx = is_eqz(x);
           x = inc[eqzx](x); //loop is infinite for x == 0
           auto psi1 = zero(as(x));
           int32_t maxn = maximum(n);
           for( int32_t i=maxn-1; i; --i )  psi1 = add[T(i) < n](psi1, T(rec(i)));
           auto euler = Ieee_constant<T, 0x3f13c468U, 0x3fe2788cfc6fb619ULL>();
           auto psi = -euler-log(x)+psi1;
           T t; ;
           auto z = -x;
           auto xk = zero(as(x));
           auto yk = one(as(x));
           auto pk = oneminus(n);
           auto ans = if_else(is_eqz(pk), zero, rec(pk));
           do
           {
             xk = inc(xk);
             yk *= z/xk;
             pk = inc(pk);
             ans = add[is_nez(pk)](ans, yk/pk);
             t = if_else(is_nez(ans), abs(yk/ans), one);
           }
           while( any(t > halfeps(as(x))));
           auto in = int_(n);
           return add[eqzx]((eve::pow(z, dec(in)) * psi / tgamma(n)) - ans, inf(as(x)));
         };
         auto xlt1 = x < 1;
         T xx = if_else(xlt1, x, one);
         notdone = next_interval(br_xlt1, notdone, xlt1, r, n, xx);
         if(any(notdone))
         {
           auto br_xge1 = [](auto n,  auto x){ // here x is always gt 1
             auto exp_intbig = (sizeof(elt_t) == 8) ? T(1ull << 57) : T(1ull << 24);
             auto r =  exp_intbig;
             int32_t sk = 1;
             T t;
             auto pkm2 = one(as(x));
             auto qkm2 = x;
             auto pkm1 =  one(as(x));
             auto qkm1 = x + n;
             auto ans = pkm1/qkm1;
             do
             {
               auto stest = is_odd(T(++sk));
               auto k_2 = T(sk >> 1);
               auto yk = if_else(stest, one, x);
               auto xk = add[stest](k_2, n);
               auto pk = pkm1 * yk  +  pkm2 * xk;
               auto qk = qkm1 * yk  +  qkm2 * xk;
               r = pk/qk;
               auto test = is_nez(qk);
               t = if_else(test,abs((ans-r)/r),one);
               ans = if_else(test, r, ans);
               pkm2 = pkm1;
               pkm1 = pk;
               qkm2 = qkm1;
               qkm1 = qk;
               test = abs(pk) > exp_intbig;
               auto fac = if_else(test, halfeps(as(x)), one);
               pkm2 *= fac;
               pkm1 *= fac;
               qkm2 *= fac;
               qkm1 *= fac;
             }
             while(any(t > eps(as(x))));
             return  add[x < maxlog(as(x))](zero(as(x)), ans*exp(-x));

           };
           T xx = if_else(xlt1, T(2), x);
           notdone = last_interval(br_xge1, notdone, r, n, xx);
         }
       }
     }
     return r;
   }
   else
     return apply_over(exp_int, n, x);
  }
}
