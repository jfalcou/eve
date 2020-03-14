//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_X86_AS_REGISTER_HPP_INCLUDED

#include <eve/arch/x86/predef.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  struct logical;
  struct sse_;
  struct avx_;
}

#if defined(EVE_HW_X86)

namespace eve
{
  template<typename Type, typename Size>
  struct as_register<Type, Size, eve::sse_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(Type)*Size::value;
      if constexpr(width <= 16)
      {
              if constexpr(std::is_same_v<Type,double> ) return  __m128d{};
        else  if constexpr(std::is_same_v<Type,float > ) return  __m128{};
        else  if constexpr(std::is_integral_v<Type>    ) return  __m128i{};
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve x86] - Type is not usable in a SIMD register");
  };

  template<typename Type, typename Size>
  struct as_register<Type, Size, eve::avx_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(Type)*Size::value;
      if constexpr(width == 32)
      {
              if constexpr(std::is_same_v<Type,double> ) return __m256d{};
        else  if constexpr(std::is_same_v<Type,float > ) return __m256{};
        else  if constexpr(std::is_integral_v<Type>    ) return __m256i{};
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve x86] - Type is not usable in a SIMD register");
  };

  // logical uses same registers
  template<typename T, typename Size>
  struct as_register<logical<T>, Size, eve::sse_> : as_register<T, Size, eve::sse_>
  {
  };

  template<typename T, typename Size>
  struct as_register<logical<T>, Size, eve::avx_> : as_register<T, Size, eve::avx_>
  {
  };
}
#endif

#if defined(SPY_COMPILER_IS_GNUC)
#  pragma GCC diagnostic pop
#endif

#endif
