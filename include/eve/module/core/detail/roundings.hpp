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
#include <eve/module/core/decorator/core.hpp>

namespace eve::detail
{

  inline bool constexpr enable_roundings = (spy::compiler == spy::clang_ && spy::architecture == spy::amd64_) || spy::compiler == spy::msvc_;

  template < typename O, typename F, typename T,  std::same_as<T> ... Ts>
  EVE_FORCEINLINE constexpr T with_rounding(F f, T a,  Ts ... b) noexcept
  {
#ifdef  SPY_COMPILER_IS_MSVC
#pragma float_control(precise, on, push)
#endif
#ifdef  SPY_COMPILER_IS_CLANG
#pragma clang fp exceptions(strict)
#endif
    auto oldstate = std::fegetround();
    std::fesetround(rounding_control<O>());
    auto r = f(a, b...);
    std::fesetround(oldstate);
#ifdef  SPY_COMPILER_IS_MSVC
#pragma float_control(pop)
#endif
    return r;
  }
}
