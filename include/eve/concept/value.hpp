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

#include <concepts>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @concept value
  //! The concept `value<T>` is satisfied if and only if T satisfies
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
  //! @concept integral_value
  //! TODO describe
  //!
  //! @groupheader{Examples}
  //! - `eve::wide<char>`
  //! - `int`
  //! - `eve::wide<int, eve::fixed<1>>`
  //================================================================================================
  template<typename T> concept integral_value        = value<T> && std::integral<element_type_t<T>>;

  //================================================================================================
  //! @concept signed_value
  //! TODO describe
  //!
  //! @groupheader{Examples}
  //! - `eve::wide<char>`
  //! - `float`
  //! - `eve::wide<int, eve::fixed<1>>`
  //================================================================================================
  template<typename T> concept signed_value          = value<T> && std::is_signed_v<element_type_t<T>>;

  //================================================================================================
  //! @concept unsigned_value
  //! TODO describe
  //!
  //! @groupheader{Examples}
  //! - `unsigned int`
  //! - `eve::wide<std::uint8_t, eve::fixed<1>>`
  //================================================================================================
  template<typename T> concept unsigned_value        = value<T> && std::unsigned_integral<element_type_t<T>>;

  //================================================================================================
  //! @concept signed_integral_value
  //! TODO describe
  //!
  //! @groupheader{Examples}
  //! - `short int`
  //! - `eve::wide<int, eve::fixed<1>>`
  //================================================================================================
  template<typename T> concept signed_integral_value = value<T> && std::signed_integral<element_type_t<T>>;

  //================================================================================================
  //! @concept floating_value
  //! TODO describe
  //!
  //! @groupheader{Examples}
  //! - `double`
  //! - `eve::wide<float, eve::fixed<2>>`
  //================================================================================================
  template<typename T> concept floating_value        = value<T> && std::floating_point<element_type_t<T>>;

  //================================================================================================
  //! @concept logical_value
  //! TODO describe
  //!
  //! @groupheader{Examples}
  //! - `eve::logical<eve::wide<char>>`
  //! - `eve::logical<double>`
  //================================================================================================
  template<typename T> concept logical_value         = value<T> && is_logical_v<T>;


  //================================================================================================
  //! @concept ordered_value
  //! TODO describe
  //!
  //! @groupheader{Examples}
  //! - `double`
  //! - `eve::wide<int, eve::fixed<2>>`
  //================================================================================================
  template<typename T> concept ordered_value = value<T> && std::totally_ordered<element_type_t<T>>;

   //================================================================================================
  //! @concept floating_ordered_value
  //! TODO describe
  //!
  //! @groupheader{Examples}
  //! - `double`
  //! - `eve::wide<float, eve::fixed<2>>`
  //================================================================================================
  template<typename T> concept floating_ordered_value = ordered_value<T> && std::floating_point<element_type_t<T>>;

}
