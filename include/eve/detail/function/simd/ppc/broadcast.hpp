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

#include <eve/detail/abi.hpp>
#include <eve/pattern.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename N, ppc_abi ABI, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto broadcast_(EVE_SUPPORTS(vmx_), logical<wide<T,N,ABI>> v, Pattern) noexcept
  {
    constexpr auto sz = Pattern::size(cardinal_v<logical<wide<T,N,ABI>>>);
    using   that_t    = as_wide_t<logical<wide<T,N,ABI>>,fixed<sz>>;
    constexpr auto idx = Pattern{}(0,sz);

    return that_t{ vec_splat(v.storage(), idx ) };
  }

  template<typename T, typename N, ppc_abi ABI, shuffle_pattern Pattern>
  EVE_FORCEINLINE auto broadcast_(EVE_SUPPORTS(vmx_), wide<T,N,ABI> v, Pattern) noexcept
  {
    constexpr auto sz = Pattern::size(cardinal_v<wide<T,N,ABI>>);
    using   that_t    = as_wide_t<wide<T,N,ABI>,fixed<sz>>;
    constexpr auto idx = Pattern{}(0,sz);

    return that_t{ vec_splat(v.storage(), idx ) };
  }
}
