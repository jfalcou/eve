//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <string_view>

namespace no_simd
{
#include "abi_namespace_inputs.hpp"
#define EVE_NATIVE_FP16
#include "abi_namespace_case.hpp"
}

namespace avx2_bmi
{
#include "abi_namespace_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_AVX2
#define EVE_USE_BMI
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#include "abi_namespace_case.hpp"
}

namespace avx2_bmi_no_nans
{
#include "abi_namespace_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_AVX2
#define EVE_USE_BMI
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#define EVE_NO_NANS
#include "abi_namespace_case.hpp"
}

namespace avx512f_only
{
#include "abi_namespace_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_AVX2
#define EVE_INCOMPLETE_AVX512_SUPPORT
#define EVE_USE_BMI
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#include "abi_namespace_case.hpp"
}

namespace avx512_knl
{
#include "abi_namespace_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_AVX2
#define EVE_INCOMPLETE_AVX512_SUPPORT
#define SPY_SIMD_IS_X86_AVX512_CD
#define EVE_USE_BMI
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#include "abi_namespace_case.hpp"
}

namespace avx512_skylake
{
#include "abi_namespace_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_AVX512
#define EVE_USE_BMI
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#include "abi_namespace_case.hpp"
}

namespace avx512_no_fma
{
#include "abi_namespace_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_AVX512
#define EVE_USE_BMI
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#include "abi_namespace_case.hpp"
}

namespace avx512_no_f16c
{
#include "abi_namespace_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_AVX512
#define EVE_USE_BMI
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#include "abi_namespace_case.hpp"
}

namespace avx512_skylake_no_asserts
{
#include "abi_namespace_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_AVX512
#define EVE_USE_BMI
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#define EVE_DISABLE_ASSERTS
#include "abi_namespace_case.hpp"
}

namespace sve_256
{
#include "abi_namespace_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_ARM_FIXED_SVE
#define __ARM_FEATURE_SVE_BITS 256
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_SCALAR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#include "abi_namespace_case.hpp"
}

namespace rvv_128
{
#include "abi_namespace_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_RISCV_FIXED_RVV
#define __riscv_v_fixed_vlen 128
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#include "abi_namespace_case.hpp"
}

namespace clash_with_tag
{
#include "abi_namespace_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_AVX2
#define EVE_USE_BMI
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#define Ih boom
#include "abi_namespace_case.hpp"
#undef Ih
}

namespace clash_with_partial_tag
{
#include "abi_namespace_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_AVX512
#define EVE_USE_BMI
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#define Ja oops
#include "abi_namespace_case.hpp"
#undef Ja
}

namespace no_clash_with_api_letter
{
#include "abi_namespace_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_AVX2
#define EVE_USE_BMI
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#define I oops
#include "abi_namespace_case.hpp"
#undef I
}

#include "abi_namespace_inputs.hpp"

TTS_CASE("ABI namespace for a given configuration")
{
  TTS_EQUAL(no_simd::tag                  , std::string_view{"Ab"}  );
  TTS_EQUAL(avx2_bmi::tag                 , std::string_view{"Ih"}  );
  TTS_EQUAL(avx2_bmi_no_nans::tag         , std::string_view{"Ihc"} );
  TTS_EQUAL(avx512f_only::tag             , std::string_view{"Vha"} );
  TTS_EQUAL(avx512_knl::tag               , std::string_view{"Vhe"} );
  TTS_EQUAL(avx512_skylake::tag           , std::string_view{"Jaac"});
  TTS_EQUAL(avx512_skylake_no_asserts::tag, std::string_view{"Ja"}  );
  TTS_EQUAL(avx512_no_fma::tag            , std::string_view{"Jaak"});
  TTS_EQUAL(avx512_no_f16c::tag           , std::string_view{"Jaag"});
  TTS_EQUAL(sve_256::tag                  , std::string_view{"Nx"}  );
  TTS_EQUAL(rvv_128::tag                  , std::string_view{"Ubd"} );

  TTS_EXPECT(no_simd::ok && avx2_bmi::ok && avx2_bmi_no_nans::ok && avx512f_only::ok && avx512_knl::ok);
  TTS_EXPECT(avx512_skylake::ok && avx512_skylake_no_asserts::ok && avx512_no_fma::ok && avx512_no_f16c::ok);
  TTS_EXPECT(sve_256::ok && rvv_128::ok);
};

TTS_CASE("ABI namespace changed by a macro is detected")
{
  TTS_EQUAL(clash_with_tag::tag, std::string_view{"boom"});
  TTS_EXPECT_NOT(clash_with_tag::ok);

  TTS_EQUAL(clash_with_partial_tag::tag, std::string_view{"oopsac"});
  TTS_EXPECT_NOT(clash_with_partial_tag::ok);

  TTS_EQUAL(no_clash_with_api_letter::tag, std::string_view{"Ih"});
  TTS_EXPECT(no_clash_with_api_letter::ok);
};
