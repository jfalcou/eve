//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/two_add.hpp>
#include <eve/module/core/regular/two_prod.hpp>

namespace eve::detail
{

  template<real_value T0, real_value U0, real_value T1, real_value U1, real_value ...Ts>
  auto sum_of_prod_(EVE_SUPPORTS(cpu_), T0 a0, U0 b0, T1 a1, U1 b1, Ts... args)
    requires (compatible_values<T0, Ts> && ...)
  {
    EVE_ASSERT(!((sizeof...(Ts))&1),"total number of parameters must be even");
    using r_t = common_compatible_t<T0,U0, T1, U1, Ts...>;
    auto sop = [](auto a, auto b, auto c,  auto d){
      auto mcd = -c * d;
      auto err = fma(c, d, mcd);
      auto dop = fms(a, b, mcd);
      return dop + err;
    };

    r_t that(sop(r_t(a0), r_t(b0), r_t(a1), r_t(b1)));
    if constexpr(sizeof...(Ts) == 0)
      return that;
    else
    {
      auto  b(false);
      r_t tmp;
      auto step = [&b, &tmp](auto it, auto arg){
        it = fam[b](it, tmp, r_t(arg));
        tmp =  r_t(arg);
        b = !b;
        return it;
      };
      ((that = step(that,args)),...);
      return that;
    }
  }

  template<real_value T0, real_value U0, real_value ...TUs>
  common_compatible_t<T0, U0, TUs...> sum_of_prod_(EVE_SUPPORTS(cpu_), pedantic_type const &
                                          , T0 t0, U0 u0, TUs... tus)
  {
    EVE_ASSERT(!((sizeof...(TUs))&1),"total number of parameters must be even");
    using r_t = common_compatible_t<T0, U0, TUs...>;
    if constexpr(sizeof...(TUs) == 0)
      return t0*u0;
    else
    {
      auto [t, e] = two_prod(r_t(t0), r_t(u0));
      r_t that = t;
      r_t err = e;
      auto  b(false);
      r_t tmp;
      auto step = [&b, &tmp, &err, &that](auto arg){
        if(b)
        {
          auto [p, ep] = two_prod(r_t(arg), tmp);
          auto [a, ea] = two_add(p, that);
          that = a;
          err += ep+ea;
        }
        else tmp =  r_t(arg);
        b = !b;
      };
      ((step(tus)),...);
      return that+err;
   }
  }

  template<std::ranges::input_range R1, std::ranges::input_range R2>
  common_compatible_t<typename R1::value_type, typename R2::value_type>
  sum_of_prod_(EVE_SUPPORTS(cpu_), R1 const & r1,  R2 const & r2)
  {

    EVE_ASSERT((distance(begin(r1), end(r1)) == distance(begin(r2), end(r2))),"ranges must share the same length");
    using r_t = common_compatible_t<typename R1::value_type, typename R2::value_type>;
    auto r1cur = begin(r1);
    auto r2cur = begin(r2);
    if(r1cur == end(r1)) return zero(as<r_t>());
    else if (distance(begin(r1), end(r1)) == 1) return r_t((*r1cur)*(r_t(*r2cur)));
    else
    {
      r_t that(0);
      for(; r1cur!= end(r1); ++r1cur, ++r2cur)
        that = fam(that, r_t(*r1cur), r_t(*r2cur));
      return that;
    }
  }

  template<std::ranges::input_range R1, std::ranges::input_range R2>
  common_compatible_t<typename R1::value_type, typename R2::value_type>
  sum_of_prod_(EVE_SUPPORTS(cpu_), pedantic_type const &, R1 const & r1,  R2 const & r2)
  {

    EVE_ASSERT((distance(begin(r1), end(r1)) == distance(begin(r2), end(r2))),"ranges must share the same length");
    using r_t = common_compatible_t<typename R1::value_type, typename R2::value_type>;
    auto r1cur = begin(r1);
    auto r2cur = begin(r2);
    if(r1cur == end(r1)) return zero(as<r_t>());
    else if (distance(begin(r1), end(r1)) == 1) return r_t((*r1cur)*(r_t(*r2cur)));
    else
    {
      r_t that(0);
      r_t err(0);
      for(; r1cur!= end(r1); ++r1cur, ++r2cur)
      {
        auto [p, ep] = two_prod(r_t(*r1cur), r_t(*r2cur));
        auto [a, ea] = two_add(p, that);
        that = a;
        err += ep+ea;
      }
      return that+err;
    }
  }
}
