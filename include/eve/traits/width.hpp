//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/deps/kumi.hpp>
#include <eve/arch.hpp>
#include <eve/arch/abi.hpp>
#include <eve/concept/scalar.hpp>

EVE_NAMESPACE
{

  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!   @brief Computes the width of a given type
  //!
  //!   **Required header:** `#include <eve/traits/width.hpp>`
  //!
  //!   For a given type `T`, computes it's associated width.
  //!
  //!   @tparam T Type to process
  //!
  //! @}
  //================================================================================================
#if defined (EVE_DOXYGEN_INVOKED)
  template<typename T>
  inline constexpr width_type = /* Implementation defined */;
#else
  template<typename Type>
  inline constexpr width_type width_v = 1;

  template<typename Type>
  requires( !std::same_as<Type, std::remove_cvref_t<Type>> )
  inline constexpr width_type width_v<Type> = width_v<std::remove_cvref_t<Type>>;
#endif

  template<typename Type>
  using width_t = lanes_t<width_v<Type>>;

  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!   @brief Computes the fundamental width of a given type
  //!
  //!   **Required header:** `#include <eve/traits/width.hpp>`
  //!
  //!   Computes the width of the smallest register able to store
  //!   values of type `Type` for a given SIMD `ABI` with no uninitialized lanes.
  //!
  //!   @tparam Type  Type of value to assess
  //!   @tparam ABI   SIMD ABI to use as reference. Must models eve::regular_abi.
  //!
  //! @}
  //================================================================================================
#if defined (EVE_DOXYGEN_INVOKED)
  template<typename T, regular_abi ABI = eve::current_abi_type>
  constexpr inline width_type fundamental_width_v = /* Implementation defined */;
#else
  template<typename T, regular_abi ABI = eve::current_abi_type>
  constexpr inline width_type fundamental_width_v = _::fundamental_width<T, ABI>;

  namespace _
  {
    template<typename ABI>
    struct fundamental_width_t
    {
      template<typename... Ts>
      using type = std::integral_constant<width_type, kumi::_::min(static_cast<std::size_t>(eve::fundamental_width_v<Ts, ABI>)...)>;
    };
  }

  template<eve::product_type Type, regular_abi ABI>
  constexpr inline width_type fundamental_width_v<Type, ABI> = kumi::apply_traits_t<_::fundamental_width_t<ABI>::template type, Type>::value;
#endif

  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!   @brief Computes the maximum native width of a given type
  //!
  //!   **Required header:** `#include <eve/traits/width.hpp>`
  //!
  //!   Returns the width of the largest native register able to store
  //!   values of type `Type` for a given SIMD `ABI`.
  //!
  //!   @tparam Type  Type of value to assess
  //!   @tparam ABI   SIMD ABI to use as reference. Must models eve::regular_abi.
  //!
  //! @}
  //================================================================================================
#if defined (EVE_DOXYGEN_INVOKED)
  template<typename T, regular_abi = eve::current_abi_type>
  inline constexpr width_type max_native_width_v = /* Implementation defined */;
#else
  template<typename T, regular_abi ABI = eve::current_abi_type>
  inline constexpr width_type max_native_width_v = _::max_native_width<T, ABI>;

  namespace _
  {
    template<typename ABI>
    struct max_native_width_t
    {
      template<typename... Ts>
      using type = std::integral_constant<width_type, kumi::_::min(static_cast<std::size_t>(eve::max_native_width_v<Ts, ABI>)...)>;
    };
  }

  template<eve::product_type T, regular_abi ABI>
  inline constexpr width_type max_native_width_v<T, ABI> = kumi::apply_traits_t<_::max_native_width_t<ABI>::template type, T>::value;
#endif
  
  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!   @brief Computes the expected width of a given type
  //!
  //!   **Required header:** `#include <eve/traits/width.hpp>`
  //!
  //!   Default register width for a type. Sometimes is smaller than max_native_width.
  //!   @see [Frequency Scaling](@ref freqscale) for an explanation.
  //!
  //!   @tparam Type  Type of value to assess
  //!   @tparam ABI   SIMD ABI to use as reference. Must models eve::regular_abi.
  //!
  //! @}
  //================================================================================================
#if defined (EVE_DOXYGEN_INVOKED)
  template<typename T, regular_abi = eve::current_abi_type>
  inline constexpr width_type expected_width_v = /* Implementation defined */;
#else
  template<typename T, regular_abi ABI = eve::current_abi_type>
  inline constexpr width_type expected_width_v = max_native_width_v<T, ABI>;

  template<typename T>
  inline constexpr width_type expected_width_v<T, x86_512_> =
    x86_512_::avx512_default_64_bytes ? max_native_width_v<T, x86_512_> : max_native_width_v<T, x86_256_>;
#endif
}
