//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSE2_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_X86_SSE2_AS_REGISTER_HPP_INCLUDED

#include <eve/arch/x86/sse2/tags.hpp>
#include <eve/ext/as_register.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve { namespace ext
{
  // double maps to __m128d
  template<int N> struct as_register<double, N, eve::sse_, std::enable_if_t<(N<=2)>>
  {
    using type = __m128d;
  };

  // float maps to __m128
  template<int N> struct as_register<float, N, eve::sse_, std::enable_if_t<(N<=4)>>
  {
    using type = __m128;
  };

  // float maps to __m128
  template<typename T, int N>
  struct as_register< T, N, eve::sse_
                    , std::enable_if_t<std::is_integral_v<T> && (N <= 16/sizeof(T))>
                    >
  {
    using type = __m128i;
  };
} }

#endif
