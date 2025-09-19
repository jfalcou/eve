//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/wide_forward.hpp>

namespace eve
{
  template<typename T0, typename... T>
  auto as_wides(T0 z, T... vs)
  {
    constexpr auto rem = (sizeof...(T)) % eve::wide<T0>::size();
    if constexpr(rem != 0)
    {
      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        auto z = [&](auto) { return zero; };
        return as_wides(z,vs..., z(N)...);
      }(std::make_index_sequence<eve::wide<T0>::size() - rem>());
    }
    else
    {
      return kumi::map( [](auto c)
                        {
                          return kumi::apply( [](auto... s) { return eve::wide<T0>{s...}; }, c);
                        }
                      , kumi::chunks<eve::wide<T0>::size()>(kumi::tie(vs...))
                      );
    }
  }
}
