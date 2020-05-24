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

#include <eve/detail/concepts.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/slice.hpp>

namespace eve::detail
{
  template<scalar_value T, integral_scalar_value I, typename N, typename X, typename Y>
  EVE_FORCEINLINE auto
  lookup_(EVE_SUPPORTS(cpu_), wide<T, N, X> const &a, wide<I, N, Y> const &ind) noexcept
  {
    auto const cond = [&]()
    {
      if constexpr( std::is_signed_v<I> ) return ind >= 0;
      else                                return ind < N::value;
    }();

    // Compute mask as SIMD
    auto  idx  = cond.bits();
          idx &= ind;
    auto  msk  = cond.mask();

    // Rebuild as scalar
    wide<T, N, X> data;
    apply<N::value>([&](auto... v) { ((data[v] = a[idx[v]]),...); });

    // Apply mask as SIMD
    data &= msk;
    return data;
  }

  template<scalar_value T, integral_scalar_value I, typename N, typename X>
  EVE_FORCEINLINE auto
  lookup_(EVE_SUPPORTS(cpu_), wide<T, N, X> const &a, wide<I, N, aggregated_> const &ind) noexcept
  {
    auto const cond = [&]()
    {
      if constexpr( std::is_signed_v<I> ) return ind >= 0;
      else                                return ind < N::value;
    }();

    // Compute mask as SIMD
    auto  idx  = cond.bits();
          idx &= ind;
    auto  msk  = cond.mask();

    // Rebuild as scalar
    wide<T, N, X> data;

    constexpr auto const half = N::value / 2;
    apply<half>([&, lx = idx.slice(lower_)](auto... v) { ((data[v]      = a[lx[v]]),...); } );
    apply<half>([&, hx = idx.slice(upper_)](auto... v) { ((data[v+half] = a[hx[v]]),...); } );

    // Apply mask as SIMD
    data &= msk;
    return data;
  }
}

#endif
