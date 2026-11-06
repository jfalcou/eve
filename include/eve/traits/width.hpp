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

namespace eve
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
  //!   @brief Computes the expected width of a given type
  //!
  //!   **Required header:** `#include <eve/traits/width.hpp>`
  //!
  //!   Returns the exact width type of the register able to store
  //!   values of type `Type` for a given SIMD `ABI` as a native register type.
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
  inline constexpr width_type expected_width_v = _::expected_width<T, ABI>;

  namespace _
  {
    template<typename ABI>
    struct expected_width_t
    {
      template<typename... Ts>
      using type = std::integral_constant<width_type, kumi::_::min(static_cast<std::size_t>(eve::expected_width_v<Ts, ABI>)...)>;
    };
  }

  template<eve::product_type T, regular_abi ABI>
  inline constexpr width_type expected_width_v<T, ABI> = kumi::apply_traits_t<_::expected_width_t<ABI>::template type, T>::value;
#endif
  
  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!   @var nofs_width_v
  //!   @brief nofs stands for "no frequency scaling".
  //!
  //!   You can find more explanations in the 'frequency scaling tutorial'.
  //!   This refers to extreme frequency scaling one encounters when working with 64 byte
  //!   registers on intel. The processor scales frequency drammatically for a substantial
  //!   period of time. So even if the algorithm itself will run faster the overall perf
  //!   will go down. Generally speaking, 64 byte registers on intel make sense only
  //!   for really big data sets. `nofs_width` will produce 32 byte registers on avx512.
  //!   If you would like to default to 64 byte registers, you can build with DEVE_AVX512_DEFAULT_64_BYTES.
  //!   This is probably a good idea on AMD-ZEN4 but we do not detect that at the moment.
  //!
  //!   @note frequency scaling exists for avx2 as well but is generally considered
  //!   acceptable. For example popular implementations of libc use avx2, so you are very
  //!   likely already have it. You can always set the width manually if needed.
  //!
  //!   @note `eve::algo` by default will use `nofs_width`. See `allow_frequency_scaling`
  //!   trait.
  //!
  //!   @tparam Type  Type of value to assess
  //!   @tparam ABI   SIMD ABI to use as reference. Must models eve::regular_abi. defaults to current.
  //!
  //! @}
  //================================================================================================
  template <scalar_value T, regular_abi ABI = eve::current_abi_type>
  constexpr width_type nofs_width_v = expected_width_v<T, ABI>;

  template <scalar_value T>
  constexpr width_type nofs_width_v<T, x86_512_> =
    x86_512_::avx512_default_64_bytes ? expected_width_v<T, x86_512_> : expected_width_v<T, x86_256_>;

  template <scalar_value T, regular_abi ABI = eve::current_abi_type>
  using nofs_width_t = lanes_t<nofs_width_v<T>>;
}
