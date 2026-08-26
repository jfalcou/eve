
//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <cstddef>
#include <eve/arch/cardinals.hpp>
#include <eve/arch/abi_traits.hpp>
#include <eve/arch/spec.hpp>
#include <eve/deps/kumi.hpp>

#include <type_traits>

namespace eve
{
  namespace _
  {
    template<typename ABI>
    struct find_fundamental_cardinal_t
    {
      template<typename T>
      consteval auto operator()(T&&) const noexcept
      {
        return fixed<ABI::template fundamental_cardinal<T>>{};
      }
    };

    template<typename ABI>
    struct find_expected_cardinal_t
    {
      template<typename T>
      consteval auto operator()(T&&) const noexcept
      {
        return fixed<ABI::template expected_cardinal<T>>{};
      }
    };
  }

  //================================================================================================
  //! @addtogroup arch
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
  //!    #### Helper variable template
  //!
  //!    @code{.cpp}
  //!    template<typename Type, regular_abi ABI = eve::current_abi_type>
  //!    inline constexpr auto fundamental_cardinal_v = /* Implementation defined */;
  //!    @endcode
  //!
  //!    #### Helper type
  //!
  //!    @code{.cpp}
  //!    template<typename Type, regular_abi ABI = eve::current_abi_type>
  //!    using fundamental_cardinal_t = fixed<fundamental_cardinal_v<Type, ABI>>;
  //!    @endcode
  //!
  //! @}
  //================================================================================================
  template<typename Type, regular_abi ABI = eve::current_abi_type>
  constexpr inline auto fundamental_cardinal_v = ABI::template fundamental_cardinal<Type>;

  template<eve::product_type Type, regular_abi ABI>
  constexpr inline auto fundamental_cardinal_v<Type, ABI> = kumi::min(kumi::result::flatten_all_t<Type, _::find_fundamental_cardinal_t<ABI>>{});

  template<typename Type, regular_abi ABI = eve::current_abi_type>
  using fundamental_cardinal_t = fixed<fundamental_cardinal_v<Type, ABI>>;
  
  //================================================================================================
  //! @addtogroup arch
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
  //!    inline constexpr auto expected_cardinal_v = /* Implementation defined */;
  //!    @endcode
  //!
  //!    #### Helper type
  //!
  //!    @code{.cpp}
  //!    template<typename Type, regular_abi ABI = eve::current_abi_type>
  //!    using fundamental_cardinal_t = fixed<expected_cardinal_v<Type, ABI>>;
  //!    @endcode
  //!
  //! @}
  //================================================================================================
  template<typename Type, regular_abi ABI = eve::current_abi_type>
  inline constexpr auto expected_cardinal_v = ABI::template expected_cardinal<Type>; 

  template<eve::product_type Type, regular_abi ABI>
  inline constexpr auto expected_cardinal_v<Type, ABI> = kumi::min(kumi::result::flatten_all_t<Type, _::find_expected_cardinal_t<ABI>>{});

  template<typename Type, regular_abi ABI = eve::current_abi_type>
  using expected_cardinal_t = fixed<expected_cardinal_v<Type, ABI>>;
}
