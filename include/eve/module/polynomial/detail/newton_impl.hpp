//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/range.hpp>
#include <eve/module/core.hpp>

#include <concepts>
#include <iterator>

#include <initializer_list>

namespace eve::detail
{
//================================================================================================
//== Newton with iterators
//================================================================================================
template<decorator D, value T0, std::input_iterator IT1, std::input_iterator IT2>
EVE_FORCEINLINE constexpr auto
newton_impl(D const& d, T0 xx, IT1 const& firstc, IT1 const& lastc, IT2 const& firstn) noexcept
{
  using r_t = common_compatible_t<T0,
                                  typename std::iterator_traits<IT1>::value_type,
                                  typename std::iterator_traits<IT2>::value_type>;
  auto x    = r_t(xx);
  if( firstc == lastc ) return r_t(0);
  if( std::distance(firstc, lastc) == 1 ) return r_t(*firstc);
  else
  {
    using std::advance;
    auto curc = firstc;
    auto curn = firstn;
    advance(curc, 1);
    advance(curn, 1);
    auto dfma = d(fma);
    r_t  that(dfma(*firstc, sub(x, *firstn), *curc));
    auto step = [&](auto that, auto argc, auto argn) { return dfma(that, sub(x, argn), argc); };
    for( advance(curc, 1); curc != lastc; advance(curc, 1), advance(curn, 1) )
      that = step(that, *curc, *curn);
    return that;
  }
}

//================================================================================================
//== Newton with ranges
//================================================================================================
template<decorator D, value T0, range R1, range R2>
EVE_FORCEINLINE constexpr auto
newton_impl(D const& d, T0 xx, R1 const& rc, R2 rn) noexcept
{
  using r_t   = decltype(xx+ (typename R1::value_type)(0)+(typename R2::value_type)(0));
  auto x      = r_t(xx);
  auto firstc = begin(rc);
  auto lastc  = end(rc);
  if( firstc == lastc ) return r_t(0);
  else
  {
    auto siz = std::distance(firstc, lastc);
    EVE_ASSERT(siz == inc(std::distance(begin(rn), end(rn))),
               "number of nodes must equal to the number of coefficients minus 1");
    if( siz == 1 ) return r_t(*firstc);
    else
    {
      using std::advance;
      auto firstn = begin(rn);
      auto curn   = firstn;
      auto curc   = firstc;
      advance(curc, 1);
      advance(curn, 1);
      auto dfma = d(fma);
      r_t  that(dfma(*firstc, sub(x, *firstn), *curc));
      auto step = [&](auto that, auto argc, auto argn) { return dfma( that, sub(x, argn), argc); };
      for( advance(curc, 1); curc != lastc; advance(curc, 1), advance(curn, 1) )
        that = step(that, *curc, *curn);
      return that;
    }
  }
}
}
