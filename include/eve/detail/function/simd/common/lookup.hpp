//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_COMMON_LOOKUP_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_COMMON_LOOKUP_HPP_INCLUDED

#include <eve/concept/stdconcepts.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<scalar_value T, integral_scalar_value I, typename N, typename X, typename Y>
  EVE_FORCEINLINE auto
  lookup_(EVE_SUPPORTS(cpu_), wide<T, N, X> const &a, wide<I, N, Y> const &ind) noexcept
  {
    using type = wide<T, N, X>;

    if constexpr( std::is_signed_v<I> )
    {
      auto cond = ind >= 0;
      auto idx  = cond.bits();
      idx &= ind;

      if( is_aggregated_v<X> )
      {
        auto [la, ha] = a.slice();
        auto [lx, hx] = idx.slice();

        using htype = std::remove_cvref_t<decltype(la)>;

        la = apply<N::value / 2>([&](auto... v) { return htype(a[lx[v]]...); });
        ha = apply<N::value / 2>([&](auto... v) { return htype(a[hx[v]]...); });

        return type {la, ha} & cond.mask();
      }
      else
      {
        return apply<N::value>([&](auto... v) { return type(a[idx[v]]...); }) & cond.mask();
      }
    }
    else
    {
      auto cond = ind < N::value;
      auto idx  = cond.bits();
      idx &= ind;

      if( is_aggregated_v<X> )
      {
        auto [la, ha] = a.slice();
        auto [lx, hx] = idx.slice();

        using htype = std::remove_cvref_t<decltype(la)>;

        la = apply<N::value / 2>([&](auto... v) { return htype(a[lx[v]]...); });
        ha = apply<N::value / 2>([&](auto... v) { return htype(a[hx[v]]...); });

        return type {la, ha} & cond.mask();
      }
      else
      {
        return apply<N::value>([&](auto... v) { return type(a[idx[v]]...); }) & cond.mask();
      }
    }
  }
}

#endif
