//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  combine(vmx_ const &, wide<T, N> const &l, wide<T, N> const &h) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    using that_t = wide<T, typename N::combined_type>;

    if constexpr( N::value * sizeof(T) == ppc_::bytes )
    {
      return typename that_t::storage_type {l, h};
    }
    else
    {
      auto mask = [&](auto... I) {
        __vector unsigned char m = {static_cast<std::uint8_t>(I)...,
                                    static_cast<std::uint8_t>(I + ppc_::bytes)...};
        return m;
      };

      return vec_perm(l.storage(), h.storage(), apply<(sizeof(T) * N::value)>(mask));
    }
  }
}
