//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <cstddef>
#include <eve/arch/widths.hpp>
#include <eve/arch/spec.hpp>
#include <eve/detail/meta.hpp>
#include <eve/deps/kumi.hpp>
#include <type_traits>
#include <limits>
#include <utility>

namespace eve
{
  //================================================================================================
  //! @addtogroup eve_arch
  //! @{
  //!   @struct fundamental_width
  //!   @brief Computes the fundamental width of a given type
  //!
  //!   **Required header:** `#include <eve/arch/fundamental_width.hpp>`
  //!
  //!   eve::fundamental_width computes the width of the smallest register able to store
  //!   values of type `Type` for a given SIMD `ABI` with no uninitialized lanes.
  //!
  //!   @tparam Type  Type of value to assess
  //!   @tparam ABI   SIMD ABI to use as reference. Must models eve::regular_abi.
  //!
  //!   #### Member types
  //!
  //!   |Name   | Definition                               |
  //!   |:------|:-----------------------------------------|
  //!   |`type` | The type of width computed for `Type` |
  //!
  //!    <br/>
  //!    #### Helper types
  //!
  //!    @code{.cpp}
  //!    template<typename Type, regular_abi ABI = eve::current_abi_type>
  //!    using fundamental_width_t = typename fundamental_width<Type, ABI>::type;
  //!    @endcode
  //!
  //!    <br/>
  //!    #### Helper variable template
  //!
  //!    @code{.cpp}
  //!    template<typename Type, regular_abi ABI = eve::current_abi_type>
  //!    inline constexpr auto fundamental_width_v = fundamental_width_t<Type, ABI>::value;
  //!    @endcode
  //!
  //!    @code{.cpp}
  //!    // Width template inline variable to use with functions like eve::load
  //!    template<typename Type, typename ABI = eve::current_abi_type>
  //!    inline constexpr fundamental_width<Type,ABI> const fundamental = {};
  //!    @endcode
  //! @}
  //================================================================================================
  template<typename Type, regular_abi ABI = eve::current_abi_type>
  struct fundamental_width
      : fixed<ABI::template fundamental_width<Type>>
  {
    using type = fixed<ABI::template fundamental_width<Type>>;
  };

  template<typename Type, regular_abi ABI = eve::current_abi_type>
  using fundamental_width_t = typename fundamental_width<Type, ABI>::type;

  template<typename Type, regular_abi ABI = eve::current_abi_type>
  constexpr inline width_type fundamental_width_v = fundamental_width<Type, ABI>::value;

  //================================================================================================
  // product_type special case
  //================================================================================================
  namespace _
  {
    template<typename T, regular_abi ABI> struct min_fundamental;

    template<typename... T, regular_abi ABI>
    struct min_fundamental<kumi::tuple<T...>,ABI>
    {
      static constexpr width_type value = std::min({fundamental_width<T,ABI>::value...});
    };
  }

  template<eve::product_type T, regular_abi ABI>
  struct fundamental_width<T,ABI> : fixed<_::min_fundamental<kumi::as_tuple_t<T>,ABI>::value>
  {
    using type = fixed<_::min_fundamental<kumi::as_tuple_t<T>,ABI>::value>;
  };

  template<typename Type, typename ABI = eve::current_abi_type>
  inline constexpr fundamental_width<Type,ABI> const fundamental = {};
}
