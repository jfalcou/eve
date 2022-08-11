//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/module/core/detail/basic_shuffle.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
template<real_scalar_value T, typename N, std::ptrdiff_t G>
    EVE_FORCEINLINE wide<T, N>
                    swap_adjacent_groups_(EVE_SUPPORTS(vmx_), wide<T, N> v, fixed<G>) noexcept
    requires(G <= N::value)
    && ppc_abi<abi_t<T, N>>
{
  if constexpr( G == N::value ) { return v; }
  else
  {
    /// TODO: Maybe there's better than just vec_perm ??
    return basic_shuffle(v, swap_adjacent_groups_pattern<G, N::value>);
  }
}
}
