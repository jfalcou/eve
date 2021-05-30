//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/function/simd/lookup_helpers.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>

namespace eve::detail
{
  template<typename T, typename I, typename N>
  EVE_FORCEINLINE auto
  lookup_(EVE_SUPPORTS(vmx_), wide<T, N> a, wide<I, N> idx) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;
    using t8_t = typename type::template rebind<std::uint8_t, fixed<16>>;

    if constexpr( sizeof(I) == 1 )
    {
      return type {vec_perm(a.storage(), a.storage(), bit_cast(idx, as<t8_t>()).storage())};
    }
    else
    {
      as_wide_t<as_integer_t<T, unsigned>, N> shf {shift<I>};

      t8_t i1 = lookup(bit_cast(vec_sl(idx.storage(), shf.storage()), as<t8_t>()),
                       t8_t {repeater<I, false>});

      i1 = bit_cast(bit_cast(i1, as<wide<I, N>>()) + offset<I, false>, as<t8_t>());

      return bit_cast(lookup(bit_cast(a, as<t8_t>()), i1), as(a));
    }
  }
}
