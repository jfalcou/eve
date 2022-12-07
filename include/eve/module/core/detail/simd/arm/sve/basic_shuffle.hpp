//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/simd/common/swizzle_helpers.hpp>
#include <eve/forward.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
template<typename T, typename N, shuffle_pattern Pattern>
EVE_FORCEINLINE auto
basic_shuffle_(EVE_SUPPORTS(sve_),
               wide<T, N> const& v,
               Pattern const& p) requires sve_abi<abi_t<T, N>>
{
  constexpr auto sz = Pattern::size();
  using that_t      = as_wide_t<wide<T, N>, fixed<sz>>;

  // We're swizzling so much we aggregate the output
  if constexpr( has_aggregated_abi_v<that_t> ) { return aggregate_shuffler(v, p); }
  else
  {
    using idx_t = as_wide_t<wide<as_integer_t<T, unsigned>, N>, fixed<sz>>;
    return that_t{svtbl(v, as_indexes<idx_t>(p))};
  }
}
}
