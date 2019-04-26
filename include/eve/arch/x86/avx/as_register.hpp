//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_AVX_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_X86_AVX_AS_REGISTER_HPP_INCLUDED

#include <eve/arch/x86/avx/tags.hpp>
#include <eve/ext/as_register.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  struct logical;

  namespace ext
  {
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

    // float maps to __m256
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
  }
}

#endif
