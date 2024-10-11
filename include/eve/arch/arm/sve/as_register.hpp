//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/predef.hpp>
#include <eve/traits/as_integer.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  struct logical;
}

namespace eve
{
  template<typename T, typename N>
  consteval auto find_register_type(as<T>, N, sve_abi auto ABI)
  {
    constexpr auto width = sizeof(Type) * Size::value * 8;

    if constexpr(width <= __ARM_FEATURE_SVE_BITS)
    {
      constexpr bool signed_v = std::is_signed_v<Type>;

      if constexpr (std::is_same_v<Type,float>)
      {
        using type = svfloat32_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
        return type{};
      }
      else if constexpr (std::is_same_v<Type,double>)
      {
        using type = svfloat64_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
        return type{};
      }
      else if constexpr (signed_v && sizeof(Type) == 1)
      {
        using type = svint8_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
        return type{};
      }
      else if constexpr (signed_v && sizeof(Type) == 2)
      {
        using type = svint16_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
        return type{};
      }
      else if constexpr (signed_v && sizeof(Type) == 4)
      {
        using type = svint32_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
        return type{};
      }
      else if constexpr (signed_v && sizeof(Type) == 8)
      {
        using type = svint64_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
        return type{};
      }
      else if constexpr (!signed_v && sizeof(Type) == 1)
      {
        using type = svuint8_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
        return type{};
      }
      else if constexpr (!signed_v && sizeof(Type) == 2)
      {
        using type = svuint16_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
        return type{};
      }
      else if constexpr (!signed_v && sizeof(Type) == 4)
      {
        using type = svuint32_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
        return type{};
      }
      else if constexpr (!signed_v && sizeof(Type) == 8)
      {
        using type = svuint64_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
        return type{};
      }
    }
  }

  // ---------------------------------------------------------------------------------------------
  // logical cases
  template<typename T, typename N>
  consteval auto find_register_type(as_logical<T>, N, sve_abi auto ABI)
  {
    constexpr auto width = sizeof(Type)*Size::value*8;

    if constexpr (width <= __ARM_FEATURE_SVE_BITS)
    {
      using type = svbool_t __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));
      return type{};
    }
  }
}
