//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSE2_ABI_OF_HPP_INCLUDED
#define EVE_ARCH_X86_SSE2_ABI_OF_HPP_INCLUDED

#include <eve/arch/x86/sse2/tags.hpp>
#include <eve/arch/abi_of.hpp>
#include <type_traits>

namespace eve { namespace ext
{
  template<int N> struct abi_of<double, N, std::enable_if_t<(N<=2)>>  { using type = ::eve::sse_; };
  template<int N> struct abi_of<float , N, std::enable_if_t<(N<=4)>>  { using type = ::eve::sse_; };

  // float maps to __m128
  template<typename T, int N>
  struct abi_of < T, N
                , std::enable_if_t<std::is_integral_v<T> && (N <= 16/sizeof(T))>
                >
  {
    using type = ::eve::sse_;
  };
} }

#endif
