//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/pedantic/lpnorm.hpp>
#include <eve/module/math/regular/pow_abs.hpp>

namespace eve::detail
{


  template<int N, real_value P, typename T0, typename T1, typename... Ts>
  auto lpnorm_(EVE_SUPPORTS(cpu_), diff_type<N>
            , P const & p, T0 arg0, T1 arg1, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0, T1, Ts...>;
    if constexpr(N > sizeof...(Ts)+3)
    {
      return zero(as<r_t >());
    }
    else if constexpr(integral_value<P>)
    {
      auto fp = floating_(p);
      return diff_type<N>()(lpnorm)(fp, arg0, arg1, args...);
    }
    else
    {
      if constexpr(N == 1) //p derivative
      {
        auto tmp = lpnorm(p, arg0, arg1, args...);
        auto tmp1= add(pow_abs(arg0, dec(p)), pow_abs(arg1, dec(p)), pow_abs(args, dec(p))...) ;
        auto tmp2= add(pow_abs(arg0, p), pow_abs(arg1, p), pow_abs(args, p)...) ;
        return (tmp/tmp2)*tmp1;
      }
      else
      {
        auto rp = r_t(p);
        auto tmp = lpnorm(p, arg0, arg1, args...);
        auto h = pow_abs(tmp, r_t(oneminus(p)));
        if constexpr(N==2)       return pow_abs(arg0, dec(rp))*h;
        else if constexpr(N==3)  return pow_abs(arg1, dec(rp))*h;
        else
        {
          auto getNth = []<std::size_t... I>(std::index_sequence<I...>, auto& that, auto... vs)
            {
              auto iff = [&that]<std::size_t J>(auto val, std::integral_constant<std::size_t,J>)
              {
                if constexpr(J==N) that = val;
              };

              ((iff(vs, std::integral_constant<std::size_t,I+3>{})),...);
            };
          r_t that(0);
          getNth(std::make_index_sequence<sizeof...(args)>{},that,args...);
          return pow_abs(that, dec(rp))*h;
        }
      }
    }
  }

  template<int N, real_value P, typename T0, typename T1, typename... Ts>
  auto lpnorm_(EVE_SUPPORTS(cpu_), decorated<diff_<N>(pedantic_)> const &, P const & p
             , T0 arg0, T1 arg1, Ts... args) noexcept
  {
    using r_t = common_compatible_t<T0,T1, Ts...>;
    if constexpr(N > sizeof...(Ts)+3)
    {
      return zero(as<r_t >());
    }
    else if constexpr(integral_value<P>)
    {
      auto fp = floating_(p);
      return decorated<diff_<N>(pedantic_)>()(lpnorm)(fp, arg0, arg1, args...);
    }
    else
    {
      if constexpr(N == 1) //p derivative
      {
        auto tmp = lpnorm(p, arg0, arg1, args...);
        auto tmp1= add(pow_abs(arg0, dec(p)), pow_abs(arg1, dec(p)), pow_abs(args, dec(p))...) ;
        auto tmp2= add(pow_abs(arg0, p), pow_abs(arg1, p), pow_abs(args, p)...) ;
        return (tmp/tmp2)*tmp1;
      }
      else
      {
        auto rp = r_t(p);
        auto tmp = pedantic(lpnorm)(p, arg0, arg1, args...);
        auto h =  pow_abs(tmp, r_t(oneminus(p)));
        if constexpr(N==2)       return pow_abs(arg0, dec(rp))*h;
        else if constexpr(N==3)  return pow_abs(arg1, dec(rp))*h;
        else
        {
          auto getNth = []<std::size_t... I>(std::index_sequence<I...>, auto& that, auto... vs)
            {
              auto iff = [&that]<std::size_t J>(auto val, std::integral_constant<std::size_t,J>)
              {
                if constexpr(J==N) that = val;
              };

              ((iff(vs, std::integral_constant<std::size_t,I+3>{})),...);
            };
          r_t that(0);
          getNth(std::make_index_sequence<sizeof...(args)>{},that,args...);
          return pow_abs(that, dec(rp))*h;
        }
      }
    }
  }

  template<int N, conditional_expr C, real_value P, real_value T0, real_value T1, real_value ...Ts>
  auto lpnorm_(EVE_SUPPORTS(cpu_), C const &cond, diff_type<N> const &
          , P const & p, T0 a0, T1 a1, Ts... args)
  requires floating_value<common_compatible_t<P, T0, T1, Ts...>>
  {
    return mask_op(  cond, eve::diff_nth<N>(eve::lpnorm), p, a0, a1, args...);
  }

}
