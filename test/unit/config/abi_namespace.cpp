//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <string>
#include <string_view>

namespace
{
#if defined(EVE_USE_BMI)
  constexpr bool has_bmi       = true;
#else
  constexpr bool has_bmi       = false;
#endif

#if defined(EVE_INCOMPLETE_AVX512_SUPPORT)
  constexpr bool incomplete_avx512 = true;
#else
  constexpr bool incomplete_avx512 = false;
#endif

#if defined(SPY_SIMD_IS_X86)
  constexpr bool is_x86        = true;
#else
  constexpr bool is_x86        = false;
#endif

#if defined(EVE_DISABLE_ASSERTS)
  constexpr bool asserts       = false;
#else
  constexpr bool asserts       = true;
#endif

  constexpr bool has_fma       = eve::platform::supports_hardware_fma;
  constexpr bool has_vbmi      = spy::supports::avx512::vbmi_;
  constexpr bool no_fp16       = !eve::_::supports_fp16_native_type;
  constexpr bool fp16_cvt      = eve::_::supports_fp16_vector_conversion;
  constexpr bool fp16_ops      = eve::_::supports_fp16_scalar_ops || eve::_::supports_fp16_vector_ops;
  constexpr bool has_denormals = eve::platform::supports_denormals;
  constexpr bool ieee          =  eve::platform::supports_nans && eve::platform::supports_infinites
                               && eve::platform::supports_negative_zero && has_denormals;

  constexpr int sve_bits =   std::same_as<eve::current_abi_type, eve::arm_sve_128_> ? 128
                           : std::same_as<eve::current_abi_type, eve::arm_sve_256_> ? 256
                           : std::same_as<eve::current_abi_type, eve::arm_sve_512_> ? 512
                           : 0;

  constexpr int rvv_bits = std::same_as<eve::current_abi_type, eve::riscv_>
                         ? eve::riscv_::bits / eve::riscv_::max_lmul
                         : 0;

  constexpr int avx512_subset_bits =  (spy::supports::avx512::bw_ ? 8 : 0)
                                   |  (spy::supports::avx512::cd_ ? 4 : 0)
                                   |  (spy::supports::avx512::dq_ ? 2 : 0)
                                   |  (spy::supports::avx512::vl_ ? 1 : 0);

  constexpr int option_bits =  (!eve::platform::supports_negative_zero ?  8 : 0)
                            |  (!eve::platform::supports_infinites     ?  4 : 0)
                            |  (!eve::platform::supports_nans          ?  2 : 0)
                            |  (!has_denormals                         ?  1 : 0);

