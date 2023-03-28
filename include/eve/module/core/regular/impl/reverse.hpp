//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_swap.hpp>
#include <eve/module/core/regular/shuffle.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE T
  reverse_(EVE_SUPPORTS(cpu_), T const& v)
  {
    if constexpr( scalar_value<T> )
    {
      return v;
    }
    else if constexpr( has_aggregated_abi_v<T> )
    {
      auto [l, h] = v.slice();
      l           = eve::reverse(l);
      h           = eve::reverse(h);
      return T {h, l};
    }
    else if constexpr( has_bundle_abi_v<T> )
    {
      return T(kumi::map([](auto m) { return reverse(m); }, v));
    }
    else
    {
      return basic_shuffle(
        v, eve::fix_pattern<T::size()>([](int i, int size) { return size - i - 1; }));
    }
  }

  template<simd_value T, std::ptrdiff_t N>
  EVE_FORCEINLINE logical<T>
  reverse_(EVE_SUPPORTS(cpu_), logical<T> const                &v)
  {
    using abi_t = typename T::abi_type;
    if constexpr( abi_t::is_wide_logical )
    {
      // Reconstruct mask, reverse then turn to mask again
      auto const m   = v.mask();
      auto const res = eve::reverse(m);
      return to_logical(res);
    }
    else { return bit_cast(reverse(v.bits()), as(v)); }
  }

  template<value T, auto N>
  EVE_FORCEINLINE T
  reverse_(EVE_SUPPORTS(cpu_), T const& v, std::integral_constant<size_t, N>)
  {
    constexpr auto S   = cardinal_v<T>;
    if constexpr(scalar_value<T>) return v;
    else if constexpr( N == 0)   return v;
    else if constexpr( 2*N >= S) return reverse(v);
    else if constexpr( has_bundle_abi_v<T> )
    {
      return T(kumi::map([](auto m) { return reverse(m, m); }, v));
    }
    else
    {
      return shuffle(
        v, eve::fix_pattern<T::size()>( [](size_t i, int S) { return ((i < N)  ? S-i-1 : ( (i > S-N-1) ? S-i-1 : i)); }));
     }
  }

  template<value T,  auto N>
  EVE_FORCEINLINE logical<T>
  reverse_(EVE_SUPPORTS(cpu_), logical<T> const &v,  std::integral_constant<size_t, N> n)
  {
    using abi_t = typename T::abi_type;
    if constexpr( abi_t::is_wide_logical )
    {
      // Reconstruct mask, reverse then turn to mask again
      auto const m   = v.mask();
      auto const res = eve::reverse(m, n);
      return to_logical(res);
    }
    else { return bit_cast(bit_swap(v.bits(), n), as(v)); }
  }
}
