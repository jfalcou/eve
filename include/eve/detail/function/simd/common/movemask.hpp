//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/logical.hpp>

#include <utility>

namespace eve::detail
{
  // There is no usecase for aggregated - use top bits.
  // For emulated, N <= 64 is enforced in top bits.

  template<typename T, typename N>
  EVE_FORCEINLINE auto movemask( eve::logical<eve::wide<T, N>> const& v ) noexcept
  {
    static_assert ( !has_aggregated_abi_v<wide<T, N>>, "movemask is an internal function that does not make sense for aggregated" );

    std::uint64_t res = 0;
    for (std::uint64_t i = 0; i != (std::uint64_t)N(); ++i) {
      std::uint64_t elem = v.get(i) ? 1 : 0;
      res |= elem << i;
    }
    if constexpr (N() <= 32)  return std::pair{(std::uint32_t) res, eve::lane<1>};
    else                      return std::pair{res, eve::lane<1>};
  }

}
