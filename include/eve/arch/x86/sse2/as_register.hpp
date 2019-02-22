//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSE2_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_X86_SSE2_AS_REGISTER_HPP_INCLUDED

#include <eve/arch/x86/sse2/tags.hpp>
#include <eve/ext/as_register.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  struct logical;

  namespace ext
  {
    // double maps to __m128d
    template<typename Size>
    struct as_register<double, Size, eve::sse_, std::enable_if_t<(Size::value <= 2)>>
    {
      using type = __m128d;
    };

    // float maps to __m128
    template<typename Size>
    struct as_register<float, Size, eve::sse_, std::enable_if_t<(Size::value <= 4)>>
    {
      using type = __m128;
    };

    // float maps to __m128
    template<typename T, typename Size>
    struct as_register<T,
                       Size,
                       eve::sse_,
                       std::enable_if_t<std::is_integral_v<T> && (Size::value <= 16 / sizeof(T))>>
    {
      using type = __m128i;
    };

    // logical uses same registers
    template<typename T, typename Size>
    struct as_register<logical<T>, Size, eve::sse_> : as_register<T, Size, eve::sse_>
    {
    };
  }
}

#endif
