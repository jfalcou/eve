//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto slice(wide<T, N> const &a, Slice const &) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr( Slice::value )
    {
      auto select = [](auto const &v, auto size) {
        auto mask = [&](auto... I) {
          auto                   offset = (sizeof(T) * size) / 2;
          __vector unsigned char m      = {static_cast<std::uint8_t>(offset + I % offset)...};
          return m;
        };

        return vec_perm(v.storage(), v.storage(), apply<16>(mask));
      };

      return wide<T, typename N::split_type>(select(a, N {}));
    }
    else
    {
      return wide<T, typename N::split_type>(a.storage());
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto slice(wide<T, N> const &a) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    std::array<wide<T, typename N::split_type>, 2> that{slice(a, lower_), slice(a, upper_)};
    return that;
  }
}
