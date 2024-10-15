
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
  static constexpr bool value = eve::detail::is_one_of<eve::element_type_t<Type>>(
      eve::detail::types<std::int8_t, std::uint16_t, float, double> {});
};

#ifdef SPY_SIMD_IS_RISCV_FIXED_RVV
template<typename types_to_filter>
using simd_types_for_compress = tts::filter<rvv_compress_filter, types_to_filter>::type;
#else
template<typename types_to_filter> using simd_types_for_compress = types_to_filter;
#endif
