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
  //! @concept simd_value
  //! @brief   Specifies that a type a SIMD type
  //!
  //! The concept `simd_value<T>` is satisfied if and only if T satisfies either
  //! `eve::arithmetic_simd_value` or `eve::logical_simd_value`.
  //!
  //! @groupheader{Examples}
  //!   - `eve::logical<eve::wide<short>>`
  //!   - `eve::wide<float>`
  //!   - `eve::wide<int, eve::fixed<1>>`
  //================================================================================================
  template<typename T>
  concept simd_value = arithmetic_simd_value<T> || logical_simd_value<T>;

  //================================================================================================
  //! @concept integral_simd_value
  //! @brief   Specifies that a type a SIMD type with integral elements
  //!
  //! The concept `integral_simd_value<T>` is satisfied if and only if T satisfies
  //! `eve::arithmetic_simd_value<T>` and `eve::element_type<T>` satisfies `std::integral`.
  //!
  //! @groupheader{Examples}
  //!  - `eve::logical<eve::wide<short>>`
  //!  - `eve::wide<unsigned int, eve::fixed<1>>`
  //================================================================================================
  template<typename T>
  concept integral_simd_value = arithmetic_simd_value<T> && std::integral<element_type_t<T>>;

  //================================================================================================
  //! @concept signed_simd_value
  //! @brief   Specifies that a type a SIMD type with signed elements
  //!
  //! The concept `integral_simd_value<T>` is satisfied if and only if T satisfies
  //! `eve::arithmetic_simd_value<T>` and `eve::element_type<T>` is signed.
  //!
  //! @groupheader{Examples}
  //!  - `eve::logical<eve::wide<short>>`
  //!  - `eve::wide<std::int64_t, eve::fixed<4>>`
  //================================================================================================
  template<typename T>
  concept signed_simd_value = arithmetic_simd_value<T> && std::is_signed_v<element_type_t<T>>;

  //================================================================================================
  //! @concept unsigned_simd_value
  //! @brief   Specifies that a type a SIMD type with unsigned elements
  //!
  //! The concept `unsigned_simd_value<T>` is satisfied if and only if T satisfies
  //! `eve::arithmetic_simd_value<T>` and `eve::element_type<T>` satisfies `std::unsigned_integral`.
  //!
  //! @groupheader{Examples}
  //!  - `eve::logical<eve::wide<unsigned int>>`
  //!  - `eve::wide<std::uint8_t, eve::fixed<8>>`
  //================================================================================================
  template<typename T>
  concept unsigned_simd_value =     arithmetic_simd_value<T>
                                &&  std::unsigned_integral<element_type_t<T>>;

  //================================================================================================
  //! @concept signed_integral_simd_value
  //! @brief   Specifies that a type a SIMD type with signed integral elements
  //!
  //! The concept `unsigned_simd_value<T>` is satisfied if and only if T satisfies
  //! `eve::arithmetic_simd_value<T>` and `eve::element_type<T>` satisfies `std::signed_integral`.
  //!
  //! @groupheader{Examples}
  //!  - `eve::logical<eve::wide<signed int>>`
  //!  - `eve::wide<std::int16_t, eve::fixed<8>>`
  //================================================================================================
  template<typename T>
  concept signed_integral_simd_value  =     arithmetic_simd_value<T>
                                        &&  std::signed_integral<element_type_t<T>>;

  //================================================================================================
  //! @concept floating_simd_value
  //! @brief   Specifies that a type a SIMD type with signed integral elements
  //!
  //! The concept `floating_simd_value<T>` is satisfied if and only if T satisfies
  //! `eve::arithmetic_simd_value<T>` and `eve::element_type<T>` satisfies `std::floating_point`.
  //!
  //! @groupheader{Examples}
  //!  - `eve::logical<eve::wide<signed int>>`
  //!  - `eve::wide<std::int16_t, eve::fixed<8>>`
  //================================================================================================
  template<typename T>
  concept floating_simd_value = arithmetic_simd_value<T> && std::floating_point<element_type_t<T>>;

  template<typename T> struct is_simd_value : std::bool_constant<simd_value<T>> {};
}
