//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/is_nez.hpp>

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE size_t nbtrue_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      return  v != 0;
    }
    else if constexpr(is_logical_v<T>)
    {
      if constexpr(has_aggregated_abi_v<T>)
      {
        auto [sl, sh] = v.slice();
        return nbtrue(sl) + nbtrue(sh);
      }
      else
      {
        std::size_t r = 0u;

        [&]<std::size_t... I>( std::index_sequence<I...> const& )
        {
          r = (r + ... + get<I>(v));
        }( std::make_index_sequence<cardinal_v<T>>{});

        return r;
      }
    }
    else
    {
      return nbtrue(is_nez(v));
    }
  }
}

