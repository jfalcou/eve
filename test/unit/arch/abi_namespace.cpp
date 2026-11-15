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
         if constexpr( current_api == neon && has_fma && no_fp16 && !has_denormals        ) return asserts ? "KB" : "KA";
    else if constexpr( !ieee                                                              ) return {};
    else if constexpr( current_api == undefined_simd && !has_fma && !no_fp16 && !fp16_cvt ) return asserts ? "Ab" : "Aa";
    else if constexpr( current_api == sse2     && !has_fma && !no_fp16 && !fp16_cvt       ) return asserts ? "Bb" : "Ba";
    else if constexpr( current_api == sse2     && !has_fma &&  no_fp16                    ) return asserts ? "Bz" : "By";
    else if constexpr( current_api == sse4_2   && !has_fma && !fp16_cvt                   ) return asserts ? "Fb" : "Fa";
    else if constexpr( current_api == avx      && !has_fma && !fp16_cvt                   ) return asserts ? "Gb" : "Ga";
    else if constexpr( current_api == avx      && !has_fma &&  fp16_cvt                   ) return asserts ? "Gf" : "Ge";
    else if constexpr( incomplete_avx512 && has_fma && fp16_cvt && has_bmi                ) return asserts ? "Vh" : "Vg";
    else if constexpr( incomplete_avx512                                                  ) return {};
    else if constexpr( current_api == avx2     && !has_fma && !fp16_cvt && !has_bmi       ) return asserts ? "Hb" : "Ha";
    else if constexpr( current_api == avx2     && !has_fma &&  fp16_cvt && !has_bmi       ) return asserts ? "Hf" : "He";
    else if constexpr( current_api == avx2     && !has_fma && !fp16_cvt &&  has_bmi       ) return asserts ? "Ib" : "Ia";
    else if constexpr( current_api == avx2     &&  has_fma &&  fp16_cvt &&  has_bmi       ) return asserts ? "Ih" : "Ig";
    else if constexpr( current_api == avx512   && !has_vbmi && !fp16_ops                  ) return asserts ? "Jaac" : "Ja";
    else if constexpr( current_api == avx512   &&  has_vbmi &&  fp16_ops                  ) return asserts ? "JFlc" : "JFl";
    else if constexpr( current_api == asimd    && !fp16_ops                               ) return asserts ? "Lh" : "Lg";
    else if constexpr( current_api == asimd    &&  fp16_ops                               ) return asserts ? "Lx" : "Lw";
    else if constexpr( current_api == sve128   && sve_bits == 128                         ) return asserts ? "Mx" : "Mw";
    else if constexpr( current_api == sve128   && sve_bits == 256                         ) return asserts ? "Nx" : "Nw";
    else if constexpr( current_api == sve128   && sve_bits == 512                         ) return asserts ? "Ox" : "Ow";
    else if constexpr( current_api == sve2_128 && sve_bits == 128                         ) return asserts ? "Px" : "Pw";
    else if constexpr( current_api == vsx_2_07                                            ) return asserts ? "TbB" : "TbA";
    else if constexpr( current_api == rvv      && rvv_bits == 128 && !fp16_cvt            ) return asserts ? "Ubd" : "Ubc";
    else if constexpr( current_api == rvv      && rvv_bits == 128 &&  fp16_cvt            ) return asserts ? "Ubh" : "Ubg";
    else if constexpr( current_api == rvv      && rvv_bits == 256 &&  fp16_ops            ) return asserts ? "Ucx" : "Ucw";
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
    if( incomplete_avx512 ) expected += "abcdefghijklmnop"[avx512_subset_bits];
    if( option_bits ) expected += "abcdefghijklmnopqrstuvwxyzABCDEF"[option_bits];
    TTS_EQUAL(std::string{eve::current_abi_namespace}, expected);
  }
};
