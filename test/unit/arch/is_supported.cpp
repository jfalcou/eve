//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================

#include <eve/arch/tags.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  std::cout << "X86-like SIMD extensions\n";
  std::cout << "========================\n";
  std::cout << "SSE2   : " << std::boolalpha << eve::is_supported(eve::sse2) << "\n";
  std::cout << "SSE3   : " << std::boolalpha << eve::is_supported(eve::sse3) << "\n";
  std::cout << "SSSE3  : " << std::boolalpha << eve::is_supported(eve::ssse3) << "\n";
  std::cout << "SSE4.1 : " << std::boolalpha << eve::is_supported(eve::sse4_1) << "\n";
  std::cout << "SSE4.2 : " << std::boolalpha << eve::is_supported(eve::sse4_2) << "\n";
  std::cout << "SSE4A  : " << std::boolalpha << eve::is_supported(eve::sse4a) << "\n";
  std::cout << "AVX    : " << std::boolalpha << eve::is_supported(eve::avx) << "\n";
  std::cout << "FMA3   : " << std::boolalpha << eve::is_supported(eve::fma3) << "\n";
  std::cout << "XOP    : " << std::boolalpha << eve::is_supported(eve::xop) << "\n";
  std::cout << "FMA4   : " << std::boolalpha << eve::is_supported(eve::fma4) << "\n";
  std::cout << "AVX2   : " << std::boolalpha << eve::is_supported(eve::avx2) << "\n";
  //std::cout << "AVX512   : " << std::boolalpha << eve::is_supported(eve::avx512) << "\n";

  std::cout << "\n";
  std::cout << "PPC SIMD extensions\n";
  std::cout << "========================\n";

  std::cout << "\n";
  std::cout << "ARM SIMD extensions\n";
  std::cout << "========================\n";

  return 0;
}
