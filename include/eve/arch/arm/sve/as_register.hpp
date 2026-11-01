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
#include <concepts>
#include <cstddef>

namespace eve::_
{
  // ---------------------------------------------------------------------------------------------
  // Fixed-width SVE types
  using sve_f16_t  = svfloat16_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
  using sve_f32_t  = svfloat32_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
  using sve_f64_t  = svfloat64_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));

  using sve_s8_t   = svint8_t    __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
  using sve_s16_t  = svint16_t   __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
  using sve_s32_t  = svint32_t   __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
  using sve_s64_t  = svint64_t   __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));

  using sve_u8_t   = svuint8_t   __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
  using sve_u16_t  = svuint16_t  __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
  using sve_u32_t  = svuint32_t  __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
  using sve_u64_t  = svuint64_t  __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));

  using sve_bool_t = svbool_t    __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));

  // ---------------------------------------------------------------------------------------------
  // SVE
  template<typename T, std::size_t Size> extern no_register<void> sve_register;

  template<std::size_t S> extern sve_f16_t sve_register<eve::float16_t, S>;
  template<std::size_t S> extern sve_f32_t sve_register<float, S>;
  template<std::size_t S> extern sve_f64_t sve_register<double, S>;

  template<std::signed_integral T> extern sve_s8_t  sve_register<T, 1>;
  template<std::signed_integral T> extern sve_s16_t sve_register<T, 2>;
  template<std::signed_integral T> extern sve_s32_t sve_register<T, 4>;
  template<std::signed_integral T> extern sve_s64_t sve_register<T, 8>;

  template<std::unsigned_integral T> extern sve_u8_t  sve_register<T, 1>;
  template<std::unsigned_integral T> extern sve_u16_t sve_register<T, 2>;
  template<std::unsigned_integral T> extern sve_u32_t sve_register<T, 4>;
  template<std::unsigned_integral T> extern sve_u64_t sve_register<T, 8>;

  template<typename T, width_type N, sve_abi ABI> requires(sizeof(T) * N * 8 <= __ARM_FEATURE_SVE_BITS)
  extern decltype(sve_register<T, sizeof(T)>) as_register<T, N, ABI>;

  template<typename T, width_type N, sve_abi ABI> requires(sizeof(T) * N * 8 <= __ARM_FEATURE_SVE_BITS)
  extern sve_bool_t as_logical_register<T, N, ABI>;
}