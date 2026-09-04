//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/arch/spec.hpp>
#include <eve/arch/float16.hpp>
#include <eve/deps/kumi.hpp>

#include <concepts>
#include <type_traits>

namespace eve
{
    template<typename T> struct logical;
}

namespace eve::_
{
  template<typename T>
  inline constexpr bool is_logical_ = false;

  template<typename T>
  inline constexpr bool is_logical_<eve::logical<T>> = true;
  
  template<typename T> concept arithmetic_ = std::is_arithmetic_v<T> || std::same_as<T, eve::float16_t>;
  
  template<typename T>
  concept supported_simd_type = !std::same_as<T, eve::float16_t> || _::supports_fp16_vector_conversion;

  template<typename T, std::ptrdiff_t N>
  inline constexpr auto width_in_bits = sizeof(T) * N * 8;

  //================================================================================================
  // Select Hardware ABI from Type x Cardinal combo
  // Emulated is the default : used wether we do not have a native register or if there is no simd
  
  // hardward_abi_of is made to be specialized for each and individual architecture
  template<typename T, std::ptrdiff_t Cardinal>
  inline constexpr emulated_ hardware_abi_of{};

  template<typename T>
  using expected_abi_t = decltype(_::hardware_abi_of<T, eve::current_abi_type::template expected_cardinal<T>>);

  //================================================================================================
  // Checks if a Type is supported on a given architecture or if we should emulate it
  
  // Specializable trait, specific architecture requirements are supported 
  template<typename T>
  inline constexpr bool should_emulate_v = false;

  template<typename T>
  concept should_emulate = !eve::product_type<T> &&
  (     !supports_simd 
    ||  !supported_simd_type<T> 
    ||  std::same_as<eve::_::expected_abi_t<T>, emulated_>
    ||  should_emulate_v<T>);

  //================================================================================================
  // Checks if a Type has a base abi so that we can aggregate native registers 

  // Specializable trait for architectures supporting native aggregation like riscv
  template<typename T, std::ptrdiff_t Cardinal>
  inline constexpr bool should_aggregate_v = (width_in_bits<T,Cardinal> > spy::simd_instruction_set.width );

  template<typename T, std::ptrdiff_t Cardinal>
  concept should_aggregate = !eve::product_type<T> && !should_emulate<T> && 
  (Cardinal > eve::current_abi_type::template expected_cardinal<T>) 
   && should_aggregate_v<T,Cardinal>;

  //================================================================================================
  // Select Software ABI from Type x Cardinal combo depending on type properties
  template<typename T, std::ptrdiff_t Cardinal>
  inline constexpr auto software_abi_of = _::hardware_abi_of<T,Cardinal>;

  template<typename T, std::ptrdiff_t Cardinal>
  inline constexpr auto software_abi_of<logical<T>,Cardinal> = software_abi_of<T, Cardinal>;

  template<typename T, std::ptrdiff_t Cardinal>
  requires ( eve::product_type<T> )
  inline constexpr auto software_abi_of<T,Cardinal> = bundle_{};

  template<typename T, std::ptrdiff_t Cardinal>
  requires( should_emulate<T> )
  inline constexpr auto software_abi_of<T,Cardinal> = emulated_{};

  template<typename T, std::ptrdiff_t Cardinal>
  requires( should_aggregate<T,Cardinal> ) 
  inline constexpr auto software_abi_of<T,Cardinal> = aggregated_{};
}

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
  template<typename Type, typename Lanes>
  using abi_t = /* Implementation defined */; 
#else
  template<typename Type, typename Lanes>
  requires( _::arithmetic_<Type> || eve::product_type<Type> || _::is_logical_<Type> )
  using abi_t = std::remove_cvref_t<decltype(_::software_abi_of<translate_t<Type>, Lanes::value>)>; 
#endif
}
