//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>
#include <iostream>

namespace eve ::detail
{
  template<integral_scalar_value T, typename N>
  EVE_FORCEINLINE
  auto bit_reverse_(EVE_SUPPORTS(sse2_), wide<T, N> const &v) noexcept
  requires x86_abi<abi_t<T, N>> && (sizeof(T) == 1)
  {
    constexpr auto c = categorize<wide<T, N>>();
    using r_t = wide<T, N>;
    using N_8 = eve::fixed < N::value/8>;
    wide<std::uint64_t, N_8> a(0x8040201008040201);
          if constexpr(c == category::uint8x64  ) return r_t(_mm512_gf2p8affine_epi64_epi8(v, a, 0));
    else  if constexpr(c == category::uint8x32  ) return r_t(_mm256_gf2p8affine_epi64_epi8(v, a, 0));
    else  if constexpr(c == category::uint8x16  ) return r_t(_mm_gf2p8affine_epi64_epi8(v, a, 0));

  }
}
