//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/implementation.hpp>

#include <concepts>

namespace eve::detail
{
template<real_scalar_value T, integral_value I>
EVE_FORCEINLINE constexpr T
lookup_(EVE_SUPPORTS(cpu_), T const& a, I const& i)
{
  return (i == static_cast<I>(-1)) ? 0 : a;
}

template<typename T, integral_scalar_value I, typename N>
EVE_FORCEINLINE auto
lookup_(EVE_SUPPORTS(cpu_), wide<T, N> const& a, wide<I, N> const& ind) noexcept
{
  if constexpr( is_bundle_v<abi_t<T, N>> )
  {
    return wide<T, N>(kumi::map([=]<typename M>(M m) { return lookup(m, ind); }, a));
  }
  else
  {
    auto const cond = [&]()
    {
      if constexpr( std::is_signed_v<I> ) return ind >= 0;
      else return ind < N::value;
    }();

    // Compute mask as SIMD
    auto idx = cond.bits();
    idx &= ind;

    // Rebuild as scalar
    wide<T, N> data;
    apply<N::value>([&](auto... v) { (data.set(v, cond.get(v) ? a.get(idx.get(v)) : T {}), ...); });

    return data;
  }
}

template<scalar_value T, integral_scalar_value I, typename N>
EVE_FORCEINLINE auto
lookup_(EVE_SUPPORTS(cpu_), logical<wide<T, N>> const& a, wide<I, N> const& ind) noexcept
{
  return bit_cast(lookup(a.bits(), ind), as(a));
}

template<scalar_value T, integral_scalar_value I, typename N>
EVE_FORCEINLINE auto
lookup_(EVE_SUPPORTS(cpu_),
        wide<T, N> const& a,
        wide<I, N> const& ind) noexcept requires std::same_as<abi_t<I, N>, aggregated_>
{
  auto const cond = [&]()
  {
    if constexpr( std::is_signed_v<I> ) return ind >= 0;
    else return ind < N::value;
  }();

  // Compute mask as SIMD
  auto idx = cond.bits();
  idx &= ind;

  // Rebuild as scalar
  wide<T, N> data;

  constexpr auto const half = N::value / 2;
  apply<half>([&, lx = idx.slice(lower_)](auto... v)
              { (data.set(v, (cond.get(v) ? a.get(lx.get(v)) : T {})), ...); });
  apply<half>([&, hx = idx.slice(upper_)](auto... v)
              { (data.set(v + half, (cond.get(v) ? a.get(hx.get(v)) : T {})), ...); });

  return data;
}
}
