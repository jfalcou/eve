//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
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
               if constexpr( width <= 16) return x86_128_{};
          else if constexpr( width == 32) return x86_256_{};
          else if constexpr( width == 64) return x86_512_{};
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
          if constexpr( spy::simd_instruction_set == spy::asimd_ )
          {
            if constexpr(width <= 8)       return arm_64_{};
            else if constexpr(width == 16) return arm_128_{};
            else                           return emulated_{};
          }
          else
          {
            if constexpr(!f64 && width <= 8)       return arm_64_{};
            else if constexpr(!f64 && width == 16) return arm_128_{};
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
