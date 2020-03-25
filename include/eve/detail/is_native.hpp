//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_IS_NATIVE_HPP_INCLUDED
#define EVE_DETAIL_IS_NATIVE_HPP_INCLUDED

#include <eve/arch/tags.hpp>
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

  // Associated Concept-like entity
  template<typename T>
  using native = std::enable_if_t<is_native_v<T>>;

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
}

namespace eve
{
  // concepts related to above traits
  template<typename T> concept emulated   = detail::is_emulated_v<T>;
  template<typename T> concept aggregated = detail::is_aggregated_v<T>;
  template<typename T> concept native_c     = detail::is_native_v<T>; 
}

#endif
