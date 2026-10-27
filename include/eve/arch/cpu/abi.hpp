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
#include <eve/types/float16.hpp>
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
  // Select Hardware ABI from Type x width combo
  // Emulated is the default : used wether we do not have a native register or if there is no simd

  // hardward_abi_of is made to be specialized for each and individual architecture
  template<typename T, std::ptrdiff_t width>
  extern emulated_ hardware_abi_of;

  template<typename T>
  using expected_abi_t = decltype(_::hardware_abi_of<T, eve::current_abi_type::template expected_width<T>>);

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
  template<typename T, std::ptrdiff_t width>
  inline constexpr bool should_aggregate_v = (width_in_bits<T,width> > spy::simd_instruction_set.width );

  template<typename T, std::ptrdiff_t width>
  concept should_aggregate = !eve::product_type<T> && !should_emulate<T> &&
  (width > eve::current_abi_type::template expected_width<T>)
   && should_aggregate_v<T,width>;

  //================================================================================================
  // Select Software ABI from Type x width combo depending on type properties
  template<typename T, std::ptrdiff_t width>
  extern decltype(_::hardware_abi_of<T,width>) software_abi_of;

  template<typename T, std::ptrdiff_t width>
  requires ( eve::product_type<T> )
  extern bundle_ software_abi_of<T,width>;

  template<typename T, std::ptrdiff_t width>
  requires( should_emulate<T> )
  extern emulated_ software_abi_of<T,width> ;

  template<typename T, std::ptrdiff_t width>
  requires( should_aggregate<T,width> )
  extern aggregated_ software_abi_of<T,width>;

  template<typename T, std::ptrdiff_t width>
  extern decltype(software_abi_of<T, width>) software_abi_of<logical<T>,width>;
}
