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
  template<typename T, typename Size>
  struct as_register<T, Size, eve::sse_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(T)*Size::value;
      if constexpr(width <= 16)
      {
              if constexpr(std::is_same_v<T,double> ) return __m128d{};
        else  if constexpr(std::is_same_v<T,float > ) return __m128{};
        else  if constexpr(std::is_integral_v<T>    ) return __m128i{};
      }
    }

    using type = decltype(find());
  };

  template<typename T, typename Size>
  struct as_register<T, Size, eve::avx_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(T)*Size::value;
      if constexpr(width == 32)
      {
              if constexpr(std::is_same_v<T,double> ) return __m256d{};
        else  if constexpr(std::is_same_v<T,float > ) return __m256{};
        else  if constexpr(std::is_integral_v<T>    ) return __m256i{};
      }
    }

    using type = decltype(find());
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

#endif
