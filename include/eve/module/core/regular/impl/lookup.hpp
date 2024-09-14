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

namespace eve::detail
{
  template<callable_options O, typename T, typename I, typename N>
  EVE_FORCEINLINE logical<wide<T,N>> lookup_(EVE_REQUIRES(cpu_), O const&, logical<wide<T,N>> a, wide<I,N> i) noexcept
  {
    if constexpr(abi_t<T, N>::is_wide_logical) return bit_cast(lookup(a.bits(), i), as(a));
    else                                       return to_logical(lookup(a.mask(), i));
  }

  template<callable_options O, typename T, integral_scalar_value I, typename N>
  EVE_FORCEINLINE wide<T,N> lookup_(EVE_REQUIRES(cpu_), O const&, wide<T,N> const& a, wide<I,N> const& ind) noexcept
  {
    if constexpr( is_bundle_v<abi_t<T, N>> )
    {
      return wide<T, N>(kumi::map([=]<typename M>(M m) { return lookup(m, ind); }, a));
    }
    else
    {
      logical<wide<I,N>> const cond = [&]()
      {
        if constexpr( std::is_signed_v<I> ) return ind >= 0; else return ind < N::value;
      }();

      // Compute mask as SIMD
      auto idx = cond.bits();
      idx     &= ind;

      // Rebuild as scalar
      wide<T, N> data(0);

      if constexpr(has_aggregated_abi_v<wide<T,N>>)
      {
        constexpr auto const half = N::value / 2;
        apply<half>([&, lx = idx.slice(lower_)](auto... v)
                    { (data.set(v, (cond.get(v) ? a.get(lx.get(v)) : T {})), ...); });
        apply<half>([&, hx = idx.slice(upper_)](auto... v)
                    { (data.set(v + half, (cond.get(v) ? a.get(hx.get(v)) : T {})), ...); });
      }
      else
      {
        apply<N::value>([&](auto... v) { (data.set(v, cond.get(v) ? a.get(idx.get(v)) : T {}), ...); });
      }

      return data;
    }
  }
}
