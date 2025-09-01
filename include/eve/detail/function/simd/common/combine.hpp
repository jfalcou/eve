//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/concept/combinable.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  struct local_combiner
  {
    EVE_FORCEINLINE auto operator()(auto... v) -> decltype(auto)
    {
      return combine(current_api, v...);
    }
  };

  template<typename T, typename N>
  EVE_FORCEINLINE auto
  combine(cpu_ const &, wide<T, N> const &l, wide<T, N> const &h) noexcept
  {
    using that_t = wide<T, typename N::combined_type>;

    if constexpr( is_emulated_v<abi_t<T, N>> )
    {
      return apply<N::value>([&](auto... I) { return that_t {l.get(I)..., h.get(I)...}; });
    }
    else if constexpr( has_aggregated_abi_v<that_t> )
    {
      that_t that;
      that.storage().assign_parts(translate(l), translate(h));
      return that;
    }
    else if constexpr( is_bundle_v<abi_t<T, N>> )
    {
      return that_t ( kumi::map ( local_combiner{}, l.storage(), h.storage() ) );
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto
  combine(cpu_ const &, logical<wide<T, N>> const &l, logical<wide<T, N>> const &h) noexcept
  {
    using that_t = logical<wide<T, typename N::combined_type>>;

    if constexpr( is_emulated_v<abi_t<T, N>> )
    {
      return apply<N::value>([&](auto... I) { return that_t {l.get(I)..., h.get(I)...}; });
    }
    else if constexpr( has_aggregated_abi_v<that_t> )
    {
      that_t that;
      that.storage().assign_parts(translate(l), translate(h));
      return that;
    }
    else
    {
      wide<T, typename N::combined_type> cb(l.mask(),h.mask());
      return bit_cast(cb, as<that_t>());
    }
  }

  template<simd_value W0, simd_value W1, simd_value W2, simd_value... Ws>
  EVE_FORCEINLINE auto combine(cpu_, W0 w0, W1 w1, W2 w2, Ws... ws) noexcept
    requires (combinable<W0, W1, W2, Ws...>)
  {
    auto [ f, s ] = kumi::split(kumi::tuple{w0, w1, w2, ws...}, kumi::index<(sizeof...(Ws) + 3) / 2>);
    return combine(current_api, kumi::apply(local_combiner{}, f), kumi::apply(local_combiner{}, s));
  }
}
