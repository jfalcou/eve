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
#include <eve/detail/function/slice.hpp>

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

      return apply<N::value>([&](auto... v) { return type(a[idx[v]]...); }) & cond.mask();
    }
    else
    {
      auto cond = ind < N::value;
      auto idx  = cond.bits();
      idx &= ind;

      return apply<N::value>([&](auto... v) { return type(a[idx[v]]...); }) & cond.mask();
    }
  }

  template<scalar_value T, integral_scalar_value I, typename N, typename X>
  EVE_FORCEINLINE auto
  lookup_(EVE_SUPPORTS(cpu_), wide<T, N, X> const &a, wide<I, N, aggregated_> const &ind) noexcept
  {
    using type = wide<T, N, X>;

    if constexpr( std::is_signed_v<I> )
    {
      auto cond = ind >= 0;
      auto idx  = cond.bits();
      idx &= ind;

      using htype = wide<T, typename N::split_type>;

      auto la = apply<N::value / 2>([&, lx = idx.slice(lower_)](auto... v) { return htype(a[lx[v]]...); });
      auto ha = apply<N::value / 2>([&, hx = idx.slice(upper_)](auto... v) { return htype(a[hx[v]]...); });

      return type {la, ha} & cond.mask();
    }
    else
    {
      auto cond = ind < N::value;
      auto idx  = cond.bits();
      idx &= ind;

      using htype = wide<T, typename N::split_type>;

      auto la = apply<N::value / 2>([&, lx = idx.slice(lower_)](auto... v) { return htype(a[lx[v]]...); });
      auto ha = apply<N::value / 2>([&, hx = idx.slice(upper_)](auto... v) { return htype(a[hx[v]]...); });

      return type {la, ha} & cond.mask();
    }
  }
}

#endif
