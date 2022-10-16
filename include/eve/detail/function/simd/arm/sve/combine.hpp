//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  combine(sve_ const &, wide<T, N> const &l, wide<T, N> const &h) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    using that_t = wide<T, typename N::combined_type>;

    if constexpr( N::value  == expected_cardinal_v<T> )
    {
      that_t that;

      that.storage().segments[0] = l;
      that.storage().segments[1] = h;

      return that;
    }
    else
    {
      logical<that_t> const maps = [&](auto i, auto) { return i < N::value; };
      return svsplice(maps,l,h);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto
  combine(sve_ const &, logical<wide<T, N>> const &l, logical<wide<T, N>> const &h) noexcept
  requires sve_abi<abi_t<T, N>>
  {
   using that_t = logical<wide<T, typename N::combined_type>>;

    if constexpr( N::value  == expected_cardinal_v<T> )
    {
      that_t that;

      that.storage().segments[0] = l;
      that.storage().segments[1] = h;

      return that;
    }
    else
    {
      return to_logical(eve::combine(l.mask(),h.mask()));
    }
  }
}
