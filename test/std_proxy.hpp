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

template <typename T>
constexpr T std_floor(T x)
{
  if constexpr (std::same_as<T, eve::float16_t>) return static_cast<eve::float16_t>(std::floor(static_cast<float>(x)));
  else                                           return std::floor(x);
}

template <typename T>
constexpr T std_ceil(T x)
{
  if constexpr (std::same_as<T, eve::float16_t>) return static_cast<eve::float16_t>(std::ceil(static_cast<float>(x)));
  else                                           return std::ceil(x);
}

template <typename T>
constexpr T std_trunc(T x)
{
  if constexpr (std::same_as<T, eve::float16_t>) return static_cast<eve::float16_t>(std::trunc(static_cast<float>(x)));
  else                                           return std::trunc(x);
}

template <typename T>
constexpr T std_nearbyint(T x)
{
  if constexpr (std::same_as<T, eve::float16_t>) return static_cast<eve::float16_t>(std::nearbyint(static_cast<float>(x)));
  else                                           return std::nearbyint(x);
}

template <typename T>
constexpr T std_abs(T x)
{
  if constexpr (std::same_as<T, eve::float16_t>) return static_cast<eve::float16_t>(std::abs(static_cast<float>(x)));
  else                                           return std::abs(x);
}

template <typename T>
constexpr T std_sqrt(T x)
{
  if constexpr (std::same_as<T, eve::float16_t>) return static_cast<eve::float16_t>(std::sqrt(static_cast<float>(x)));
  else                                           return std::sqrt(x);
}
