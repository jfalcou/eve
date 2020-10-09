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

#include <eve/arch.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/forward.hpp>
#include <eve/traits/cardinal.hpp>

namespace eve::detail
{
  template<typename Generator, typename ABI, typename Pack>
  EVE_FORCEINLINE auto fill(eve::as_<Pack> const &, ABI const &, Generator g) noexcept
  {
    if constexpr( is_aggregated_v<ABI> )
    {
      Pack that;

      that.storage().apply([&]<typename... Sub>(Sub & ...v) {
        int k = 0;

        ((v = Sub([&](auto i, auto) { return g(i + k, Pack::static_size); }),
          k += Sub::static_size),
         ...);
      });

      return that;
    }
    else
    {
      static constexpr typename Pack::size_type sz = cardinal_v<Pack>;
      Pack                                      that;

      for( typename Pack::size_type i = 0; i < sz; ++i ) that.set(i, g(i, sz));

      return that;
    }
  }
}
