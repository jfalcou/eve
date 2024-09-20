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

  template < typename O >
  EVE_FORCEINLINE constexpr int rcontrol() noexcept
  {
    if constexpr(O::contains(lower))          return round_down;
    else if constexpr(O::contains(upper))     return round_up;
    else if constexpr(O::contains(tonearest)) return round_to_nearest;
    else if constexpr(O::contains(tozero))    return round_toward_zero;
    else return round_to_nearest;
  }

  template < typename O, typename F, typename T,  std::same_as<T> ... Ts>
  EVE_FORCEINLINE constexpr T with_rounding(F f, T a,  Ts ... b) noexcept
  {
#ifdef  SPY_COMPILER_IS_MSVC
#pragma float_control(precise, on, push)
#endif
#ifdef  SPY_COMPILER_IS_CLANG
#pragma clang fp exceptions(strict)
#endif
#ifdef  SPY_COMPILER_IS_GCC
#if __GNUC__ >= 13
#pragma STDC FENV_ACCESS on
#endif
#endif
    auto oldstate = std::fegetround();
    std::fesetround(rcontrol<O>());
    auto r = f(a, b...);
    std::fesetround(oldstate);
#ifdef  SPY_COMPILER_IS_GCC
#if __GNUC__ >= 13
#pragma STDC FENV_ACCESS off
#endif
#endif
#ifdef  SPY_COMPILER_IS_MSVC
#pragma float_control(pop)
#endif
    return r;
  }
}
