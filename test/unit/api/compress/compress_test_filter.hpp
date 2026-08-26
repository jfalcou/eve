
//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once
#include "test.hpp"

template<typename T> struct rvv_compress_filter 
  : std::bool_constant<std::same_as<eve::element_type_t<T>, std::int8_t> 
                    || std::same_as<eve::element_type_t<T>, std::uint16_t>
                    || std::same_as<eve::element_type_t<T>, float>
                    || std::same_as<eve::element_type_t<T>, double>>
{};

#ifdef SPY_SIMD_IS_RISCV_FIXED_RVV
template<typename types_to_filter>
using simd_types_for_compress = tts::filter<rvv_compress_filter, types_to_filter>::type;
#else
template<typename types_to_filter> using simd_types_for_compress = types_to_filter;
#endif
