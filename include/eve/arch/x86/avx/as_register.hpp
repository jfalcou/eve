//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_AVX_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_X86_AVX_AS_REGISTER_HPP_INCLUDED

#include <eve/arch/x86/avx/tags.hpp>
#include <eve/ext/as_register.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve { namespace ext
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
} }

#endif
