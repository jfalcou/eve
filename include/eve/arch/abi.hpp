//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/deps/spy.hpp>
#include <eve/arch/cpu/abi.hpp>

#include <eve/deps/kumi.hpp>
#include <type_traits>

#if !defined(EVE_NO_SIMD)
#  if defined(EVE_INCLUDE_X86_HEADER)
#    include <eve/arch/x86/abi.hpp>
#  elif defined(EVE_INCLUDE_POWERPC_HEADER)
#    include <eve/arch/ppc/abi.hpp>
#  elif defined(EVE_INCLUDE_ARM_SVE_HEADER)
#    include <eve/arch/arm/sve/abi.hpp>
#  elif defined(EVE_INCLUDE_ARM_NEON_HEADER)
#    include <eve/arch/arm/neon/abi.hpp>
#  elif defined(EVE_INCLUDE_RISCV_HEADER)
#    include <eve/arch/riscv/abi.hpp>
#  endif
#endif

namespace eve
{
  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!
  //! @typedef abi_t
  //! @brief Find proper ABI type for Type/Lanes pair
  //!
  //! Computes the best ABI to use to efficiently store `Lanes` elements of type `Type` in
  //! order to use SIMD implementations and returns it's type.
  //!
  //! @tparam Type  Type of the element to store
  //! @tparam Lanes Number of elements to store
  //!
  //! @}
  //================================================================================================
#if defined (EVE_DOXYGEN_INVOKED)
  template<typename Type, width_type Lanes>
  using abi_t = /* Implementation defined */;
#else
  template<typename Type, width_type Lanes>
  requires( _::arithmetic_<Type> || eve::product_type<Type> || _::is_logical_<Type> )
  using abi_t = decltype(_::software_abi_of<translate_t<Type>, Lanes>);
#endif

  //================================================================================================
  // Check for bundle_ ABI
  //================================================================================================
  template<typename T>
  concept bundle_abi = std::same_as<T, bundle_> || requires
  {
    typename T::abi_type;
    requires std::same_as<typename T::abi_type, bundle_>;
  };

  //================================================================================================
  // Check for emulated_ ABI
  //================================================================================================
  template<typename T>
  concept emulated_abi = std::same_as<T, emulated_> || requires
  {
    typename T::abi_type;
    requires std::same_as<typename T::abi_type, emulated_>;
  };

  //================================================================================================
  // Check for aggregated_ ABI
  //================================================================================================
  template<typename T>
  concept aggregated_abi = std::same_as<T, aggregated_> || requires
  {
    typename T::abi_type;
    requires std::same_as<typename T::abi_type, aggregated_>;
  };

  //================================================================================================
  // Check for native ABI
  //================================================================================================
  template<typename T>
  concept native_abi = std::is_arithmetic_v<T> || !(emulated_abi<T> || aggregated_abi<T> || bundle_abi<T>);

  //================================================================================================
  // Check for non-native ABI
  //================================================================================================
  template<typename T>
  concept non_native_abi = !native_abi<T>;

  //================================================================================================
  // Concept for discriminating aggregated from non-agregated ABI
  //================================================================================================
  template<typename T>
  concept regular_abi = !aggregated_abi<T>;

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
