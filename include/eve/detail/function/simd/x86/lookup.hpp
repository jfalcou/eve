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

// TODO: fix operator<< in operators.hpp
#include <eve/function/shl.hpp>

namespace eve::detail
{
  template<typename T, typename I, typename N>
  EVE_FORCEINLINE wide<T, N, x86_128_>
                  lookup_(EVE_SUPPORTS(ssse3_), wide<T, N, x86_128_> a, wide<I, N, x86_128_> idx) noexcept
  {
    // TODO: We use sizeof as a discriminant but we could actually use shuffle
    // to extract the one byte for the lookup form bigger integer and put them inside
    // a proper wide<char> before indexing. This would make lookup usable with any
    // integer index on x86
    if constexpr( sizeof(I) == 1 )
    {
      return _mm_shuffle_epi8(a, idx);
    }
    else
    {
      using t8_t = typename wide<T, N, x86_128_>::template rebind<std::uint8_t, fixed<16>>;

      t8_t i1 = _mm_shuffle_epi8(shl(idx, shift<I>), t8_t {repeater<I>});
      i1      = bit_cast(bit_cast(i1, as<wide<I, N, x86_128_>>()) + offset<I>, as<t8_t>());

      t8_t const blocks = _mm_shuffle_epi8(bit_cast(a, as<t8_t>()), i1);
      return bit_cast(blocks, as(a));
    }
  }
}

