//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"
#include <eve/detection.hpp>
#include <iostream>
#include <iomanip>

TTS_CASE("Static detections of API")
{
  std::cout << "========================\n";
  std::cout << "Current API: " << eve::current_api << "\n";
  std::cout << "========================\n";
  std::cout << "X86-like SIMD extensions\n";
  std::cout << "SSE2        : " << std::boolalpha << (eve::current_api >= eve::sse2  ) << "\n";
  std::cout << "SSE3        : " << std::boolalpha << (eve::current_api >= eve::sse3  ) << "\n";
  std::cout << "SSSE3       : " << std::boolalpha << (eve::current_api >= eve::ssse3 ) << "\n";
  std::cout << "SSE4.1      : " << std::boolalpha << (eve::current_api >= eve::sse4_1) << "\n";
  std::cout << "SSE4.2      : " << std::boolalpha << (eve::current_api >= eve::sse4_2) << "\n";
  std::cout << "AVX         : " << std::boolalpha << (eve::current_api >= eve::avx   ) << "\n";
  std::cout << "FMA3        : " << std::boolalpha << eve::supports_fma3                << "\n";
  std::cout << "AVX2        : " << std::boolalpha << (eve::current_api >= eve::avx2  ) << "\n";
  std::cout << "AVX512      : " << std::boolalpha << (eve::current_api >= eve::avx512) << "\n";
  std::cout << "AVX512bw    : " << std::boolalpha << eve::supports_avx512bw            << "\n";
  std::cout << "AVX512cd    : " << std::boolalpha << eve::supports_avx512cd            << "\n";
  std::cout << "AVX512dq    : " << std::boolalpha << eve::supports_avx512dq            << "\n";
  std::cout << "AVX512ifma  : " << std::boolalpha << eve::supports_avx512ifma          << "\n";
  std::cout << "AVX512pf    : " << std::boolalpha << eve::supports_avx512pf            << "\n";
  std::cout << "AVX512vl    : " << std::boolalpha << eve::supports_avx512vl            << "\n";
  std::cout << "AVX512pop   : " << std::boolalpha << eve::supports_avx512popcntdq_     << "\n";
  std::cout << "AVX5124fma  : " << std::boolalpha << eve::supports_avx512_4fmaps_      << "\n";
  std::cout << "AVX512vnniw : " << std::boolalpha << eve::supports_avx512vnniw_        << "\n";
  std::cout << "AVX512vbmi  : " << std::boolalpha << eve::supports_avx512vbmi_         << "\n";
  std::cout << "AVX512bf16  : " << std::boolalpha << eve::supports_avx512bf16_         << "\n";
  std::cout << "AVX512bitalg: " << std::boolalpha << eve::supports_avx512bitalg_       << "\n";
  std::cout << "AVX512vbmi2 : " << std::boolalpha << eve::supports_avx512vbmi2_        << "\n";
  std::cout << "AVX512vnni  : " << std::boolalpha << eve::supports_avx512vnni_         << "\n";
  std::cout << "AVX512vpint : " << std::boolalpha << eve::supports_avx512vpintersect_  << "\n";
  std::cout << "\n";
  std::cout << "========================\n";
  std::cout << "PPC SIMD extensions\n";
  std::cout << "VSX   : " << std::boolalpha << (eve::current_api >= eve::vsx   ) << "\n";
  std::cout << "VMX   : " << std::boolalpha << (eve::current_api >= eve::vmx   ) << "\n";
  std::cout << "\n";
  std::cout << "========================\n";
  std::cout << "ARM SIMD extensions\n";
  std::cout << "NEON  : " << std::boolalpha << (eve::current_api >= eve::neon   ) << "\n";
  std::cout << "ASIMD : " << std::boolalpha << (eve::current_api >= eve::asimd  )  << "\n";
  std::cout << "\n";

  TTS_PASS("All static detections - done");
};

TTS_CASE("Dynamic detections of API")
{
  std::cout << "========================\n";
  std::cout << "Current API: " << eve::current_api << "\n";
  std::cout << "========================\n";
  std::cout << "X86-like SIMD extensions\n";
  std::cout << "SSE2   : " << std::boolalpha << eve::is_supported(eve::sse2) << "\n";
  std::cout << "SSE3   : " << std::boolalpha << eve::is_supported(eve::sse3) << "\n";
  std::cout << "SSSE3  : " << std::boolalpha << eve::is_supported(eve::ssse3) << "\n";
  std::cout << "SSE4.1 : " << std::boolalpha << eve::is_supported(eve::sse4_1) << "\n";
  std::cout << "SSE4.2 : " << std::boolalpha << eve::is_supported(eve::sse4_2) << "\n";
  std::cout << "AVX    : " << std::boolalpha << eve::is_supported(eve::avx) << "\n";
  std::cout << "FMA3   : " << std::boolalpha << eve::is_supported(eve::fma3) << "\n";
  std::cout << "AVX2   : " << std::boolalpha << eve::is_supported(eve::avx2) << "\n";
  std::cout << "AVX512 : " << std::boolalpha << eve::is_supported(eve::avx512) << "\n";
  std::cout << "\n";
  std::cout << "========================\n";
  std::cout << "PPC SIMD extensions\n";
  std::cout << "VMX   : " << std::boolalpha << eve::is_supported(eve::vmx) << "\n";
  std::cout << "VSX   : " << std::boolalpha << eve::is_supported(eve::vsx) << "\n";
  std::cout << "\n";
  std::cout << "========================\n";
  std::cout << "ARM SIMD extensions\n";
  std::cout << "NEON  : " << std::boolalpha << eve::is_supported(eve::neon) << "\n";
  std::cout << "ASIMD : " << std::boolalpha << eve::is_supported(eve::asimd) << "\n";

  TTS_PASS("All dynamic detections - done");
};
