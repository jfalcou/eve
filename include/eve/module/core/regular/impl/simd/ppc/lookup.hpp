//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/detail/generic/lookup_helpers.hpp>

namespace eve::detail
{
template<typename T, typename I, typename N>
EVE_FORCEINLINE wide<T, N>
lookup_(EVE_SUPPORTS(vmx_), wide<T, N> a, wide<I, N> idx) noexcept requires ppc_abi<abi_t<T, N>>
{
  using type = wide<T, N>;
  using t8_t = typename type::template rebind<std::uint8_t, fixed<16>>;

  if constexpr( sizeof(I) == 1 && sizeof(T) == 1 )
  {
    return type {vec_perm(a.storage(), a.storage(), bit_cast(idx, as<t8_t>()).storage())};
  }
  else
  {
    using i_t = wide<as_integer_t<T>, N>;
    t8_t i1 = lookup(bit_cast(idx << shift<T>, as<t8_t>()), t8_t {repeater<T, I, false>});
    i1      = bit_cast(bit_cast(i1, as<i_t>()) + i_t{offset<T, false>, as<t8_t>()});

    return bit_cast(lookup(bit_cast(a, as<t8_t>()), i1), as(a));
  }
}
}
