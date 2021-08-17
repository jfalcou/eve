//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/abi_of.hpp>
#include <eve/arch/tags.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits.hpp>
#include <type_traits>

namespace eve::detail
{
  // Check if a given ABI is native
  template<typename X>
  struct is_native
      : std::integral_constant< bool,
                                  !std::is_same_v<X, aggregated_> && !std::is_same_v<X, emulated_>
                              &&  !std::is_void_v<X>
                              >
  {
  };

  template<typename T>
  inline constexpr bool is_native_v = is_native<T>::value;

  template<typename T>
  using is_native_t = typename is_native<T>::type;

  // Check aggregated/emulated status of ABI
  template<typename X>
  struct is_aggregated : std::is_same<X, aggregated_>
  {
  };

  template<typename T>
  inline constexpr bool is_aggregated_v = is_aggregated<T>::value;

  template<typename T>
  using is_aggregated_t = typename is_aggregated<T>::type;

  template<typename X>
  struct is_emulated : std::is_same<X, emulated_>
  {
  };

  template<typename T>
  inline constexpr bool is_emulated_v = is_emulated<T>::value;

  template<typename T>
  using is_emulated_t = typename is_emulated<T>::type;

  template<typename X>
  struct is_bundle : std::is_same<X, bundle_>
  {
  };

  template<typename T>
  inline constexpr bool is_bundle_v = is_bundle<T>::value;

  template<typename T>
  using is_bundle_t = typename is_emulated<T>::type;
}

namespace eve
{
  // concepts related to above traits
  template<typename T> concept bundle     = detail::is_bundle_v<T>;
  template<typename T> concept emulated   = detail::is_emulated_v<T>;
  template<typename T> concept aggregated = detail::is_aggregated_v<T>;
  template<typename T> concept native     = detail::is_native_v<T>;
}
