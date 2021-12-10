//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/eps.hpp>
#include <eve/function/all.hpp>
#include <eve/function/any.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/reverse_horner.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/fam.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_nlez.hpp>
#include <eve/function/is_ngez.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/log.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/nan.hpp>
#include <eve/detail/hz_device.hpp>
#include <array>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto lambert_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    using elt_t =  element_type_t<T>;
    auto halley = [](auto x, auto w_i,  auto max_iters)
      {
        auto w = w_i;
        for(int i=0; i<max_iters; i++) {
          T e = eve::exp(w);
          T p = inc(w);
          T t = fms(w, e, x);
          t /=  if_else(is_gtz(w), e*p, e*p - T(0.5)*inc(p)*t/p);
          w -= t;
          T tol = 10*eps(as(x))*eve::max(eve::abs(w), rec(eve::abs(p)*e));
          if(eve::all(eve::abs(t) < tol) )break;
        }
        return w;
      };


    if constexpr( has_native_abi_v<T> )
    {
      auto serie = [](auto , auto r){
        constexpr std::array < elt_t, 12> P = {
          -1.0,
          2.331643981597124203363536062168,
          -1.812187885639363490240191647568,
          1.936631114492359755363277457668,
          -2.353551201881614516821543561516,
          3.066858901050631912893148922704,
          -4.175335600258177138854984177460,
          5.858023729874774148815053846119,
          -8.401032217523977370984161688514,
          12.250753501314460424,
          -18.100697012472442755,
          27.029044799010561650
        };
        return reverse_horner(r, P);
      };
      T q = x+T(0.367879441171442);
      auto lambert0_small = [&serie, x](auto q){ //branch 0 q <= 1.0e-3
        return serie(x, eve::sqrt(q));
      };
      auto lambert0_other = [&halley](auto x, auto q){ // branch 0 q <= 1.0e'3
        auto p = eve::sqrt(T(5.436563656918090)*q);
        auto w1= dec(p*(inc(p*fam(T(-0.333333333333333), p, T(1.388888888888889e-02)))));
        auto w2= log(x);
        w2 -= if_else(x > 3, zero, log(w2));
        auto init =  if_else(x < one(as(x)), w1, w2);
        return halley(x, init, 10);
      };
      auto lambert1 = [&halley, &serie](auto x, auto q, auto positivex){ // branch 1 q > 0
        T r = -eve::sqrt(q);
        auto test = (x < T(-1.0e-6));
        T w1(0);
        if(eve::any(test)) w1 = serie(x, r);
        if(eve::all(test)&&eve::all(q < T(3.0e-3))) return w1;
        T l1 = log(-x);
        T l2 = log(-l1);
        T w2 = l1 - l2 + l2/l1;
        return if_else(is_eqz(x) && !positivex, minf(as(x)), halley(x, w2, 30));
      };

      auto r = nan(as<T>());            //nan case treated here
      r =  if_else(is_eqz(x), zero, r); //zero case treated here
      r =  if_else(x == inf(as(x)), x, r);
      auto notdone =  is_nlez(q)&&(q != inf(as(x)));
      if(eve::any(notdone))
      {
        notdone = next_interval(lambert0_small, notdone, q < T(1.0e-3), r, q);
        if(eve::any(notdone))
        {
          notdone = last_interval(lambert0_other, q >= T(1.0e-3), r, x, q);
        }
      }
      auto positivex = is_positive(x);
      if (eve::all(positivex)) return kumi::make_tuple(r, r);
      auto r1 = if_else(positivex, r, lambert1(x, q,  positivex));
      return  kumi::make_tuple(r, r1);
    }
    else
      return apply_over2(lambert, x);
  }
}
