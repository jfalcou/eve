//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/product_type.hpp>
#include <eve/function/deinterleave_groups_shuffle.hpp>

namespace eve::detail
{
  template<std::ptrdiff_t G, simd_value T, std::same_as<T>... Ts>
  EVE_FORCEINLINE
  kumi::tuple<T, Ts...>
  deinterleave_groups_(EVE_SUPPORTS(cpu_), eve::fixed<G> g, T v0, Ts... vs) noexcept
    requires (( T::size() * (sizeof...(Ts) + 1)) >= G)
  {
    auto const values = kumi::make_tuple(v0,vs...);

         if constexpr ( sizeof...(Ts) == 0 ) return {deinterleave_groups_shuffle(v0, g)};
    else if constexpr ( sizeof...(Ts) == 1 )
    {
      auto [l, h] = deinterleave_groups_shuffle(v0, get<1>(values), g).slice();
      return {l, h};
    }
  }
}
