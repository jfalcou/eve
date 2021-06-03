//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/function/simd/lookup_helpers.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/implementation.hpp>
#include <cstddef>

namespace eve::detail
{
  template<typename T, typename I, typename N>
  EVE_FORCEINLINE wide<T, N>
  lookup_(EVE_SUPPORTS(ssse3_), wide<T, N> a, wide<I, N> idx) noexcept
    requires std::same_as<abi_t<T, N>, x86_128_>
  {
    using t8_t = typename wide<T, N>::template rebind<std::uint8_t, fixed<16>>;
    auto const b= bit_cast(a, as<t8_t>());

    if constexpr( sizeof(I) == 1 && sizeof(T) == 1 )
    {
      return bit_cast( t8_t(_mm_shuffle_epi8(b, idx)), as(a) );
    }
    else
    {
      t8_t i1 = _mm_shuffle_epi8( idx << shift<T>, t8_t {repeater<T,I>});
           i1 = bit_cast(bit_cast(i1, as<wide<as_integer_t<T>, N>>()) + offset<T>, as<t8_t>());
      return bit_cast(_mm_shuffle_epi8(b, i1), as(a));
    }
  }
}
