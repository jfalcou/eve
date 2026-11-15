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
#include "abi_namespace_clear_inputs.hpp"
#define EVE_NATIVE_FP16
#include "abi_namespace_case.hpp"
}

namespace avx2_bmi
{
#include "abi_namespace_clear_inputs.hpp"
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
#include "abi_namespace_clear_inputs.hpp"
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
#include "abi_namespace_clear_inputs.hpp"
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
#include "abi_namespace_clear_inputs.hpp"
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
#include "abi_namespace_clear_inputs.hpp"
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
#include "abi_namespace_clear_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_AVX512
#define EVE_USE_BMI
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#include "abi_namespace_case.hpp"
}

namespace avx512_no_f16c
{
#include "abi_namespace_clear_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_AVX512
#define EVE_USE_BMI
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#include "abi_namespace_case.hpp"
}

namespace avx512_skylake_no_asserts
{
#include "abi_namespace_clear_inputs.hpp"
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
#include "abi_namespace_clear_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_ARM_FIXED_SVE
#define __ARM_FEATURE_SVE_BITS 256
#define EVE_SIMD_IS_ANY_FIXED_SVE
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_SCALAR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#include "abi_namespace_case.hpp"
}

namespace rvv_128
{
#include "abi_namespace_clear_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_RISCV_FIXED_RVV
#define __riscv_v_fixed_vlen 128
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#include "abi_namespace_case.hpp"
}

namespace sse2_no_fp16
{
#include "abi_namespace_clear_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_SSE2
#include "abi_namespace_case.hpp"
}

namespace avx2_no_fma
{
#include "abi_namespace_clear_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_AVX2
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#include "abi_namespace_case.hpp"
}

namespace avx2_no_f16c
{
#include "abi_namespace_clear_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_X86_AVX2
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#include "abi_namespace_case.hpp"
}

namespace asimd_fp16
{
#include "abi_namespace_clear_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define EVE_SIMD_IS_ARM_ASIMD
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_SCALAR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#include "abi_namespace_case.hpp"
}

namespace sve_1024_as_asimd
{
#include "abi_namespace_clear_inputs.hpp"
#define EVE_SUPPORTS_NATIVE_SIMD
#define SPY_SIMD_IS_ARM_FIXED_SVE
#define __ARM_FEATURE_SVE_BITS 1024
#define EVE_SIMD_IS_ARM_ASIMD
#define EVE_HAS_HARDWARE_FMA
#define EVE_NATIVE_FP16
#define SPY_SUPPORTS_FP16_SCALAR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_OPS
#define SPY_SUPPORTS_FP16_VECTOR_CONVERSION
#include "abi_namespace_case.hpp"
}

#include "abi_namespace_clear_inputs.hpp"

TTS_CASE("ABI namespace for a given configuration")
{
  TTS_EQUAL(no_simd::tag                  , std::string_view{"abi_B"}   );
  TTS_EQUAL(avx2_bmi::tag                 , std::string_view{"abi_R"}   );
  TTS_EQUAL(avx2_bmi_no_nans::tag         , std::string_view{"abi_RAC"} );
  TTS_EQUAL(avx512f_only::tag             , std::string_view{"abi_T"}   );
  TTS_EQUAL(avx512_knl::tag               , std::string_view{"abi_TAAE"});
  TTS_EQUAL(avx512_skylake::tag           , std::string_view{"abi_V"}   );
  TTS_EQUAL(avx512_skylake_no_asserts::tag, std::string_view{"abi_U"}   );
  TTS_EQUAL(avx512_no_fma::tag            , std::string_view{"abi_VAAI"});
  TTS_EQUAL(avx512_no_f16c::tag           , std::string_view{"abi_VAAE"});
  TTS_EQUAL(sve_256::tag                  , std::string_view{"abi_J"}   );
  TTS_EQUAL(rvv_128::tag                  , std::string_view{"abi_F"}   );
  TTS_EQUAL(sse2_no_fp16::tag             , std::string_view{"abi_DY"}  );
  TTS_EQUAL(avx2_no_fma::tag              , std::string_view{"abi_PC"}  );
  TTS_EQUAL(avx2_no_f16c::tag             , std::string_view{"abi_PE"}  );
  TTS_EQUAL(asimd_fp16::tag               , std::string_view{"abi_FU"}  );
  TTS_EQUAL(sve_1024_as_asimd::tag        , std::string_view{"abi_FU"}  );
};
