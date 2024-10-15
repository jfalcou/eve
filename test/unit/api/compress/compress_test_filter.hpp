
//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once
#include "test.hpp"
template<typename Type> struct rvv_compress_filter
{
  static consteval bool is_enabled()
  {
    // For vlen = 128, we test types with all integer up to lmul==1
    constexpr auto bit_size = 128;
    using scalar_t          = typename Type::value_type;
    if( sizeof(Type) <= bit_size / 8 && std::is_integral_v<scalar_t> ) return true;
    constexpr auto cardinal          = eve::cardinal_v<Type>;
    constexpr auto expected_cardinal = eve::expected_cardinal_v<scalar_t>;
    // and double
    if( sizeof(scalar_t) != 8 || !std::is_floating_point_v<scalar_t> ) return false;
    // for expected cardinal (lmul==8)
    if( expected_cardinal == cardinal ) return true;
    // for combined type
    if( 2 * expected_cardinal == cardinal ) return true;
    return false;
  }

  static constexpr bool value = is_enabled();
};

#ifdef SPY_SIMD_IS_RISCV_FIXED_RVV
template<typename types_to_filter>
using simd_types_for_compress = tts::filter<rvv_compress_filter, types_to_filter>::type;

template<typename T>
using simd_type_cardinal_for_compress_tuple =
    std::conditional_t<T::cardinal_type::value <= eve::expected_cardinal_v<double> * 2,
                       typename T::cardinal_type,
                       typename eve::expected_cardinal_t<double>>;
#else
template<typename types_to_filter> using simd_types_for_compress = types_to_filter;
template<typename T> using simd_type_cardinal_for_compress_tuple = typename T::cardinal_type;
#endif
