//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE
  Copyright 2020 Denis YAROSHEVSKIY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#pragma once

#include <eve/arch/logical.hpp>

#include <utility>

namespace eve::detail
{
  // There is no usecase for aggregated - use top bits.
  // For emulated, N <= 64 is enforced in top bits.

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto movemask( eve::logical<eve::wide<T, N, ABI>> const& v ) noexcept
  {
    std::uint64_t res = 0;
    for (std::uint64_t i = 0; i != (std::uint64_t)N(); ++i) res |= v.get(i) << i;
    if constexpr (N() < 32) return std::pair{(std::uint32_t) res, eve::lane<1>};
    else                    return std::pair{res, eve::lane<1>};
  }

}
