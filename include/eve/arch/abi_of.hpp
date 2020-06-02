//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>
#include <eve/arch/tags.hpp>

namespace eve
{
  template<typename T> struct logical;

  //================================================================================================
  // Select ABI from Type x Cardinal combo
  template<typename Type, int Cardinal> struct abi_of
  {
    static constexpr auto find()
    {
      if constexpr(supports_simd)
      {
        constexpr auto width  = sizeof(Type) * Cardinal;
        constexpr bool f64    = std::is_same_v<Type,double>;

        if constexpr( spy::simd_instruction_set == spy::x86_simd_ )
        {
               if constexpr( width <= 16) return sse_{};
          else if constexpr( width == 32) return avx_{};
          else                            return aggregated_{};
        }
        else if constexpr( spy::simd_instruction_set == spy::vmx_ )
        {
          if constexpr(!f64 && width <= 16) return ppc_{};
          else                              return emulated_{};
        }
        else if constexpr( spy::simd_instruction_set == spy::vsx_ )
        {
          if constexpr(width <= 16) return ppc_{};
          else                      return emulated_{};
        }
        else if constexpr( spy::simd_instruction_set == spy::arm_simd_ )
        {
          if constexpr( spy::supports::aarch64_ )
          {
            if constexpr(width <= 8)       return neon64_{};
            else if constexpr(width == 16) return neon128_{};
            else                           return emulated_{};
          }
          else
          {
            if constexpr(!f64 && width <= 8)       return neon64_{};
            else if constexpr(!f64 && width == 16) return neon128_{};
            else                                   return emulated_{};
          }
        }
        else
        {
          return emulated_{};
        }
      }
      else
      {
        return emulated_{};
      }
    }

    using type = decltype(find());
  };

  //================================================================================================
  // ABI for logical<T>
  template<typename Type, int Cardinal>
  struct abi_of<logical<Type>, Cardinal> : abi_of<Type, Cardinal> {};

  //================================================================================================
  // Typename shortcut
  template<typename Type, int Cardinal>
  using abi_of_t = typename abi_of<Type, Cardinal>::type;
}

