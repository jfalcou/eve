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
#include <eve/deps/kumi.hpp>

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
  
  //================================================================================================
  // Select Hardware ABI from Type x Cardinal combo
  template<typename Type, std::ptrdiff_t Cardinal> consteval auto hardware_abi_of()
  {
    constexpr bool f16                  = std::same_as<Type, eve::float16_t>;
    constexpr bool supported_simd_type  = !f16 || _::supports_fp16_vector_conversion;

    if constexpr ( supports_simd && supported_simd_type )
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
      else if constexpr( spy::simd_instruction_set >= spy::vsx_ )
      {
        if constexpr(width <= 16) return ppc_{};
        else                      return emulated_{};
      }
      else if constexpr( spy::simd_instruction_set >= spy::vmx_ )
      {
        if constexpr(!f64 && width <= 16) return ppc_{};
        else                              return emulated_{};
      }
      else if constexpr( (spy::simd_instruction_set == spy::fixed_sve_) || (spy::simd_instruction_set == spy::fixed_sve2_) )
      {
             if constexpr(spy::simd_instruction_set.width == 128) return arm_sve_128_{};
        else if constexpr(spy::simd_instruction_set.width == 256) return arm_sve_256_{};
        else if constexpr(spy::simd_instruction_set.width == 512) return arm_sve_512_{};
        else                                                      return emulated_{};
      }
      else if constexpr( spy::simd_instruction_set == spy::arm_simd_ )
      {
        if constexpr( spy::simd_instruction_set == spy::asimd_ )
        {
               if constexpr(width <=  8) return arm_64_{};
          else if constexpr(width == 16) return arm_128_{};
          else                           return emulated_{};
        }
        else
        {
               if constexpr (f16 || f64 ) return emulated_{};
          else if constexpr (width <=  8) return arm_64_{};
          else if constexpr (width == 16) return arm_128_{};
          else                            return emulated_{};
        }
      }
      else if constexpr( (spy::simd_instruction_set == spy::fixed_rvv_) && (spy::simd_instruction_set.width >= 64) )
      {
        return riscv_{};
      }
      else return emulated_{};
    }
    else return emulated_{};
  }

  // Types that are too big and are not emulated require aggregation 
  template<typename ABI, typename T, std::ptrdiff_t Size>
  inline constexpr bool require_aggregation = (Size > eve::current_abi_type::template expected_cardinal<T>) && !std::same_as<ABI, eve::emulated_>;

  //================================================================================================
  // Select Software ABI from Type x Cardinal combo depending on type properties
  template<typename T, std::ptrdiff_t Cardinal> consteval auto software_abi_of()
  {
         if constexpr ( eve::_::is_logical<T> ) return software_abi_of<typename T::value_type, Cardinal>();
    else if constexpr ( eve::product_type<T>  ) return bundle_{};
    else
    {
      constexpr auto abi = hardware_abi_of<T,Cardinal>();
      using abi_type = std::remove_cvref_t<decltype(abi)>;
      if constexpr ( require_aggregation<abi_type, T, Cardinal> ) return aggregated_{};
      else                                                        return abi;
    }
  }
}

namespace eve
{
  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!
  //! @struct abi
  //! @brief Find proper ABI for Type/Lanes pair
  //!
  //! Computes the best ABI to use to efficiently store `Lanes` elements of type `Type` in
  //! order to use SIMD implementations.
  //!
  //! @tparam Type  Type of the element to store
  //! @tparam Lanes Number of elements to store
  //!
  //! #### Member types
  //!
  //! |Name   | Definition                                                  |
  //! |:------|:------------------------------------------------------------|
  //! |`type` | The tag for the ABI to use for current Type/lanes selection |
  //!
  //! <br/>
  //! #### Helper types
  //!
  //! @code{.cpp}
  //! template<typename Type, typename Lanes>
  //! using abi_t = typename abi<Type,Lanes>::type;
  //! @endcode
  //!
  //! @}
  //================================================================================================
  template<typename Type, typename Lanes> struct abi{};

  template<typename Type, typename Lanes> 
  requires( eve::product_type<Type> || _::arithmetic<Type> || _::is_logical<Type> )
  struct abi<Type, Lanes>
  {
    using type = decltype(_::software_abi_of<Type, Lanes::value>());
  };

  // Type short-cut
  template<typename Type, typename Lanes>
  using abi_t = typename abi<Type,Lanes>::type;

}
