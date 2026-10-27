//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/predef.hpp>
#include <eve/types/float16.hpp>
#include <eve/traits/as_integer.hpp>
#include <type_traits>

namespace eve::_
{
  // ---------------------------------------------------------------------------------------------
  // NEON 64
  template<typename T, width_type N> extern no_register<void> neon64_register;

  template<std::signed_integral T> extern int8x8_t  neon64_register<T, 8>;
  template<std::signed_integral T> extern int16x4_t neon64_register<T, 4>;
  template<std::signed_integral T> extern int32x2_t neon64_register<T, 2>;
  template<std::signed_integral T> extern int64x1_t neon64_register<T, 1>;

  template<std::unsigned_integral T> extern uint8x8_t  neon64_register<T, 8>;
  template<std::unsigned_integral T> extern uint16x4_t neon64_register<T, 4>;
  template<std::unsigned_integral T> extern uint32x2_t neon64_register<T, 2>;
  template<std::unsigned_integral T> extern uint64x1_t neon64_register<T, 1>;

  #ifdef SPY_SUPPORTS_FP16_VECTOR_CONVERSION
    template<width_type N> extern float16x4_t neon64_register<eve::float16_t, N>;
  #endif

  template<width_type N> extern float32x2_t neon64_register<float, N>;

  #if defined(SPY_SIMD_IS_ARM_ASIMD)
    template<width_type N> extern float64x1_t neon64_register<double, N>;
  #endif

  template<typename T, width_type N> requires( N <= 8 / sizeof(T))
  extern decltype(neon64_register<T, 8 / sizeof(T)>) as_register<T, N, eve::arm_64_>;

  template<typename T, width_type N> requires( N <= 8 / sizeof(T))
  extern decltype(neon64_register<as_integer_t<T, unsigned>, 8 / sizeof(T)>) as_logical_register<T, N, eve::arm_64_>;
  
  // ---------------------------------------------------------------------------------------------
  // NEON 128
  template<typename T, width_type N> extern no_register<void> neon128_register;

  template<std::signed_integral T> extern int8x16_t neon128_register<T, 16>;
  template<std::signed_integral T> extern int16x8_t neon128_register<T,  8>;
  template<std::signed_integral T> extern int32x4_t neon128_register<T,  4>;
  template<std::signed_integral T> extern int64x2_t neon128_register<T,  2>;

  template<std::unsigned_integral T> extern uint8x16_t neon128_register<T, 16>;
  template<std::unsigned_integral T> extern uint16x8_t neon128_register<T,  8>;
  template<std::unsigned_integral T> extern uint32x4_t neon128_register<T,  4>;
  template<std::unsigned_integral T> extern uint64x2_t neon128_register<T,  2>;

  #ifdef SPY_SUPPORTS_FP16_VECTOR_CONVERSION
    template<width_type N> extern float16x8_t neon128_register<eve::float16_t, N>;
  #endif

  template<width_type N> extern float32x4_t neon128_register<float, N>;

  #if defined(SPY_SIMD_IS_ARM_ASIMD)
    template<width_type N> extern float64x2_t neon128_register<double, N>;
  #endif
  
  template<typename T, width_type N> requires( N == 16 / sizeof(T))
  extern decltype(neon128_register<T,N>) as_register<T, N, eve::arm_128_>;

  template<typename T, width_type N> requires( N == 16 / sizeof(T))
  extern decltype(neon128_register<as_integer_t<T, unsigned>, N>) as_logical_register<T, N, eve::arm_128_>;
}
