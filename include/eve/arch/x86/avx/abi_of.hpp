//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_AVX_ABI_OF_HPP_INCLUDED
#define EVE_ARCH_X86_AVX_ABI_OF_HPP_INCLUDED

#include <eve/arch/x86/avx/tags.hpp>
#include <eve/ext/abi_of.hpp>
#include <type_traits>

namespace eve { namespace ext
{
  template<> struct abi_of<double, 4>  { using type = ::eve::avx_; };
  template<> struct abi_of<float , 8>  { using type = ::eve::avx_; };

  template<typename T, int N>
  struct abi_of < T, N
                , std::enable_if_t<std::is_integral_v<T> && (N == 32/sizeof(T))>
                >
  {
    using type = ::eve::avx_;
  };
} }

#endif
