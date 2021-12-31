//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/wide.hpp>
#include <eve/logical.hpp>

namespace eve::experimental
{
  template<typename T>
  using simd = eve::wide<T, eve::fixed<16/sizeof(T)>>;

  template<typename T, int N >
  using fixed_size_simd = eve::wide<T, eve::fixed<N>>;

  template<typename T>
  using native_simd = eve::experimental::simd<T>;

  template<typename T>
  using simd_mask = eve::logical<eve::wide<T, eve::fixed<16/sizeof(T)>>>;

  template<typename T, int N >
  using fixed_size_simd_mask = eve::logical<eve::wide<T, eve::fixed<N>>>;

  template<typename T>
  using native_simd_mask = eve::experimental::simd_mask<T>;
}