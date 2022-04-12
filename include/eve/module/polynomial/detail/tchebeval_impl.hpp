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

namespace eve::detail
{
  //================================================================================================
  //== Tchebeval with range
  //================================================================================================
  template<decorator D, value T0, std::ranges::bidirectional_range R>
  EVE_FORCEINLINE constexpr common_compatible_t<T0, typename R::value_type>
  tchebeval_impl(D const & d, T0 xx, R const & r) noexcept
  {
    using r_t = common_compatible_t<T0, typename R::value_type>;
    auto x =  r_t(xx);
    auto first =  std::begin(r);
    auto cur  =  std::end(r);
    if (first == cur) return r_t(0);
    if (std::distance(first, cur) == 1) return r_t((*first)/2);
    else
    {
      --cur;
      auto dfma = d(fma);
      r_t b2 = zero(as<r_t>());
      r_t b1 = r_t(*cur--);
      for(; cur != first; --cur)
      {
        r_t tmp = dfma(x+x, b1, *cur-b2);
        b2 = b1;
        b1 = tmp;
      }
      return dfma(x, b1, fms(*cur, half(as<r_t>()), b2));
    }
  }

  //================================================================================================
  //== N+1 parameters
  //================================================================================================

  template<decorator D, value T0, value ...Cs>
  EVE_FORCEINLINE constexpr
  common_compatible_t<T0, Cs...>
  tchebeval_impl(D const & d, T0 x, Cs... cs) noexcept
  {
    constexpr size_t N = sizeof...(cs);
    //copy the coefficients to an array
    if constexpr (N == 0) return zero(as(x));
    else
    {
      using r_t = common_compatible_t<T0, Cs...>;
      std::array<r_t, N> c{r_t(cs)...};
      return tchebeval_impl(d, r_t(x), c);
    }
  }
}
