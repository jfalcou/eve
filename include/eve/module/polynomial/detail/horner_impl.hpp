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
#include <eve/traits/common_value.hpp>

#include <concepts>
#include <iterator>

#include <initializer_list>
#include <iostream>

namespace eve::detail
{
//================================================================================================
//== Horner variadic
//================================================================================================
template<decorator D, value T0, value... Cs>
EVE_FORCEINLINE constexpr auto
horner_impl(D const& d, T0 const& xx, Cs... cs) noexcept
-> common_value_t<T0, Cs...>
{
  using r_t          = common_value_t<T0, Cs...>;
  constexpr size_t N = sizeof...(Cs);
  if constexpr( N == 0 ) return r_t(0);
  else if constexpr( N == 1 ) return (r_t(cs), ...);
  else if constexpr( N == 2 ) return d(fma)(r_t(xx), r_t(cs)...);
  else
  {
    auto x    = r_t(xx);
    auto dfma = d(fma);
    r_t  that(zero(as<r_t>()));
    auto next = [&](auto that, auto arg) { return dfma(x, that, arg); };
    ((that = next(that, cs)), ...);
    return that;
  }
}

}
