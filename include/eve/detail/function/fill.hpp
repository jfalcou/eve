//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/forward.hpp>
#include <eve/arch.hpp>

namespace eve::detail
{
  template<typename Generator, typename Pack>
  EVE_FORCEINLINE auto fill(eve::as<Pack> const &, Generator g) noexcept
  {
    // MSVC emits a spurious error trying to interpret the Pack construction as an
    // initializer_list when it should not. We then manually split the two cases.
    if constexpr(cardinal_v<Pack> > 1)
    {
      return  [&g]<std::ptrdiff_t... N>(std::integer_sequence<std::ptrdiff_t,N...>)
              {
                return Pack( g(N,cardinal_v<Pack>)... );
              }( std::make_integer_sequence<std::ptrdiff_t,cardinal_v<Pack>>{});
    }
    else
    {
      return Pack( g(0,1) );
    }
  }
}
