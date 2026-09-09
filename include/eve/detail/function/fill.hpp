//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/traits/width.hpp>
#include <eve/forward.hpp>
#include <eve/arch.hpp>

namespace eve::_
{
  template<typename Pack, eve::invocable<width_type, width_type> Generator>
  EVE_FORCEINLINE Pack fill(eve::as<Pack>, Generator&& g) noexcept
  {
    // MSVC emits a spurious error trying to interpret the Pack construction as an
    // initializer_list when it should not. We then manually split the two cases.
    if constexpr(width_v<Pack> > 1)
    {
      return  [&g]<width_type... N>(std::integer_sequence<width_type,N...>)
              {
                return Pack( g(N,width_v<Pack>)... );
              }( std::make_integer_sequence<width_type, width_v<Pack>>{});
    }
    else
    {
      if constexpr(logical_value<Pack>) return Pack( static_cast<bool>(g(0,1)) );
      else                              return Pack( g(0,1) );
    }
  }

  template<typename Pack, eve::invocable<width_type> Generator>
  EVE_FORCEINLINE Pack fill(eve::as<Pack>, Generator&& g) noexcept
  {
    // MSVC emits a spurious error trying to interpret the Pack construction as an
    // initializer_list when it should not. We then manually split the two cases.
    if constexpr(width_v<Pack> > 1)
    {
      return  [&g]<width_type... N>(std::integer_sequence<width_type,N...>)
              {
                return Pack( g(N)... );
              }( std::make_integer_sequence<width_type, width_v<Pack>>{});
    }
    else
    {
      if constexpr(logical_value<Pack>) return Pack( static_cast<bool>(g(0)) );
      else                              return Pack( g(0) );
    }
  }
}
