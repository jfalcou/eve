//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, ppc_abi ABI, std::ptrdiff_t G>
  EVE_FORCEINLINE wide<T,N,ABI> swap_adjacent_groups_( EVE_SUPPORTS(cpu_)
                                                    , wide<T,N,ABI> v, fixed<G>
                                                    ) noexcept
  requires(G<=N::value)
  {
    if constexpr(G == N::value)
    {
      return v;
    }
    else
    {
      /// TODO: Maybe there's better than just vec_perm ??
      return basic_swizzle(v, swap_adjacent_groups_pattern<G,N::value> );
    }
  }
}
