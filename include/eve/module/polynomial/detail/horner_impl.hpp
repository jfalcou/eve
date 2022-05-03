//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/concept/range.hpp>
#include <concepts>
#include <iterator>
#include <initializer_list>
#include <ranges>

namespace eve::detail
{
  //================================================================================================
  //== Horner variadic
  //================================================================================================
  template<decorator D, value T0, value ...Cs>
  EVE_FORCEINLINE constexpr
  auto horner_impl(D const & d, T0 const & xx, Cs... cs) noexcept
  {
    using r_t = common_compatible_t<T0, Cs...>;
    constexpr size_t N =  sizeof...(Cs);
    if constexpr(N == 0) return r_t(0);
    else if constexpr(N == 1) return (r_t(cs), ...);
    else if constexpr(N == 2) return d(fma)(r_t(xx), r_t(cs)...);
    else
    {
      auto x =  r_t(xx);
      auto dfma = d(fma);
      r_t that(zero(as<r_t>()));
      auto next = [&](auto that, auto arg){
        return dfma(x, that, arg);
      };
      ((that = next(that, cs)),...);
      return that;
    }
  }


  //================================================================================================
  //== Horner with ranges
  //================================================================================================
  template<decorator D, value T0, std::ranges::input_range R>
  EVE_FORCEINLINE constexpr auto horner_impl(D const & d, T0 xx, R const & r) noexcept
  requires (compatible_values<T0, typename R::value_type> && (!simd_value<R>))
  {
    using r_t = common_compatible_t<T0, typename R::value_type>;
    auto x =  r_t(xx);
    auto cur =  std::begin(r);
    auto last  =  std::end(r);
    if (last == cur) return r_t(0);
    else  if (std::distance(cur, last) == 1) return r_t(*cur);
    else
    {
      using std::advance;
      auto dfma = d(fma);
      auto that = r_t(*cur);
      auto step = [&](auto that, auto arg){
        return dfma(x, that, arg);
      };
      for (advance(cur, 1); cur != last; advance(cur, 1))
        that = step(that, *cur);
      return that;
    }
  }

  template<value T0, std::ranges::input_range R>
  EVE_FORCEINLINE constexpr auto horner_impl(comp_type const &, T0 xx, R const & r) noexcept
  requires (compatible_values<T0, typename R::value_type> && (!simd_value<R>))
  {
    using r_t = common_compatible_t<T0, typename R::value_type>;
    auto x =  r_t(xx);
    auto cur =  std::begin(r);
    auto last  =  std::end(r);
    if (last == cur) return r_t(0);
    else  if (std::distance(cur, last) == 1) return r_t(*cur);
    else
    {
      using std::advance;
      auto that{r_t(*cur)};
      auto err{zero(as < r_t>())};
      auto step = [&x, &that, &err](auto arg){
        auto [pi, epi] = two_prod(x, that);
        auto [th, si] = two_add(pi, arg);
        that = th;
        err = fma(err, x, epi+si);
      };
      for (advance(cur, 1); cur != last; advance(cur, 1))
        step(r_t(*cur));
      return that+err;
    }
  }

}
