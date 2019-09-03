//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_ABI_CAST_HPP_INCLUDED
#define EVE_DETAIL_ABI_CAST_HPP_INCLUDED

#include <eve/concept/vectorized.hpp>
#include <type_traits>

namespace eve::detail
{
  // Cast to Target unless Origin is Vectorized
  template<typename Target, typename Origin>
  decltype(auto) abi_cast(Origin &&o)
  {
    if constexpr(is_vectorized_v<Origin>)
      return std::forward<Origin>(o);
    else
      return static_cast<Target>(o);
  }
}

#endif
