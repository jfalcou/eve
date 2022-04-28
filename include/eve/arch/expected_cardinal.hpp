//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <cstddef>
#include <eve/arch/cardinals.hpp>
#include <eve/arch/spec.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/kumi.hpp>
#include <type_traits>
#include <limits>
#include <utility>
#include <algorithm>


namespace eve
{
  //================================================================================================
  //! @addtogroup arch
  //! @{
  //!   @struct expected_cardinal
  //!   @brief Computes the expected cardinal of a given type
  //!
  //!   **Required header:** `#include <eve/arch/expected_cardinal.hpp>`
  //!
  //!   eve::expected_cardinal computed the cardinal of the  register able to store
  //!   values of type `Type` for a given SIMD `ABI` as a native register type.
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
  //!    template<typename Type, regular_abi ABI = EVE_CURRENT_ABI>
  //!    using expected_cardinal_t = typename expected_cardinal<Type, ABI>::type;
  //!    @endcode
  //!
  //!    <br/>
  //!    #### Helper variable template
  //!
  //!    @code{.cpp}
  //!    template<typename Type, regular_abi ABI = EVE_CURRENT_ABI>
  //!    inline constexpr auto expected_cardinal_v = expected_cardinal_t<Type, ABI>::value;
  //!    @endcode
  //!
  //!    @code{.cpp}
  //!    // Cardinal template inline variable to use with functions like eve::load
  //!    template<typename Type, typename ABI = EVE_CURRENT_ABI>
  //!    inline constexpr expected_cardinal<Type,ABI> const expected = {};
  //!    @endcode
  //! @}
  //================================================================================================
  template<typename Type, regular_abi ABI = EVE_CURRENT_ABI>
  struct expected_cardinal
      : fixed<ABI::template expected_cardinal<Type>>
  {
    using type = fixed<ABI::template expected_cardinal<Type>>;
  };

  template<typename Type, regular_abi ABI = EVE_CURRENT_ABI>
  using expected_cardinal_t = typename expected_cardinal<Type, ABI>::type;

  template<typename Type, regular_abi ABI = EVE_CURRENT_ABI>
  constexpr inline auto expected_cardinal_v = expected_cardinal<Type, ABI>::value;

  //================================================================================================
  // product_type special case
  //================================================================================================
  namespace detail
  {
    template<typename T, regular_abi ABI> struct min_cardinal;

    template<typename... T, regular_abi ABI>
    struct min_cardinal<kumi::tuple<T...>,ABI>
    {
      static constexpr std::ptrdiff_t value = std::min({expected_cardinal<T,ABI>::value...});
    };
  }

  template<kumi::product_type T, regular_abi ABI>
  struct expected_cardinal<T,ABI> : fixed<detail::min_cardinal<kumi::as_tuple_t<T>,ABI>::value>
  {
    using type = fixed<detail::min_cardinal<kumi::as_tuple_t<T>,ABI>::value>;
  };

  //================================================================================================
  // Cardinal template inline object for passing cardinal values to functions like load/store
  //================================================================================================
  template<typename Type, typename API = EVE_CURRENT_ABI>
  inline constexpr expected_cardinal<Type,API> const expected = {};
}
