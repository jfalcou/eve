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

#include <eve/detail/function/simd/lookup_helpers.hpp>
#include <eve/detail/implementation.hpp>

// TODO: fix operator<< in operators.hpp
#include <eve/function/shl.hpp>

// TODO: later std::bit_cast
#include <eve/function/bit_cast.hpp>

namespace eve::detail
{
  template<typename T, typename I, typename N>
  EVE_FORCEINLINE auto
  lookup_(EVE_SUPPORTS(neon128_), wide<T, N, neon64_> a, wide<I, N, neon64_> idx) noexcept
  {
    if constexpr( std::is_signed_v<I> )
    {
      using utype = wide<make_integer_t<sizeof(I), unsigned>, N>;
      return lookup(a, bit_cast(idx, as<utype>()));
    }
    else
    {
      using t8_t = typename wide<T, N, neon64_>::template rebind<std::uint8_t, fixed<8>>;

      if constexpr( sizeof(I) == 1 )
      {
        return bit_cast(t8_t(vtbl1_u8(bit_cast(a, as<t8_t>()), idx)), as(a));
      }
      else
      {
        t8_t i1 = lookup(bit_cast( eve::shl(idx, shift<I>), as(i1)), t8_t {repeater<I>});
        i1      = bit_cast(bit_cast(i1, as<wide<I, N, neon64_>>()) + offset<I>, as<t8_t>());
        return bit_cast(lookup(bit_cast(a, as<t8_t>()), i1), as(a));
      }
    }
  }

  template<typename T, typename I, typename N>
  EVE_FORCEINLINE auto
  lookup_(EVE_SUPPORTS(neon128_), wide<T, N, neon128_> a, wide<I, N, neon128_> idx) noexcept
  {
    if constexpr( std::is_signed_v<I> )
    {
      using utype = wide<make_integer_t<sizeof(I), unsigned>, N>;
      return lookup(a, bit_cast(idx, as<utype>()));
    }
    else
    {
      using t8_t = typename wide<T, N, neon128_>::template rebind<std::uint8_t, fixed<16>>;

      if constexpr( sizeof(I) == 1 )
      {
        using t8h_t = typename wide<T, N, neon128_>::template rebind<std::uint8_t, fixed<8>>;

        auto        pieces = bit_cast(a, as<t8_t>());
        uint8x8x2_t tbl    = {{pieces.slice(lower_), pieces.slice(upper_)}};
        auto        idxs   = idx.slice();

        return bit_cast(t8_t(t8h_t(vtbl2_u8(tbl, idxs[0])), t8h_t(vtbl2_u8(tbl, idxs[1]))), as(a));
      }
      else
      {
        t8_t i1 = lookup(bit_cast( eve::shl(idx, shift<I>), as(i1)), t8_t {repeater<I>});
        i1      = bit_cast(bit_cast(i1, as<wide<I, N, neon128_>>()) + offset<I>, as<t8_t>());
        return bit_cast(lookup(bit_cast(a, as<t8_t>()), i1), as(a));
      }
    }
  }
}

