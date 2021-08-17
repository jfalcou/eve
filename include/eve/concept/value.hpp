//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/forward.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/traits/is_logical.hpp>

#include <concepts>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var value
  //! The concept `value<T>` is satisfied if and only if T satisfies
  //! either `eve::scalar_value` or `eve::simd_value`.
  //!
  //! #### Examples
  //! - `eve::logical<eve::wide<char>>`
  //! - `float`
  //! - `eve::wide<std::uint64_t>`
  //! - `eve::wide<int, eve::fixed<1>>`
  //! @}
  //================================================================================================
  template<typename T> concept value                 = simd_value<T> || scalar_value<T>;

  template<typename T> concept integral_value        = value<T> && std::integral<detail::value_type_t<T>>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var integral_value
  //! TODO describe
  //!
  //! #### Examples
  //! - `eve::wide<char>`
  //! - `int`
  //! - `eve::wide<int, eve::fixed<1>>`
  //! @}
  //================================================================================================

  template<typename T> concept signed_value          = value<T> && std::is_signed_v<detail::value_type_t<T>>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var signed_value
  //! TODO describe
  //!
  //! #### Examples
  //! - `eve::wide<char>`
  //! - `float`
  //! - `eve::wide<int, eve::fixed<1>>`
  //! @}
  //================================================================================================

  template<typename T> concept unsigned_value        = value<T> && std::unsigned_integral<detail::value_type_t<T>>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var unsigned_value
  //! TODO describe
  //!
  //! #### Examples
  //! - `unsigned int`
  //! - `eve::wide<std::uint8_t, eve::fixed<1>>`
  //! @}
  //================================================================================================

  template<typename T> concept signed_integral_value = value<T> && std::signed_integral<detail::value_type_t<T>>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var signed_integral_value
  //! TODO describe
  //!
  //! #### Examples
  //! - `short int`
  //! - `eve::wide<int, eve::fixed<1>>`
  //! @}
  template<typename T> concept floating_value        = value<T> && std::floating_point<detail::value_type_t<T>>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var floating_value
  //! TODO describe
  //!
  //! #### Examples
  //! - `double`
  //! - `eve::wide<float, eve::fixed<2>>`
  //! @}

  template<typename T> concept real_value            = real_simd_value<T> || real_scalar_value<T>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var real_value
  //! TODO describe
  //!
  //! #### Examples
  //! - `double`
  //! - `eve::wide<int, eve::fixed<2>>`
  //! @}

  template<typename T> concept floating_real_value   = real_value<T> && std::floating_point<detail::value_type_t<T>>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var floating_real_value
  //! TODO describe
  //!
  //! #### Examples
  //! - `double`
  //! - `eve::wide<float, eve::fixed<2>>`
  //! @}

  template<typename T> concept integral_real_value   = real_value<T> && std::integral<detail::value_type_t<T>>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var integral_real_value
  //! TODO describe
  //!
  //! #### Examples
  //! - `char`
  //! - `eve::wide<long int, eve::fixed<2>>`
  //! @}

  template<typename T> concept logical_value         = value<T> && is_logical_v<T>;
  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //! @var logical_value
  //! TODO describe
  //!
  //! #### Examples
  //! - `eve::logical<eve::wide<char>>`
  //! - `eve::logical<double>`
  //! @}
}
