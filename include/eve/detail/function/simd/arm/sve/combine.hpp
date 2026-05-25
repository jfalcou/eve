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
#include <eve/module/core/constant/iota.hpp>

namespace eve::_
{
  template<typename T, auto N>
  EVE_FORCEINLINE wide<T, N * 2>
  combine(sve_ const &, wide<T, N> const &l, wide<T, N> const &h) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    using that_t = wide<T, N * 2>;

    if constexpr( N == expected_cardinal_v<T> )
    {
      that_t that;
      that.storage().assign_parts(l,h);
      return that;
    }
    else
    {
      auto const maps = iota(as<wide<as_integer_t<T>,N>>{}) < N;
      return svsplice(maps,l,h);
    }
  }

  template<typename T, auto N>
  EVE_FORCEINLINE logical<wide<T, N * 2>>
  combine(sve_ const &, logical<wide<T, N>> const &l, logical<wide<T, N>> const &h) noexcept
  requires sve_abi<abi_t<T, N>>
  {
   using that_t = logical<wide<T, N * 2>>;

    if constexpr( N == expected_cardinal_v<T> )
    {
      that_t that;
      that.storage().assign_parts(l,h);
      return that;
    }
    else
    {
      return to_logical(combine(current_api, l.mask(),h.mask()));
    }
  }
}
