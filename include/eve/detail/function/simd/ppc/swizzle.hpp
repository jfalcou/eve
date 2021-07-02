//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/simd/common/swizzle_helpers.hpp>
#include <eve/forward.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  template<typename T, typename N, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto basic_swizzle_( EVE_SUPPORTS(vmx_), wide<T, N> const& v, Pattern const&)
    requires ppc_abi<abi_t<T, N>>
  {
    constexpr auto sz = Pattern::size();
    using that_t      = as_wide_t<wide<T, N>,fixed<sz>>;

    constexpr Pattern q = {};

    // We're swizzling so much we aggregate the output
    if constexpr( has_aggregated_abi_v<that_t> )
    {
      return aggregate_swizzle(v,q);
    }
    else
    {
      using bytes_t = typename that_t::template rebind<std::uint8_t,fixed<16>>;
      that_t that = vec_perm( v.storage(), v.storage()
                            , as_bytes<wide<T, N>>(q,as<bytes_t>()).storage()
                            );

      return process_zeros(that,q);
    }
  }
}
