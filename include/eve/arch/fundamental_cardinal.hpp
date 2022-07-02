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

namespace eve
{
  //================================================================================================
  //! @addtogroup arch
  //! @{
  //!   @struct fundamental_cardinal
  //!   @brief Computes the fundamental cardinal of a given type
  //!
  //!   **Required header:** `#include <eve/arch/fundamental_cardinal.hpp>`
  //!
  //!   eve::fundamental_cardinal computed the cardinal of the smallest register able to store
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
  struct fundamental_cardinal
      : fixed<ABI::template fundamental_cardinal<Type>>
  {
    using type = fixed<ABI::template fundamental_cardinal<Type>>;
  };

  template<typename Type, regular_abi ABI = eve::current_abi_type>
  using fundamental_cardinal_t = typename fundamental_cardinal<Type, ABI>::type;

  template<typename Type, regular_abi ABI = eve::current_abi_type>
  constexpr inline auto fundamental_cardinal_v = fundamental_cardinal<Type, ABI>::value;

  //================================================================================================
  // product_type special case
  //================================================================================================
  namespace detail
  {
    template<typename T, regular_abi ABI> struct min_fundamental;

    template<typename... T, regular_abi ABI>
    struct min_fundamental<kumi::tuple<T...>,ABI>
    {
      static constexpr std::ptrdiff_t value = std::min({fundamental_cardinal<T,ABI>::value...});
    };
  }

  template<kumi::product_type T, regular_abi ABI>
  struct fundamental_cardinal<T,ABI> : fixed<detail::min_fundamental<kumi::as_tuple_t<T>,ABI>::value>
  {
    using type = fixed<detail::min_fundamental<kumi::as_tuple_t<T>,ABI>::value>;
  };

  template<typename Type, typename ABI = eve::current_abi_type>
  inline constexpr fundamental_cardinal<Type,ABI> const fundamental = {};
}
