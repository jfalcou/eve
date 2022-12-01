//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/concept/range.hpp>
#include <eve/module/core.hpp>
#include <eve/module/polynomial/numeric/horner.hpp>
#include <eve/module/polynomial/pedantic/horner.hpp>
#include <eve/module/polynomial/regular/horner.hpp>
#include <eve/traits/common_value.hpp>

#include <concepts>
#include <iterator>

#include <initializer_list>

namespace eve::detail
{

template<decorator D, floating_value T0, value C0, value... Cs>
EVE_FORCEINLINE constexpr auto
reverse_horner_impl(D const& d, T0 xx, C0 c0, Cs... cs) noexcept
-> decltype(horner(xx, c0, cs...))
{
  if constexpr((scalar_value<C0> && ... && scalar_value<Cs>))
  {
    using e_t =  element_type_t<T0>;
    std::array<e_t, sizeof...(cs)+1> c {e_t(c0), e_t(cs)...};
     return d(reverse_horner)(xx, c);
  }
  else
  {
    using r_t                         = common_value_t<T0, C0, Cs...>;
    auto                           x = r_t(xx);
    std::array<r_t, sizeof...(cs)+1> c {r_t{c0}, r_t{cs}...};
    return d(reverse_horner)(x, c);
  }
}

//================================================================================================
//== Reverse_Horner with ranges
//================================================================================================
template<decorator D, value T0, range R>
EVE_FORCEINLINE constexpr auto
reverse_horner_impl(D const& d, T0 xx, R const& r) noexcept
-> common_value_t<T0, typename R::value_type>
{
  using r_t  = common_value_t<T0, typename R::value_type>;
  auto x     = r_t(xx);
  auto cur   = std::rbegin(r);
  auto first = std::rend(r);
  if( first == cur ) return r_t(0);
  else if( std::distance(cur, first) == 1 ) return r_t(*cur);
  else
  {
    auto dfma = d(fma);
    auto that = r_t(0);
    auto step = [&](auto that, auto arg) { return dfma(x, that, arg); };
    for(; cur != first; ++cur ) that = step(that, *cur);
    return that;
  }
}
}
