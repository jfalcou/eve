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
#include <eve/traits/common_value.hpp>

#include <concepts>
#include <iterator>

#include <initializer_list>

namespace eve::detail
{
//================================================================================================
//== Horner variadic
//================================================================================================

// This commented implementation will be used later to implement right quaternion or octonion polynomial evaluation
// when multiple decorators will be allowed
//
// template<decorator D, value T0, value... Cs>
// EVE_FORCEINLINE constexpr auto
// horner_impl(D const& d, T0 const& xx, Cs... cs) noexcept
// -> common_value_t<T0, Cs...>
// {
//   using r_t          = common_value_t<T0, Cs...>;
//   constexpr size_t N = sizeof...(Cs);
//   if constexpr( N == 0 ) return r_t(0);
//   else if constexpr( N == 1 ) return (r_t(cs), ...);
//   else if constexpr( N == 2 ) return d(fma)(r_t(xx), r_t(cs)...);
//   else
//   {
//     auto x    = r_t(xx);
//     auto dfma = d(fma);
//     r_t  that(zero(as<r_t>()));
//     auto next = [&](auto that, auto arg) { return dfma(x, that, arg); };
//     ((that = next(that, cs)), ...);
//     return that;
//   }
// }

// This  implementation is used for left-polynomial evaluation (even for quaternion or octonion)
//

  template<decorator D, value T0, value... Cs>
  EVE_FORCEINLINE constexpr auto
  horner_impl(D const& d, T0 const& xx, Cs... cs) noexcept
  -> common_value_t<T0, Cs...>
  {
    using r_t          = common_value_t<T0, Cs...>;
    constexpr size_t N = sizeof...(Cs);
    if constexpr( N == 0 ) return r_t(0);
    else if constexpr( N == 1 ) return (r_t(cs), ...);
    else
    {
      auto x    = r_t(xx);
      auto dfma = d(fma);
      r_t  that(zero(as<r_t>()));
      auto next = [&](auto that, auto arg) { return dfma(that, x, arg); };
      ((that = next(that, cs)), ...);
      return that;
    }
  }


//================================================================================================
//== Horner with ranges
//================================================================================================
  template<decorator D, value T0, range R>
  EVE_FORCEINLINE constexpr auto
  horner_impl(D const& d, T0 xx, R const& r) noexcept
  -> common_value_t<T0, typename R::value_type>
  {
    using r_t = common_value_t<T0, typename R::value_type>;
    auto x    = r_t(xx);
    auto cur  = std::begin(r);
    auto last = std::end(r);
    if( last == cur ) return r_t(0);
    else if( std::distance(cur, last) == 1 ) return r_t(*cur);
    else
    {
      using std::advance;
      auto dfma = d(fma);
      auto that = r_t(*cur);
      auto step = [&](auto that, auto arg) { return dfma(x, that, arg); };
      for( advance(cur, 1); cur != last; advance(cur, 1) ) that = step(that, *cur);
      return that;
    }
  }

  template<value T0, range R>
  EVE_FORCEINLINE constexpr auto
  horner_impl(compensated_type const&, T0 xx, R const& r) noexcept
  -> common_value_t<T0, typename R::value_type>
  {
    using r_t = common_value_t<T0, typename R::value_type>;
    auto x    = r_t(xx);
    auto cur  = std::begin(r);
    auto last = std::end(r);
    if( last == cur ) return r_t(0);
    else if( std::distance(cur, last) == 1 ) return r_t(*cur);
    else
    {
      using std::advance;
      auto that {r_t(*cur)};
      auto err {zero(as<r_t>())};
      auto step = [&x, &that, &err](auto arg)
        {
          auto [pi, epi] = two_prod(x, that);
          auto [th, si]  = two_add(pi, arg);
          that           = th;
          err            = fma(err, x, epi + si);
        };
      for( advance(cur, 1); cur != last; advance(cur, 1) ) step(r_t(*cur));
      return that + err;
    }
  }

}
