//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/wasm/predef.hpp>

#include <type_traits>

namespace eve
{
template<typename T> struct logical;
struct wasm_128_;
}

#if defined(EVE_HW_WASM)

namespace eve
{
// Check the types are fine then return *the* WASM SIMD type: v128_t
template<typename Type, typename Size> struct as_register<Type, Size, eve::wasm_128_>
{
  static constexpr auto find()
  {
    constexpr auto width = sizeof(Type) * Size::value;
    if constexpr( width <= 16 )
    {
      if constexpr( std::is_same_v<Type, double> ) return v128_t {};
      else if constexpr( std::is_same_v<Type, float> ) return v128_t {};
      else if constexpr( std::is_integral_v<Type> ) return v128_t {};
    }
  }

  using type = decltype(find());
  static_assert(!std::is_void_v<type>, "[eve WASM] - Type is not usable in a SIMD register");
};

// logical uses same registers
template<typename T, typename Size>
struct as_logical_register<T, Size, eve::wasm_128_> : as_register<T, Size, eve::wasm_128_>
{};
}

#endif
