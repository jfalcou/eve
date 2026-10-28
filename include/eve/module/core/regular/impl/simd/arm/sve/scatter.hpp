//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/unalign.hpp>

namespace eve::_
{
  template<typename T, width_type N, typename Idx, typename Ptr, callable_options O>
   void scatter_(EVE_REQUIRES(sve_), O const& opts, wide<T, N> const& v, Ptr ptr, Idx const& idx) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    using i_t = make_integer_t<sizeof(T)>;

    // Ignore All case : nothing to write
    if      constexpr( match_option<condition_key, O, ignore_all_> ) return;
    // SVE scatters 32 and 64-bit lanes only
    else if constexpr( sizeof(T) < 4 )                       scatter.behavior(cpu_{}, opts, v, ptr, idx);
    // A relative condition does not slice, so an aggregated wide goes through the generic cases
    else if constexpr( aggregated_abi<wide<T, N>> )          scatter.behavior(cpu_{}, opts, v, ptr, idx);
    // SVE scatter requires same size for index and values
    else if constexpr( sizeof(element_type_t<Idx>) != sizeof(T) ) scatter[opts](v, ptr, convert(idx, as<i_t>{}));
    else
    {
      auto m = expand_mask(opts[condition_key], as<wide<T, N>>{});
      svst1_scatter_index(m, unalign(ptr), idx, v);
    }
  }
}
