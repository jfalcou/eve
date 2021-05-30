//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/concepts.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/slice.hpp>

namespace eve::detail
{
  template<scalar_value T, integral_scalar_value I, typename N>
  EVE_FORCEINLINE auto
  lookup_(EVE_SUPPORTS(cpu_), wide<T, N> const &a, wide<I, N> const &ind) noexcept
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
    wide<T, N> data;
    apply<N::value>([&](auto... v) { (data.set(v,a.get(idx.get(v))),...); });

    // Apply mask as SIMD
    data &= msk;
    return data;
  }

  template<scalar_value T, integral_scalar_value I, typename N>
  EVE_FORCEINLINE auto
  lookup_(EVE_SUPPORTS(cpu_), logical<wide<T, N>> const &a, wide<I, N> const &ind) noexcept
  {
    return bit_cast(lookup(a.bits(),ind), as(a));
  }

  template<scalar_value T, integral_scalar_value I, typename N>
  EVE_FORCEINLINE auto
  lookup_(EVE_SUPPORTS(cpu_), wide<T, N> const &a, wide<I, N> const &ind) noexcept
    requires std::same_as<abi_t<I, N>, aggregated_>
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
    wide<T, N> data;

    constexpr auto const half = N::value / 2;
    apply<half>([&, lx = idx.slice(lower_)](auto... v) { (data.set(v     , a.get(lx.get(v))),...); } );
    apply<half>([&, hx = idx.slice(upper_)](auto... v) { (data.set(v+half, a.get(hx.get(v))),...); } );

    // Apply mask as SIMD
    data &= msk;
    return data;
  }
}
