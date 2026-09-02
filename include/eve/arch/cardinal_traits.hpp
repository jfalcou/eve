
//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/cardinals.hpp>
#include <eve/arch/spec.hpp>
#include <eve/detail/kumi.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>

namespace eve
{
  namespace _
  {
    template<typename T>
    inline constexpr std::ptrdiff_t cardinal_v = 1;

    template<typename T>
    inline constexpr std::ptrdiff_t cardinal_v<logical<T>> = cardinal_v<T>;

    template<typename T, typename Size>
    inline constexpr std::ptrdiff_t cardinal_v<wide<Type,Size>> = Size{};

    template<regular_abi ABI>
    struct std::ptrdiff_t find_fundamental_cardinal_t
    {
      template<typename T>
      consteval auto operator()(T&&) const noexcept
      {
        return fixed<ABI::template fundamental_cardinal<T>>{};
      }
    };

    template<regular_abi ABI>
    struct std::ptrdiff_t find_expected_cardinal_t
    {
      template<typename T>
      consteval auto operator()(T&&) const noexcept
      {
        return fixed<ABI::template expected_cardinal<T>>{};
      }
    };
  }

  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!   @struct cardinal
  //!   @brief Computes the cardinal of a given type
  //!
  //!   **Required header:** `#include <eve/arch/cardinal_traits.hpp>`
  //!
  //!   For a given type `T`, computes the type of its cardinal.
  //!
  //!   @tparam T Type to process
  //!
  //!   #### Member types
  //!
  //!   |Name   | Definition               |
  //!   |:------|:-------------------------|
  //!   |`type` | The cardinal type of `T` |
  //!
  //!    <br/>
  //!
  //!   @groupheader{Helper types}
  //!
  //!   @code{.cpp}
  //!   template<typename Type>
  //!   using cardinal_t = typename cardinal<Type>::type;
  //!   @endcode
  //!
  //!   @groupheader{Helper variable template}
  //!
  //!   @code{.cpp}
  //!   template<typename Type>
  //!   inline constexpr auto cardinal_v = cardinal<Type>::value;
  //!   @endcode
  //! @}
  //================================================================================================
  template<typename T>
  inline constexpr std::ptrdiff_t cardinal_v = _::cardinal_v<std::remove_cvref_t<T>>;

  template<typename T>
  using cardinal_t = fixed<cardinal_v<T>>; 

  //================================================================================================
  //! @addtogroup eve_arch
  //! @{
  //!   @struct fundamental_cardinal
  //!   @brief Computes the fundamental cardinal of a given type
  //!
  //!   **Required header:** `#include <eve/arch/cardinal_traits.hpp>`
  //!
  //!   eve::fundamental_cardinal computes the cardinal of the smallest register able to store
  //!   values of type `Type` for a given SIMD `ABI` with no uninitialized lanes.
  //!
  //!   @tparam Type  Type of value to assess
  //!   @tparam ABI   SIMD ABI to use as reference. Must models eve::regular_abi.
  //!
  //!   #### Member types
  //!
  //!   |Name   | Definition                               |
  //!   |:------|:-----------------------------------------|
  //!   |`type` | The type of cardinal computed for `Type` |
  //!
  //!    <br/>
  //!    #### Helper types
  //!
  //!    @code{.cpp}
  //!    template<typename Type, regular_abi ABI = eve::current_abi_type>
  //!    using fundamental_cardinal_t = typename fundamental_cardinal<Type, ABI>::type;
  //!    @endcode
  //!
  //!    <br/>
  //!    #### Helper variable template
  //!
  //!    @code{.cpp}
  //!    template<typename Type, regular_abi ABI = eve::current_abi_type>
  //!    inline constexpr auto fundamental_cardinal_v = fundamental_cardinal_t<Type, ABI>::value;
  //!    @endcode
  //!
  //!    @code{.cpp}
  //!    // Cardinal template inline variable to use with functions like eve::load
  //!    template<typename Type, typename ABI = eve::current_abi_type>
  //!    inline constexpr fundamental_cardinal<Type,ABI> const fundamental = {};
  //!    @endcode
  //! @}
  //================================================================================================
  template<typename Type, regular_abi ABI = eve::current_abi_type>
  constexpr inline auto fundamental_cardinal_v = ABI::template fundamental_cardinal<Type>;

  template<eve::product_type Type, regular_abi ABI>
  constexpr inline auto fundamental_cardinal_v<Type, ABI> = 
    kumi::min(kumi::result::flatten_all_t<Type, _::find_fundamental_cardinal_t<ABI>>{});

  template<typename Type, regular_abi ABI = eve::current_abi_type>
  using fundamental_cardinal_t = fixed<fundamental_cardinal_v<Type, ABI>>;

  //================================================================================================
  //! @addtogroup eve_arch
  //! @{
  //!   @typedef expected_cardinal_t
  //!   @brief Computes the expected cardinal of a given type
  //!
  //!   **Required header:** `#include <eve/arch/cardinal_traits.hpp>`
  //!
  //!   @ref eve::expected_cardinal_t is the exact cardinal type of the register able to store
  //!   values of type `Type` for a given SIMD `ABI` as a native register type.
  //!
  //!   @tparam Type  Type of value to assess
  //!   @tparam ABI   SIMD ABI to use as reference. Must models eve::regular_abi.
  //!
  //!    #### Helper variable template
  //!
  //!    @code{.cpp}
  //!    template<typename Type, regular_abi ABI = eve::current_abi_type>
  //!    inline constexpr auto expected_cardinal_v = expected_cardinal_t<Type, ABI>::value;
  //!    @endcode
  //! @}
  //================================================================================================
  template<typename Type, regular_abi ABI = eve::current_abi_type>
  inline constexpr auto expected_cardinal_v = ABI::template expected_cardinal<Type>;

  template<eve::product_type Type, regular_abi ABI>
  inline constexpr auto expected_cardinal_v<Type, ABI> = 
    kumi::min(kumi::result::flatten_all_t<Type, _::find_expected_cardinal_t<ABI>>{});

  template<typename Type, regular_abi ABI = eve::current_abi_type>
  using expected_cardinal_t = fixed<expected_cardinal_v<Type, ABI>>;
}

