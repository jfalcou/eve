//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/meta.hpp>

namespace eve::detail
{
  template <typename N>
  EVE_FORCEINLINE constexpr N set_lower_n_bits(std::ptrdiff_t n)
  {
    using uint_res = make_integer_t<sizeof(N), unsigned>;

    if constexpr (std::same_as<std::uint64_t, uint_res>) {
      if (n == 64) return { static_cast<std::uint64_t>(-1) };
    }

    std::uint64_t res{1};
    res <<= n;
    res -= 1;
    return { static_cast<uint_res>(res) };
  }
}
