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
#include <eve/pattern.hpp>

namespace eve::detail
{
  template< typename T, typename N, ppc_abi ABI
          , std::ptrdiff_t I0, std::ptrdiff_t... Is
          >
  EVE_FORCEINLINE auto swizzle_pattern( vmx_ const&, wide<T,N,ABI> const& v
                                      , pattern_t<I0, Is...> const&       p
                                      )
  {
    constexpr auto sz = pattern_t<I0, Is...>::size(N::value);
    using that_t      = as_wide_t<wide<T,N,ABI>,fixed<sz>>;

    constexpr pattern_t<I0, Is...> q{};

    // PPC broadcast is optimizable
    if constexpr( ((Is == I0) && ...) )
    {
      return that_t{vec_splat(v.storage(),I0)};
    }
    // Try common patterns then
    else if constexpr( !std::same_as<void, decltype(swizzle_pattern(cpu_{},v,q))> )
    {
      return swizzle_pattern(cpu_{},v,q);
    }
    // If all pattern fails, we return void to signify we need to do a proper swizzle
  }
}
