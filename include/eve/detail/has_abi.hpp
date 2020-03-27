//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIl_HAS_ABI_HPP_INCLUDED
#define EVE_DETAIl_HAS_ABI_HPP_INCLUDED

#include <eve/arch/tags.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  // Check for emulated_ ABI
  //================================================================================================
  template<typename T> struct has_emulated_abi    : std::false_type {};

  template<typename T>
  requires requires { typename T::abi_type; }
  struct has_emulated_abi<T> : std::is_same<typename T::abi_type, emulated_>
  {};

  template<typename T>
  inline constexpr bool has_emulated_abi_v = has_emulated_abi<T>::value;

  template<typename T>
  using has_emulated_abi_t = typename has_emulated_abi<T>::type;

  //================================================================================================
  // Check for aggregated_ ABI
  //================================================================================================
  template<typename T> struct has_aggregated_abi  : std::false_type {};

  template<typename T>
  requires requires { typename T::abi_type; }
  struct has_aggregated_abi<T> : std::is_same<typename T::abi_type, aggregated_>
  {};

  template<typename T>
  inline constexpr bool has_aggregated_abi_v = has_aggregated_abi<T>::value;

  template<typename T>
  using has_aggregated_abi_t = typename has_aggregated_abi<T>::type;

  //================================================================================================
  // Check for native ABI
  //================================================================================================
  template<typename T>
  struct has_native_abi : std::bool_constant<   std::is_arithmetic_v<T>
                                            ||(!has_emulated_abi_v<T> && !has_aggregated_abi_v<T>)
                                            >
  {};

  template<typename T>
  inline constexpr bool has_native_abi_v = has_native_abi<T>::value;

  template<typename T>
  using has_native_abi_t = typename has_native_abi<T>::type;
}

#endif


