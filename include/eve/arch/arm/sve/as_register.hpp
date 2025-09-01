//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/predef.hpp>
#include <eve/arch/float16.hpp>
#include <eve/traits/as_integer.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  struct logical;
}

namespace eve
{
  template<typename T, typename N, sve_abi ABI>
  consteval auto find_register_type(as<T>, N, ABI)
  {
    constexpr auto width = sizeof(T) * N::value * 8;

    if constexpr (width <= __ARM_FEATURE_SVE_BITS)
    {
      if constexpr (std::same_as<T, eve::float16_t>)
      {
        using type = svfloat16_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
        return type{};
      }
      else if constexpr (std::same_as<T, float>)
      {
        using type = svfloat32_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
        return type{};
      }
      else if constexpr (std::same_as<T, double>)
      {
        using type = svfloat64_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
        return type{};
      }
      else if constexpr (std::signed_integral<T>)
      {
        if constexpr (sizeof(T) == 1)
        {
          using type = svint8_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
          return type{};
        }
        else if constexpr (sizeof(T) == 2)
        {
          using type = svint16_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
          return type{};
        }
        else if constexpr (sizeof(T) == 4)
        {
          using type = svint32_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
          return type{};
        }
        else if constexpr (sizeof(T) == 8)
        {
          using type = svint64_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
          return type{};
        }
      }
      else if constexpr (std::unsigned_integral<T>)
      {
        if constexpr (sizeof(T) == 1)
        {
          using type = svuint8_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
          return type{};
        }
        else if constexpr (sizeof(T) == 2)
        {
          using type = svuint16_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
          return type{};
        }
        else if constexpr (sizeof(T) == 4)
        {
          using type = svuint32_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
          return type{};
        }
        else if constexpr (sizeof(T) == 8)
        {
          using type = svuint64_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
          return type{};
        }
      }
    }
  }

  // ---------------------------------------------------------------------------------------------
  // logical cases
  template<typename T, typename N>
  consteval auto find_logical_register_type(as<T>, N, sve_abi auto)
  {
    constexpr size_t width = sizeof(T) * N::value * 8;

    if constexpr (width <= __ARM_FEATURE_SVE_BITS)
    {
      using type = svbool_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
      return type{};
    }
  }
}
