//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/arch/spec.hpp>
#include <eve/arch/float16.hpp>
#include <eve/detail/kumi.hpp>

#include <concepts>
#include <type_traits>

namespace eve
{
    template<typename T> struct logical;
}

namespace eve::_
{
  namespace
  {
    template<typename T>
    inline constexpr bool is_logical = false;

    template<typename T>
    inline constexpr bool is_logical<eve::logical<T>> = true;
    
    template<typename T> concept arithmetic = std::is_arithmetic_v<T> || std::same_as<T, eve::float16_t>;
  }
  
  using no_hardware_abi = void;

  //================================================================================================
  // Select Hardware ABI from Type x Cardinal combo
  // Returns eve::_::no_hardware_abi if there is no native register for the type 
  template<typename Type, std::ptrdiff_t Cardinal> consteval auto hardware_abi_of()
  {
    constexpr auto width = sizeof(Type) * Cardinal * 8;

          // Risc-V handles register aggregating up to max_lmul natively
         if constexpr( width > spy::simd_instruction_set.width && spy::simd_instruction_set != spy::fixed_rvv_) return;
    else if constexpr( spy::simd_instruction_set == spy::x86_simd_ )
    {
           if constexpr( width <= 128 ) return x86_128_{};
      else if constexpr( width == 256 ) return x86_256_{};
      else if constexpr( width == 512 ) return x86_512_{};
    }
    else if constexpr( spy::simd_instruction_set >= spy::vsx_ && width <= 128 ) return ppc_{};
    else if constexpr( spy::simd_instruction_set >= spy::vmx_ && width <= 128 ) return ppc_{};
    else if constexpr( (spy::simd_instruction_set == spy::fixed_sve_) || (spy::simd_instruction_set == spy::fixed_sve2_) )
    {
           if constexpr( spy::simd_instruction_set.width == 128 ) return arm_sve_128_{};
      else if constexpr( spy::simd_instruction_set.width == 256 ) return arm_sve_256_{};
      else if constexpr( spy::simd_instruction_set.width == 512 ) return arm_sve_512_{};
    }
    else if constexpr( spy::simd_instruction_set == spy::arm_simd_ )
    {
             if constexpr ( width <=  64 ) return arm_64_{};
        else if constexpr ( width == 128 ) return arm_128_{};
    }
    else if constexpr( (spy::simd_instruction_set == spy::fixed_rvv_) && spy::simd_instruction_set.width >= 64)  return riscv_{};
  }

  template<typename T>
  using expected_abi_t = decltype(_::hardware_abi_of<T, eve::current_abi_type::template expected_cardinal<T>>());

  //================================================================================================
  // Checks if a Type is supported on a given architecture or if we should emulate
  template<typename T> consteval bool should_emulate()
  {
    constexpr bool f16    = std::same_as<T, eve::float16_t>;
    constexpr bool f64    = std::same_as<T, double>;
    constexpr bool supported_simd_type = !f16 || _::supports_fp16_vector_conversion;
    
    if constexpr ( std::is_same_v<eve::current_abi_type, emulated_> ) return true;
    else if constexpr( !supports_simd || !supported_simd_type       ) return true; 
    else if constexpr( spy::simd_instruction_set >= spy::vmx_  &&           
                       spy::simd_instruction_set  < spy::vsx_       ) return f64; // no doubles on altivec
    else if constexpr( spy::simd_instruction_set == spy::arm_simd_  ) 
    {
      // 32bit arm does not support f16 nor f64
      return (spy::simd_instruction_set != spy::asimd_) && (f16 || f64); 
    }
    else return std::same_as<eve::_::expected_abi_t<T>, eve::_::no_hardware_abi>; 
  };

  //================================================================================================
  // Checks if a Type has a native abi so that we can aggregate registers 
  template<typename T, std::ptrdiff_t Cardinal> consteval bool should_aggregate()
  {
    constexpr bool native_register     = !std::same_as<eve::_::expected_abi_t<T>, eve::_::no_hardware_abi>; 
    constexpr bool require_aggregation = Cardinal > eve::current_abi_type::template expected_cardinal<T>;
    if constexpr( require_aggregation ) return native_register;
    else                                return false;
  };

  //================================================================================================
  // Select Software ABI from Type x Cardinal combo depending on type properties
  template<typename T, std::ptrdiff_t Cardinal> 
  requires( _::arithmetic<T> || eve::product_type<T> || _::is_logical<T> )
  consteval auto software_abi_of()
  { 
         if constexpr( eve::_::is_logical<T>          ) return software_abi_of<typename T::value_type, Cardinal>();
    else if constexpr( eve::product_type<T>           ) return bundle_{};
    else if constexpr( should_emulate<T>()            ) return emulated_{}; 
    else if constexpr( should_aggregate<T, Cardinal>()) return aggregated_{};
    else 
    {
      using abi = decltype(_::hardware_abi_of<T,Cardinal>());
      constexpr bool has_register = !std::same_as<abi, eve::_::no_hardware_abi>;
      
      if constexpr ( has_register ) return abi{};
      else                          return emulated_{};
    }
  }
}

namespace eve
{
  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!
  //! @typedef abi_t
  //! @brief Find proper ABI type for Type/Lanes pair
  //!
  //! Computes the best ABI to use to efficiently store `Lanes` elements of type `Type` in
  //! order to use SIMD implementations and returns it's type.
  //!
  //! @tparam Type  Type of the element to store
  //! @tparam Lanes Number of elements to store
  //!
  //! @}
  //================================================================================================
#if defined (EVE_DOXYGEN_INVOKED)
  template<typename Type, typename Lanes>
  using abi_t = /* Implementation defined */; 
#else
  template<typename Type, typename Lanes>
  requires( _::arithmetic<Type> || eve::product_type<Type> || _::is_logical<Type> )
  using abi_t = decltype(_::software_abi_of<translate_t<Type>, Lanes::value>()); 
#endif
}