  constexpr std::string_view ci_namespace()
  {
    using namespace eve;
         if constexpr( current_api == neon && has_fma && no_fp16 && !has_denormals              ) return asserts ? "DA" : "CA";
    else if constexpr( !ieee                                                                    ) return {};
    else if constexpr( current_api == undefined_simd && !has_fma && !no_fp16 && !fp16_cvt       ) return asserts ? "BA" : "AA";
    else if constexpr( current_api == sse2     && !has_fma && !no_fp16 && !fp16_cvt             ) return asserts ? "DA" : "CA";
    else if constexpr( current_api == sse2     && !has_fma &&  no_fp16                          ) return asserts ? "DY" : "CY";
    // clang-cl -msse4.2/-mavx/-mavx2/-march=skylake-avx512: unit.config.abi_namespace failed (abi_LY
    // vs abi_L): no native _Float16 on MSVC/clang-cl, and the rows below assume one.
    else if constexpr( is_x86 && no_fp16                                                     ) return {};
    else if constexpr( current_api == sse4_2   && !has_fma && !fp16_cvt                         ) return asserts ? "LA" : "KA";
    else if constexpr( current_api == avx      && !has_fma && !fp16_cvt                         ) return asserts ? "NA" : "MA";
    else if constexpr( current_api == avx      && !has_fma &&  fp16_cvt                         ) return asserts ? "NE" : "ME";
    else if constexpr( incomplete_avx512 && has_fma && fp16_cvt && has_bmi                      ) return asserts ? "TA" : "SA";
    else if constexpr( incomplete_avx512                                                        ) return {};
    else if constexpr( current_api == avx2     && !has_fma && !fp16_cvt && !has_bmi             ) return asserts ? "PG" : "OG";
    else if constexpr( current_api == avx2     && !has_fma &&  fp16_cvt && !has_bmi             ) return asserts ? "PC" : "OC";
    else if constexpr( current_api == avx2     && !has_fma && !fp16_cvt &&  has_bmi             ) return asserts ? "RG" : "QG";
    else if constexpr( current_api == avx2     &&  has_fma &&  fp16_cvt && !has_bmi             ) return asserts ? "PA" : "OA";
    else if constexpr( current_api == avx2     &&  has_fma &&  fp16_cvt &&  has_bmi             ) return asserts ? "RA" : "QA";
    else if constexpr( current_api == avx512   && has_fma && fp16_cvt && !has_vbmi && !fp16_ops ) return asserts ? "VAAA" : "UAAA";
    else if constexpr( current_api == avx512   && has_fma && fp16_cvt &&  has_vbmi &&  fp16_ops ) return asserts ? "V5LA" : "U5LA";
    else if constexpr( current_api == asimd    && !fp16_ops                                     ) return asserts ? "FA" : "EA";
    else if constexpr( current_api == asimd    &&  fp16_ops                                     ) return asserts ? "FU" : "EU";
    else if constexpr( current_api == sve128   && sve_bits == 128                               ) return asserts ? "HA" : "GA";
    else if constexpr( current_api == sve128   && sve_bits == 256                               ) return asserts ? "JA" : "IA";
    else if constexpr( current_api == sve128   && sve_bits == 512                               ) return asserts ? "LA" : "KA";
    else if constexpr( current_api == sve2_128 && sve_bits == 128                               ) return asserts ? "NA" : "MA";
    else if constexpr( current_api == vsx_2_07                                                  ) return asserts ? "RA" : "QA";
    else if constexpr( current_api == rvv      && rvv_bits == 128 && !fp16_cvt                  ) return asserts ? "FA" : "EA";
    else if constexpr( current_api == rvv      && rvv_bits == 128 &&  fp16_cvt                  ) return asserts ? "FE" : "EE";
    else if constexpr( current_api == rvv      && rvv_bits == 256 &&  fp16_ops                  ) return asserts ? "HU" : "GU";
    else                                                                                    return {};
  }
}

EVE_NAMESPACE
{
  struct abi_namespace_probe {};
}

TTS_CASE("Check eve ABI namespace wiring")
{
  TTS_TYPE_IS(eve::abi_namespace_probe, eve::EVE_ABI_NAMESPACE::abi_namespace_probe);
};

TTS_CASE("Check eve ABI namespace for CI configurations")
{
  if constexpr( ci_namespace().empty() ) TTS_PASS("Configuration not covered by CI");
  else
  {
    std::string expected{ci_namespace()};
    expected += "ABCDEFGHIJKLMNOPQRSTUVWXYZ012345"[option_bits];
    if( incomplete_avx512 ) expected += "ABCDEFGHIJKLMNOP"[avx512_subset_bits];
    while( expected.size() > 1 && expected.back() == 'A' ) expected.pop_back();
    TTS_EQUAL(std::string{eve::current_abi_namespace}, "abi_" + expected);
  }
};

TTS_CASE("Check that the ABI namespace string helpers don't leak into user code")
{
#if defined(EVE_ABI_STRING) || defined(EVE_ABI_STRING_)
  TTS_FAIL("EVE_ABI_STRING is still defined after including eve");
#else
  TTS_PASS("EVE_ABI_STRING is not defined after including eve");
#endif
};
