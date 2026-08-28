//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/abi.hpp>
#include <eve/detail/kumi.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  // Check for bundle_ ABI
  //================================================================================================
  template<typename T>
  concept bundle_abi = std::same_as<T, bundle_> || requires
  {
    typename T::abi_type;
    requires std::same_as<typename T::abi_type, bundle_>;
  };
  
  template<typename T>
  inline constexpr bool has_bundle_abi_v = bundle_abi<T>;

  template<typename T>
  using has_bundle_abi_t = std::bool_constant<bundle_abi<T>>; 
  
  //================================================================================================
  // Check for emulated_ ABI
  //================================================================================================
  template<typename T>
  concept emulated_abi = std::same_as<T, emulated_> || requires
  {
    typename T::abi_type;
    requires std::same_as<typename T::abi_type, emulated_>;
  };
  
  template<typename T>
  inline constexpr bool has_emulated_abi_v = emulated_abi<T>;

  template<typename T>
  using has_emulated_abi_t = std::bool_constant<emulated_abi<T>>; 

  //================================================================================================
  // Check for aggregated_ ABI
  //================================================================================================
  template<typename T>
  concept aggregated_abi = std::same_as<T, aggregated_> || requires
  {
    typename T::abi_type;
    requires std::same_as<typename T::abi_type, aggregated_>;
  };
 
  template<typename T>
  inline constexpr bool has_aggregated_abi_v = aggregated_abi<T>;

  template<typename T>
  using has_aggregated_abi_t = std::bool_constant<aggregated_abi<T>>;
 
  //================================================================================================
  // Check for native ABI
  //================================================================================================
  template<typename T>
  concept native_abi = std::is_arithmetic_v<T> || 
                       !(emulated_abi<T> || aggregated_abi<T> || bundle_abi<T> || std::is_void_v<T>);

  template<typename T>
  inline constexpr bool has_native_abi_v = native_abi<T>;

  template<typename T>
  using has_native_abi_t = std::bool_constant<native_abi<T>>;

  //================================================================================================
  // Check for non-native ABI 
  //================================================================================================
  template<typename T>
  concept non_native_abi = !native_abi<T>;
  
  template<typename T>
  inline constexpr bool has_non_native_abi_v = non_native_abi<T>;

  template<typename T>
  using has_non_native_abi_t = std::bool_constant<non_native_abi<T>>;

  //================================================================================================
  // Concept for discriminating aggregated from non-agregated ABI
  //================================================================================================
  template<typename T> 
  concept regular_abi = !aggregated_abi<T>;

  template<typename T>
  inline constexpr bool has_regular_abi_v = regular_abi<T>;

  template<typename T>
  using has_regular_abi_t = std::bool_constant<regular_abi<T>>; 

  //================================================================================================
  // Check if at least one type inside a wide has an aggregated ABI
  //================================================================================================
  namespace _
  {
    template<typename... Ts>
    using has_aggregate = std::bool_constant<(eve::aggregated_abi<Ts> || ... || false)>;
  }

  template<typename T>
  inline constexpr bool has_aggregated_component_v = eve::aggregated_abi<T>;

  template<typename T>
  requires ( eve::product_type<T> )
  inline constexpr bool has_aggregated_component_v<T> = kumi::apply_traits_t<_::has_aggregate, T>::value; 
}
