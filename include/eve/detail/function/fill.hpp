//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/forward.hpp>
#include <eve/arch.hpp>

namespace eve::detail
{
  template<typename Generator, typename Pack, std::ptrdiff_t... N>
  auto filler(eve::as<Pack>, Generator g, std::integer_sequence<std::ptrdiff_t,N...>) noexcept
  {
    return Pack{ g(N,cardinal_v<Pack>)... };
  }

  template<typename Generator, typename Pack>
  EVE_FORCEINLINE auto fill(eve::as<Pack> tgt, Generator g) noexcept
  {
    // MSVC emits a spurious error trying to interpret the Pack construction as an
    // initializer_list when it should not. We then manually split the two cases.
    if constexpr(cardinal_v<Pack> > 1)
    {
      return  filler(tgt,g,std::make_integer_sequence<std::ptrdiff_t,cardinal_v<Pack>>{});
    }
    else
    {
      return Pack( g(0,1) );
    }
  }
}
