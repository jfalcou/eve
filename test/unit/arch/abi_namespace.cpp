//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <string_view>

#define EVE_TEST_STRINGIFY_(x) #x
#define EVE_TEST_STRINGIFY(x)  EVE_TEST_STRINGIFY_(x)

namespace
{
  constexpr std::string_view abi_namespace = EVE_TEST_STRINGIFY(EVE_ABI_NAMESPACE);

#if defined(EVE_USE_BMI)
  constexpr bool has_bmi       = true;
#else
  constexpr bool has_bmi       = false;
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

  constexpr std::string_view ci_namespace()
  {
    using namespace eve;
         if constexpr( current_api == neon && has_fma && no_fp16 && !has_denormals        ) return "Krb";
    else if constexpr( !ieee                                                              ) return {};
    else if constexpr( current_api == undefined_simd && !has_fma && !no_fp16 && !fp16_cvt ) return "Aa";
    else if constexpr( current_api == sse2     && !has_fma && !no_fp16 && !fp16_cvt       ) return "Ba";
    else if constexpr( current_api == sse2     && !has_fma &&  no_fp16                    ) return "Bq";
    else if constexpr( current_api == sse4_2   && !has_fma && !fp16_cvt                   ) return "Fa";
    else if constexpr( current_api == avx      && !has_fma && !fp16_cvt                   ) return "Ga";
    else if constexpr( current_api == avx      && !has_fma &&  fp16_cvt                   ) return "Gc";
    else if constexpr( current_api == avx2     && !has_fma && !fp16_cvt && !has_bmi       ) return "Ha";
    else if constexpr( current_api == avx2     && !has_fma &&  fp16_cvt && !has_bmi       ) return "Hc";
    else if constexpr( current_api == avx2     && !has_fma && !fp16_cvt &&  has_bmi       ) return "Ia";
    else if constexpr( current_api == avx2     &&  has_fma &&  fp16_cvt &&  has_bmi       ) return "Id";
    else if constexpr( current_api == avx512   && !has_vbmi && !fp16_ops                  ) return "Ja";
    else if constexpr( current_api == avx512   &&  has_vbmi &&  fp16_ops                  ) return "JFl";
    else if constexpr( current_api == asimd    && !fp16_ops                               ) return "Ld";
    else if constexpr( current_api == asimd    &&  fp16_ops                               ) return "Lp";
    else if constexpr( current_api == sve128   && sve_bits == 128                         ) return "Mp";
    else if constexpr( current_api == sve128   && sve_bits == 256                         ) return "Np";
    else if constexpr( current_api == sve128   && sve_bits == 512                         ) return "Op";
    else if constexpr( current_api == sve2_128 && sve_bits == 128                         ) return "Pp";
    else if constexpr( current_api == vsx_2_07                                            ) return "Tbr";
    else if constexpr( current_api == rvv      && rvv_bits == 128 && !fp16_cvt            ) return "Ubb";
    else if constexpr( current_api == rvv      && rvv_bits == 128 &&  fp16_cvt            ) return "Ubd";
    else if constexpr( current_api == rvv      && rvv_bits == 256 &&  fp16_ops            ) return "Ucp";
    else                                                                                    return {};
  }
}

TTS_CASE("Check eve ABI namespace wiring")
{
  TTS_TYPE_IS(eve::wide<float>, eve::EVE_ABI_NAMESPACE::wide<float>);
};

TTS_CASE("Check eve ABI namespace for CI configurations")
{
  if constexpr( ci_namespace().empty() ) TTS_PASS("Configuration not covered by CI");
  else                                   TTS_EQUAL(abi_namespace, ci_namespace());
};
