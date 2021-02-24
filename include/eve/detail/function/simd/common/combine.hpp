//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto
  combine(cpu_ const &, wide<T, N, ABI> const &l, wide<T, N, ABI> const &h) noexcept
  {
    using that_t = wide<T, typename N::combined_type>;

    if constexpr( is_emulated_v<ABI> )
    {
      return apply<N::value>([&](auto... I) { return that_t {l.get(I)..., h.get(I)...}; });
    }
    else if constexpr( is_aggregated_v<ABI> )
    {
      that_t that;

      that.storage().segments[0] = l;
      that.storage().segments[1] = h;

      return that;
    }
  }

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto
  combine(cpu_ const &, logical<wide<T, N, ABI>> const &l, logical<wide<T, N, ABI>> const &h) noexcept
  {
    using that_t = logical<wide<T, typename N::combined_type>>;

    if constexpr( is_emulated_v<ABI> )
    {
      return apply<N::value>([&](auto... I) { return that_t {l.get(I)..., h.get(I)...}; });
    }
    else if constexpr( is_aggregated_v<ABI> )
    {
      that_t that;

      that.storage().segments[0] = l;
      that.storage().segments[1] = h;

      return that;
    }
    else
    {
      wide<T, typename N::combined_type> cb(l.mask(),h.mask());
      return bit_cast(cb, as_<that_t>());
    }
  }
}
