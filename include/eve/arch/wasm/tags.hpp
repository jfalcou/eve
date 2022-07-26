//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/cpu/tags.hpp>
#include <eve/arch/wasm/predef.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/spy.hpp>

namespace eve
{
//================================================================================================
// ABI tags for all X86 bits SIMD registers
//================================================================================================
template<std::size_t Size, bool Logical> struct wasm_abi_
{
  static constexpr std::size_t bits            = Size;
  static constexpr std::size_t bytes           = Size / 8;
  static constexpr bool        is_wide_logical = Logical;

  template<typename Type>
  static constexpr bool is_full = ((Type::size() * sizeof(typename Type::value_type)) >= 16);

  template<typename Type> static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);

  template<typename Type> static constexpr std::size_t fundamental_cardinal = 16 / sizeof(Type);
};

struct wasm_128_ : wasm_abi_<128, true>
{};

//================================================================================================
// Dispatching tag for WASM SIMD implementation
//================================================================================================
struct simd128_ : simd_api<simd_, spy::simd128_>
{};

//================================================================================================
// WASM SIMD extension tag objects
//================================================================================================
inline constexpr simd128_ simd128 = {};

//================================================================================================
// WASM ABI concept
//================================================================================================
template<typename T>
concept wasm_abi = detail::is_one_of<T>(detail::types<wasm_128_> {});
}
