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
#include <eve/detail/function/simd/common/swizzle_patterns.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  template<typename T, typename N, x86_abi ABI, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto swizzle_pattern(neon128_ const&, wide<T,N,ABI> const& v, Pattern const&)
  {
    constexpr auto sz = Pattern::size(N::value);
    //using that_t      = as_wide_t<wide<T,N,ABI>,fixed<sz>>;

    constexpr Pattern q{};

    // Try common patterns first
    if constexpr( !std::same_as<void, decltype(swizzle_pattern(cpu_{},v,q))> )
    {
      return swizzle_pattern(cpu_{},v,q);
    }

    // If all pattern fails, we return void to signify we need to do a proper swizzle
  }
}
