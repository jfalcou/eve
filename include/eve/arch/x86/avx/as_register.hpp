//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_AVX_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_X86_AVX_AS_REGISTER_HPP_INCLUDED

#include <eve/arch/x86/avx/tags.hpp>
#include <eve/ext/as_register.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve
{
  template<typename T> struct logical;

  namespace ext
  {
    template<> struct as_register<double, 4, eve::avx_> { using type = __m256d; };
    template<> struct as_register<float , 8, eve::avx_> { using type = __m256;  };

    // float maps to __m256
    template<typename T, int N>
    struct as_register< T, N, eve::avx_
                      , std::enable_if_t<std::is_integral_v<T> && (N == 32/sizeof(T))>
                      >
    {
      using type = __m256i;
    };

    // logical uses same registers
    template<typename T, int N>
    struct as_register< logical<T>, N, eve::avx_> : as_register<T,N,eve::avx_>
    {};
  }
}

#endif
