//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/forward.hpp>
#include <eve/arch.hpp>

namespace eve::detail
{
  template<typename Generator, typename Pack>
  EVE_FORCEINLINE auto fill(eve::as_<Pack> const &, Generator g) noexcept
  {
    if constexpr( has_aggregated_abi_v<Pack> )
    {
      Pack that;

      that.storage().apply
      (
        [&]<typename... Sub>(Sub&... v)
        {
          std::ptrdiff_t k = 0;

          ( ( v = Sub([&](auto i, auto) { return g(i + k, Pack::size()); })
            , k += Sub::size()
            )
          , ...
          );
        }
      );

      return that;
    }
    else
    {
      return  [&g]<std::ptrdiff_t... N>(std::integer_sequence<std::ptrdiff_t,N...>)
              {
                return Pack( g(N,cardinal_v<Pack>)... );
              }( std::make_integer_sequence<std::ptrdiff_t,cardinal_v<Pack>>{});
    }
  }
}
