//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/abi.hpp>
#include <eve/deps/kumi.hpp>
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
  struct has_bundle_abi<T> : std::bool_constant<bundle_abi<T>> 
  {};

  template<typename T>
  inline constexpr bool bundle_abi = bundle_abi<T>;

  template<typename T>
  using has_bundle_abi_t = typename has_bundle_abi<T>::type;

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
  struct has_emulated_abi<T> : std::bool_constant<emulated_abi<T>> 
  {};

  template<typename T>
  inline constexpr bool emulated_abi = emulated_abi<T>;

  template<typename T>
  using has_emulated_abi_t = typename has_emulated_abi<T>::type;

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
  struct has_aggregated_abi<T> : std::bool_constant<aggregated_abi<T>> 
  {};

  template<typename T>
  inline constexpr bool aggregated_abi = aggregated_abi<T>;

  template<typename T>
  using has_aggregated_abi_t = typename has_aggregated_abi<T>::type;

  //================================================================================================
  // Check for native ABI
  //================================================================================================
  template<typename T>
  concept native_abi = (!emulated_abi<T> && !aggregated_abi<T> && !std::is_void_v<T>) || std::is_arithmetic_v<T>;

  template<typename T>
  struct has_native_abi : std::bool_constant<native_abi<T>>
  {};

  template<typename T>
  inline constexpr bool native_abi = native_abi<T>;

  template<typename T>
  using has_native_abi_t = typename has_native_abi<T>::type;

  //================================================================================================
  // Check for non-native ABI 
  //================================================================================================
  template<typename T>
  concept non_native_abi = _::one_of<T, aggregated_, emulated_, bundle_>; 
  
  template<typename T>
  struct has_non_native_abi : std::bool_constant<non_native_abi<T>>
  {};

  template<typename T>
  inline constexpr bool non_native_abi = non_native_abi<T>;

  template<typename T>
  using has_non_native_abi_t = typename has_non_native_abi<T>::type;

  //================================================================================================
  // Concept for discriminating aggregated from non-agregated ABI
  //================================================================================================
  template<typename T> 
  concept regular_abi = !std::same_as<T,aggregated_>;

  //================================================================================================
  // Check if at least one type inside a wide has an aggregated ABI
  //================================================================================================
  template<typename T>
  struct has_aggregated_component : std::bool_constant<aggregated_abi<T>> {};

  namespace _
  {
    struct check_abi
    {
      template<typename A, typename T>
      auto operator()(A const&, T const&) const noexcept
      {
        return std::bool_constant<A::value || eve::aggregated_abi<T>>{};
      }
    };
  }

  template<typename T>
  requires eve::product_type<T>
  struct  has_aggregated_component<T>
        : kumi::result::fold_left<_::check_abi, T, std::false_type>::type
  {};

  template<typename T>
  inline constexpr bool has_aggregated_component_v = has_aggregated_component<T>::value;

  template<typename T>
  using has_aggregated_component_t = typename has_aggregated_component<T>::type;
}
