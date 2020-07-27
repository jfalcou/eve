//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/x86/tags.hpp>
#include <cstddef>

namespace eve
{
  // SSE ABI
  template<> struct limits<eve::sse2_>
  {
    static constexpr std::size_t bits           = 128;
    static constexpr std::size_t bytes          = 16;
    static constexpr bool        is_bit_logical = true;

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);
  };

  template<> struct limits<eve::sse3_>    : limits<eve::sse2_>  {};
  template<> struct limits<eve::ssse3_>   : limits<eve::sse2_>  {};
  template<> struct limits<eve::sse4_1_>  : limits<eve::sse2_>  {};
  template<> struct limits<eve::sse4_2_>  : limits<eve::sse2_>  {};

  // AVX ABI
  template<> struct limits<eve::avx_>
  {
    static constexpr std::size_t bits           = 256;
    static constexpr std::size_t bytes          = 32;
    static constexpr bool        is_bit_logical = true;

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);
  };

  template<> struct limits<eve::avx2_> : limits<eve::avx_> {};

  // TODO: AVX512 ABI
}

