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
#include <iostream>
namespace eve::detail
{

  bool constexpr enable_roundings = spy::compiler == spy::clang_ /*|| spy::compiler >= 13_gcc*/ || spy::compiler == spy::msvc_;

  template < typename O, typename F, typename T,  std::same_as<T> ... Ts>
  EVE_FORCEINLINE constexpr T with_rounding(F f, T a,  Ts ... b) noexcept
  {
#ifdef  SPY_COMPILER_IS_MSVC
#pragma float_control(precise, on, push)
#endif
#ifdef  SPY_COMPILER_IS_CLANG
#pragma clang fp exceptions(strict)
#endif
// gcc does not want to work with this nor with -frounding_math
// #ifdef  SPY_COMPILER_IS_GCC
// #if __GNUC__ >= 13
// #pragma STDC FENV_ACCESS on
// #endif
// #endif
//    std::cout << "icitte" << std::endl;
    auto oldstate = std::fegetround();
    std::fesetround(rounding_control<O>());
    auto r = f(a, b...);
    std::fesetround(oldstate);
// #ifdef  SPY_COMPILER_IS_GCC
// #if __GNUC__ >= 13
// #pragma STDC FENV_ACCESS off
// #endif
// #endif
#ifdef  SPY_COMPILER_IS_MSVC
#pragma float_control(pop)
#endif
    return r;
  }
}
