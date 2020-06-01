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

#include <eve/arch/limits.hpp>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  combine(vmx_ const &, wide<T, N, ppc_> const &l, wide<T, N, ppc_> const &h) noexcept
  {
    using that_t = wide<T, typename N::combined_type>;

    if constexpr( N::value * sizeof(T) == limits<eve::vmx_>::bytes )
    {
      return typename that_t::storage_type {l, h};
    }
    else
    {
      auto mask = [&](auto... I) {
        __vector unsigned char m = {static_cast<std::uint8_t>(I)...,
                                    static_cast<std::uint8_t>(I + limits<eve::vmx_>::bytes)...};
        return m;
      };

      return vec_perm(l.storage(), h.storage(), apply<(sizeof(T) * N::value)>(mask));
    }
  }
}

