//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/wide_forward.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/traits/is_logical.hpp>
#include <eve/traits/element_type.hpp>

#include <concepts>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept value
  //! @brief The concept `value<T>` is satisfied if and only if T satisfies
  //! either `eve::scalar_value` or `eve::simd_value`.
  //!
  //! @groupheader{Examples}
  //! - `eve::logical<eve::wide<char>>`
  //! - `float`
  //! - `eve::wide<std::uint64_t>`
  //! - `eve::wide<int, eve::fixed<1>>`
  //================================================================================================
  template<typename T> concept value                 = simd_value<T> || scalar_value<T>;
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept integral_value
  //! @brief The concept `integral_value<T>` is satisfied if and only if T satisfies
  //! `eve::value` and the element type satisfies `std::integral`
  //!
  //! @groupheader{Examples}
  //! - `eve::wide<char>`
  //! - `int`
  //! - `eve::wide<int, eve::fixed<1>>`
  //================================================================================================
  template<typename T> concept integral_value        = value<T> && std::integral<translate_element_type_t<T>>;
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept signed_value
  //! @brief The concept `signed_value<T>` is satisfied if and only if T satisfies
  //! `eve::value` and the element type satisfies `std::is_signed`
  //!
  //! @groupheader{Examples}
  //! - `eve::wide<char>`
  //! - `float`
  //! - `eve::wide<int, eve::fixed<1>>`
  //================================================================================================
  template<typename T> concept signed_value          = value<T> && std::is_signed_v<translate_element_type_t<T>>;
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept unsigned_value
  //! @brief The concept `unsigned_value<T>` is satisfied if and only if T satisfies
  //! `eve::value` and the element type satisfies `std::unsigned_integral`
  //!
  //! @groupheader{Examples}
  //! - `unsigned int`
  //! - `eve::wide<std::uint8_t, eve::fixed<1>>`
  //================================================================================================
  template<typename T> concept unsigned_value        = value<T> && std::unsigned_integral<translate_element_type_t<T>>;
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept signed_integral_value
  //! @brief The concept `signed_integral_value<T>` is satisfied if and only if T satisfies
  //! `eve::value` and the element type satisfies `std::signed_integral`
  //!
  //! @groupheader{Examples}
  //! - `short int`
  //! - `eve::wide<int, eve::fixed<1>>`
  //================================================================================================
  template<typename T> concept signed_integral_value = value<T> && std::signed_integral<translate_element_type_t<T>>;
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept floating_value
  //! @brief The concept `floating_value<T>` is satisfied if and only if T satisfies
  //! `eve::value` and the element type satisfies `std::floating_point`
  //!
  //! @groupheader{Examples}
  //! - `double`
  //! - `eve::wide<float, eve::fixed<2>>`
  //================================================================================================
  template<typename T> concept floating_value        = value<T> && std::floating_point<translate_element_type_t<T>>;
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept logical_value
  //! @brief The concept `logical_value<T>` is satisfied if and only if T satisfies
  //! `eve::value` and the element type satisfies is_logical_v
  //!
  //! @groupheader{Examples}
  //! - `eve::logical<eve::wide<char>>`
  //! - `eve::logical<double>`
  //================================================================================================
  template<typename T> concept logical_value         = value<T> && is_logical_v<T>;
  //================================================================================================
  //! @}
  //================================================================================================


  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept plain_value
  //! @brief The concept `plain_value<T>` is satisfied if and only if T satisfies
  //! `eve::plain_simd_value` or `eve::plain_scalar_value`.
  //!
  //! @groupheader{Examples}
  //! - `char`
  //! - `eve::wide<double>`
  //================================================================================================
  template<typename T> concept plain_value         = plain_simd_value<T> || plain_scalar_value<T>;
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @concept relaxed_logical_value
  //! @brief The concept `relaxed_logical_value<T>` is satisfied if and only if T is a
  //! boolean value or satisfies the `eve::logical_value` concept.
  //!
  //! @groupheader{Examples}
  //! - `eve::logical<char>`
  //! - `eve::logical<eve::wide<char>>`
  //! - `float`
  //! - `eve::wide<float>`
  //! - `bool`
  //================================================================================================
  template <typename T>
  concept relaxed_logical_value = logical_value<T> || std::same_as<T, bool>;
  //================================================================================================
  //! @}
  //================================================================================================
}
