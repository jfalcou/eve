//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
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

      that.storage().segments[0] = l;
      that.storage().segments[1] = h;

      return that;
    }
    else if constexpr( is_bundle_v<abi_t<T, N>> )
    {
      return that_t ( kumi::map ( eve::combine, l.storage(), h.storage() ) );
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

      that.storage().segments[0] = l;
      that.storage().segments[1] = h;

      return that;
    }
    else
    {
      wide<T, typename N::combined_type> cb(l.mask(),h.mask());
      return bit_cast(cb, as<that_t>());
    }
  }
}
