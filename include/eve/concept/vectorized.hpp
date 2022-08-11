//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/logical.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/traits/is_logical.hpp>
#include <eve/detail/wide_forward.hpp>

#include <concepts>

namespace eve
{
  //================================================================================================
  //!   @concept simd_value
  //!   @brief    Specifies that a type a SIMD type
  //!
  //!    The concept `simd_value<T>` is satisfied if and only if T verifies that
  //!    `std::is_same_v<cardinal_t<T>,scalar_cardinal> == false`.
  //!
  //!    @groupheader{Examples}
  //!    - `eve::logical<eve::wide<char>>`
  //!    - `eve::wide<float>`
  // !   - `eve::wide<int, eve::fixed<1>>`
  //================================================================================================
  template<typename T>
  concept simd_value = !std::same_as<eve::cardinal_t<T>, scalar_cardinal>;

  //================================================================================================
  //!   @concept integral_simd_value
  //!   @brief    Specifies that a type a SIMD type with integral elements
  //!
  //!    The concept `integral_simd_value<T>` is satisfied if and only if T satisfies
  //!    `eve::simd_value<T>` and `std::integral<` `eve::element_type<T>::``type>`.
  //!
  //!    @groupheader{Examples}
  //!    - `eve::logical<eve::wide<char>>`
  //!    - `eve::wide<int, eve::fixed<1>>`
  //================================================================================================
  template<typename T>
  concept integral_simd_value        = simd_value<T> && std::integral<element_type_t<T>>;

  template<typename T> concept signed_simd_value          = simd_value<T> && std::is_signed_v<element_type_t<T>>;
  template<typename T> concept unsigned_simd_value        = simd_value<T> && std::unsigned_integral<element_type_t<T>>;
  template<typename T> concept signed_integral_simd_value = simd_value<T> && std::signed_integral<element_type_t<T>>;
  template<typename T> concept floating_simd_value        = simd_value<T> && std::floating_point<element_type_t<T>>;
  template<typename T> concept real_simd_value            = simd_value<T> && std::is_arithmetic_v<element_type_t<T>>;
  template<typename T> concept floating_real_simd_value   = real_simd_value<T> && std::floating_point<element_type_t<T>>;
  template<typename T> concept integral_real_simd_value   = real_simd_value<T> && std::integral<element_type_t<T>>;

  template<typename T> struct is_simd_value : std::bool_constant<simd_value<T>> {};
}
