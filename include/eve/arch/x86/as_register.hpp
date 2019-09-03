//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_X86_AS_REGISTER_HPP_INCLUDED

#include <eve/arch/x86/predef.hpp>
#include <eve/ext/as_register.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  struct logical;
  struct sse_;
  struct avx_;
}

namespace eve::ext
{
#if EVE_HW_X86 >= EVE_SSE2_VERSION
  template<typename Size>
  struct as_register<double, Size, eve::sse_, std::enable_if_t<(Size::value <= 2)>>
  {
    using type = __m128d;
  };

  template<typename Size>
  struct as_register<float, Size, eve::sse_, std::enable_if_t<(Size::value <= 4)>>
  {
    using type = __m128;
  };

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

#endif

#if EVE_HW_X86 >= EVE_AVX_VERSION
  template<typename Size>
  struct as_register<double, Size, eve::avx_>
  {
    using type = __m256d;
  };

  template<typename Size>
  struct as_register<float, Size, eve::avx_>
  {
    using type = __m256;
  };

  template<typename T, typename Size>
  struct as_register<T,
                     Size,
                     eve::avx_,
                     std::enable_if_t<std::is_integral_v<T> && (Size::value == 32 / sizeof(T))>>
  {
    using type = __m256i;
  };

  // logical uses same registers
  template<typename T, typename Size>
  struct as_register<logical<T>, Size, eve::avx_> : as_register<T, Size, eve::avx_>
  {
  };
#endif

}

#endif
