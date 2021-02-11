//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018-2021 Joel FALCOU
  Copyright 2018-2021 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
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
  template<typename T, typename N, ppc_abi ABI, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto basic_swizzle_( EVE_SUPPORTS(vmx_), wide<T,N,ABI> const& v, Pattern const&)
  {
    constexpr auto sz = Pattern::size(N::value);
    using that_t      = as_wide_t<wide<T,N,ABI>,fixed<sz>>;

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
                            , as_bytes<wide<T,N,ABI>>(q,as_<bytes_t>()).storage()
                            );

      return process_zeros(that,q);
    }
  }
}
