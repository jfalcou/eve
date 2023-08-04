//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/polynomial/detail/newton_impl.hpp>

namespace eve::detail
{
//================================================================================================
//== Newton with iterators
//================================================================================================

  template<value T0, std::input_iterator IT0, std::input_iterator IT1>
  EVE_FORCEINLINE constexpr auto
  newton_(EVE_SUPPORTS(cpu_), T0 xx, IT0 const& firstc, IT0 const& lastc, IT1 const& firstn) noexcept

  {
    return detail::newton_impl(regular_type(), xx, firstc, lastc, firstn);
  }

//================================================================================================
//== Newton with ranges
//================================================================================================
  template<value T0, range R1, range R2>
  EVE_FORCEINLINE constexpr auto
  newton_(EVE_SUPPORTS(cpu_), T0 xx, R1 const& rc, R2 const& rn) noexcept
  {
    return detail::newton_impl(regular_type(), xx, rc, rn);
  }

//================================================================================================
//== Newton with tuples
//================================================================================================
  template<value T0, value ...Coefs ,value... Nodes >
  EVE_FORCEINLINE constexpr auto
  newton_(EVE_SUPPORTS(cpu_), T0 xx,  kumi::tuple<Coefs...> const& cs
         , kumi::tuple<Nodes...> const& ns) noexcept
  {
    EVE_ASSERT((kumi::size_v<decltype(cs)> == 0 && kumi::size_v<decltype(ns)> == 0)||
               (kumi::size_v<decltype(cs)> ==  kumi::size_v<decltype(ns)>+1), "nodes andcoefs have incompatible sizes");
    using r1_t  = std::decay_t<decltype((xx+...+Coefs(0)))>;
    using r2_t  = std::decay_t<decltype((xx +...+Nodes(0)))>;
    using r_t   = decltype(r1_t{}+r2_t{});
    if constexpr(kumi::size_v<decltype(cs)> == 0)
    {
     return zero(as<r_t>());
    }
    else if constexpr(kumi::size_v<decltype(cs)> == 1)
    {
      return r_t(get<0>(cs));
    }
    else
    {
      r_t that = r_t(get<0>(cs));
      auto ans = kumi::zip(kumi::pop_front(cs), ns);
      auto compute = [&](auto ... args){
        auto doit = [&](auto an){
          auto [a, n] = an;
          that =  fma(that, xx-n, a);
        };
        ((doit(args), ...));
        return that;
      };
      return kumi::apply(compute, ans);
    }
  }

  template<decorator D, value T0, value ...Coefs ,value... Nodes>
  EVE_FORCEINLINE constexpr auto
  newton_(EVE_SUPPORTS(cpu_), D const& d, T0 xx,  kumi::tuple<Coefs...> const& cs
         , kumi::tuple<Nodes...> const& ns) noexcept
  {
    if constexpr(kumi::size_v<decltype(cs)> == 0)  return zero(as(xx));
    else
    {
      using r1_t  = std::decay_t<decltype((xx+...+Coefs(0)))>;
      using r2_t  = std::decay_t<decltype((xx +...+Nodes(0)))>;
      using r_t   = decltype(r1_t{}+r2_t{});
      if constexpr(kumi::size_v<decltype(cs)> == 1)
        return r_t(get<0>(cs));
      else
      {
        r_t that = r_t(get<0>(cs));
        auto ans = kumi::zip(kumi::pop_front(cs), ns);
        auto compute = [&](auto ... args){
          auto doit = [&](auto an){
            auto [a, n] = an;
            that =  d(fma)( that, xx-n, a);
          };
          ((doit(args), ...));
          return that;
        };
        return kumi::apply(compute, ans);
      }
    }
  }
}
