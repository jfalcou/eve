//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/float16.hpp>

#include <cmath>
#include <type_traits>
#include <concepts>

/*
  Standard library proxies to be used in tests where compatiblity with _Float16, or eve::float16_t,
  is needed pre C++23.
*/

#define MAKE_STD_PROXY(NAME)                                            \
  template <typename T>                                                 \
  constexpr T std_##NAME(T x)                                           \
  {                                                                     \
    if constexpr (std::same_as<T, eve::float16_t>)                      \
      return static_cast<eve::float16_t>(std::NAME(static_cast<float>(x)));\
      else return std::NAME(x);                                         \
  }                                                                     \
/* */

MAKE_STD_PROXY(abs);
MAKE_STD_PROXY(acos);
MAKE_STD_PROXY(acosh);
MAKE_STD_PROXY(asin);
MAKE_STD_PROXY(asinh);
MAKE_STD_PROXY(atan);
MAKE_STD_PROXY(atanh);
MAKE_STD_PROXY(cbrt);
MAKE_STD_PROXY(ceil);
MAKE_STD_PROXY(cos);
MAKE_STD_PROXY(cosh);
MAKE_STD_PROXY(exp);
MAKE_STD_PROXY(exp2);
MAKE_STD_PROXY(expm1);
MAKE_STD_PROXY(floor);
MAKE_STD_PROXY(log);
MAKE_STD_PROXY(log1p);
MAKE_STD_PROXY(log2);
MAKE_STD_PROXY(log10);
MAKE_STD_PROXY(nearbyint);
MAKE_STD_PROXY(sin);
MAKE_STD_PROXY(sqrt);
MAKE_STD_PROXY(tan);
MAKE_STD_PROXY(trunc);

#undef MAKE_STD_PROXY
