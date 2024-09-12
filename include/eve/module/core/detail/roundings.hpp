//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <cstdint>
#include <cfenv>

namespace eve::detail
{

  inline constexpr std::uint32_t round_to_nearest = FE_TONEAREST;  // Round to nearest (even)
  inline constexpr std::uint32_t round_down       = FE_DOWNWARD;   // Round down
  inline constexpr std::uint32_t round_up         = FE_UPWARD;     // Round up
  inline constexpr std::uint32_t round_toward_zero= FE_TOWARDZERO; // Round toward zero

  struct rounding_state{
    std::uint32_t oldrs;
    std::uint32_t currs;
    rounding_state(std::uint32_t newrs) : oldrs(fegetround())
    {
      currs = newrs;
      fesetround(newrs);
    }
    void restore(){ currs = oldrs; fesetround(oldrs); }
    void set(std::uint32_t rc){ currs = rc; fesetround(currs);      }
  };
}
