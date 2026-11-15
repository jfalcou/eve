//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
// No include guard: test/unit/config/abi_namespace_table.cpp includes it once per configuration.

#undef EVE_ABI_NAMESPACE
#undef EVE_ABI_API
#undef EVE_ABI_ASSERTS
#undef EVE_ABI_AVX512BW
#undef EVE_ABI_AVX512CD
#undef EVE_ABI_AVX512DQ
#undef EVE_ABI_AVX512VL
#undef EVE_ABI_BF16
#undef EVE_ABI_BITALG
#undef EVE_ABI_BITS1
#undef EVE_ABI_BITS2
#undef EVE_ABI_BITS3
#undef EVE_ABI_BITS4
#undef EVE_ABI_BITS5
#undef EVE_ABI_NO_F16C
#undef EVE_ABI_NO_FMA
#undef EVE_ABI_FMA
#undef EVE_ABI_FP16
#undef EVE_ABI_FP16_CVT
#undef EVE_ABI_FP16_SCALAR
#undef EVE_ABI_FP16_VECTOR
#undef EVE_ABI_FP_BITS
#undef EVE_ABI_IFMA
#undef EVE_ABI_NO_DENORMALS
#undef EVE_ABI_NO_FP16
#undef EVE_ABI_NO_INFINITIES
#undef EVE_ABI_NO_MINUSZERO
#undef EVE_ABI_NO_NANS
#undef EVE_ABI_ODD_FMA
#undef EVE_ABI_ODD_FP16
#undef EVE_ABI_TAG1
#undef EVE_ABI_TAG2
#undef EVE_ABI_TAG3
#undef EVE_ABI_TAG4
#undef EVE_ABI_TAG5
#undef EVE_ABI_USUAL_FMA
#undef EVE_ABI_USUAL_FP16
#undef EVE_ABI_VBMI
#undef EVE_ABI_VBMI2
#undef EVE_ABI_VNNI
#undef EVE_ABI_VP2INTERSECT
#undef EVE_ABI_VPOPCNTDQ
#undef EVE_ABI_W64

// The API takes 4 bits. It only has to be unique within a platform: objects built for different
// platforms are never linked together.
#if !defined(EVE_SUPPORTS_NATIVE_SIMD)
#  define EVE_ABI_API 0, 0, 0, 0
#elif defined(SPY_SIMD_IS_X86_AVX512)
#  define EVE_ABI_API 1, 0, 1, 0
#elif defined(EVE_INCOMPLETE_AVX512_SUPPORT)
#  define EVE_ABI_API 1, 0, 0, 1
#elif defined(SPY_SIMD_IS_X86_AVX2) && defined(EVE_USE_BMI)
#  define EVE_ABI_API 1, 0, 0, 0
#elif defined(SPY_SIMD_IS_X86_AVX2)
#  define EVE_ABI_API 0, 1, 1, 1
#elif defined(SPY_SIMD_IS_X86_AVX)
#  define EVE_ABI_API 0, 1, 1, 0
#elif defined(SPY_SIMD_IS_X86_SSE4_2)
#  define EVE_ABI_API 0, 1, 0, 1
#elif defined(SPY_SIMD_IS_X86_SSE4_1)
#  define EVE_ABI_API 0, 1, 0, 0
#elif defined(SPY_SIMD_IS_X86_SSSE3)
#  define EVE_ABI_API 0, 0, 1, 1
#elif defined(SPY_SIMD_IS_X86_SSE3)
#  define EVE_ABI_API 0, 0, 1, 0
#elif defined(SPY_SIMD_IS_X86_SSE2)
#  define EVE_ABI_API 0, 0, 0, 1
#elif defined(SPY_SIMD_IS_ARM_FIXED_SVE2) && __ARM_FEATURE_SVE_BITS == 512
#  define EVE_ABI_API 1, 0, 0, 0
#elif defined(SPY_SIMD_IS_ARM_FIXED_SVE2) && __ARM_FEATURE_SVE_BITS == 256
#  define EVE_ABI_API 0, 1, 1, 1
#elif defined(SPY_SIMD_IS_ARM_FIXED_SVE2) && __ARM_FEATURE_SVE_BITS == 128
#  define EVE_ABI_API 0, 1, 1, 0
#elif defined(SPY_SIMD_IS_ARM_FIXED_SVE) && __ARM_FEATURE_SVE_BITS == 512
#  define EVE_ABI_API 0, 1, 0, 1
#elif defined(SPY_SIMD_IS_ARM_FIXED_SVE) && __ARM_FEATURE_SVE_BITS == 256
#  define EVE_ABI_API 0, 1, 0, 0
#elif defined(SPY_SIMD_IS_ARM_FIXED_SVE) && __ARM_FEATURE_SVE_BITS == 128
#  define EVE_ABI_API 0, 0, 1, 1
#elif defined(EVE_SIMD_IS_ARM_ASIMD)
#  define EVE_ABI_API 0, 0, 1, 0
#elif defined(EVE_SIMD_IS_ARM_NEON)
#  define EVE_ABI_API 0, 0, 0, 1
#elif defined(SPY_SIMD_IS_PPC_VSX_3_01)
#  define EVE_ABI_API 1, 0, 1, 0
#elif defined(SPY_SIMD_IS_PPC_VSX_3_00)
#  define EVE_ABI_API 1, 0, 0, 1
#elif defined(SPY_SIMD_IS_PPC_VSX_2_07)
#  define EVE_ABI_API 1, 0, 0, 0
#elif defined(SPY_SIMD_IS_PPC_VSX_2_06)
#  define EVE_ABI_API 0, 1, 1, 1
#elif defined(SPY_SIMD_IS_PPC_VMX_3_01)
#  define EVE_ABI_API 0, 1, 1, 0
#elif defined(SPY_SIMD_IS_PPC_VMX_3_00)
#  define EVE_ABI_API 0, 1, 0, 1
#elif defined(SPY_SIMD_IS_PPC_VMX_2_07)
#  define EVE_ABI_API 0, 1, 0, 0
#elif defined(SPY_SIMD_IS_PPC_VMX_2_06)
#  define EVE_ABI_API 0, 0, 1, 1
#elif defined(SPY_SIMD_IS_PPC_VMX_2_05)
#  define EVE_ABI_API 0, 0, 1, 0
#elif defined(SPY_SIMD_IS_PPC_VMX_2_03)
#  define EVE_ABI_API 0, 0, 0, 1
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 65536
#  define EVE_ABI_API 1, 0, 1, 1
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 32768
#  define EVE_ABI_API 1, 0, 1, 0
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 16384
#  define EVE_ABI_API 1, 0, 0, 1
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 8192
#  define EVE_ABI_API 1, 0, 0, 0
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 4096
#  define EVE_ABI_API 0, 1, 1, 1
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 2048
#  define EVE_ABI_API 0, 1, 1, 0
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 1024
#  define EVE_ABI_API 0, 1, 0, 1
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 512
#  define EVE_ABI_API 0, 1, 0, 0
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 256
#  define EVE_ABI_API 0, 0, 1, 1
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 128
#  define EVE_ABI_API 0, 0, 1, 0
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 64
#  define EVE_ABI_API 0, 0, 0, 1
#else
#  error "[EVE] - Unsupported SIMD extension"
#endif

// What a build of that API usually has: the tag only records the differences.
#if !defined(EVE_SUPPORTS_NATIVE_SIMD)
#  define EVE_ABI_USUAL_FMA  0
#  define EVE_ABI_USUAL_FP16 0
#elif defined(SPY_SIMD_IS_X86_AVX2)
#  define EVE_ABI_USUAL_FMA  1
#  define EVE_ABI_USUAL_FP16 1
#elif defined(EVE_SIMD_IS_ANY_FIXED_SVE)
#  define EVE_ABI_USUAL_FMA  1
#  define EVE_ABI_USUAL_FP16 5
#elif defined(EVE_SIMD_IS_ARM_ASIMD)
#  define EVE_ABI_USUAL_FMA  1
#  define EVE_ABI_USUAL_FP16 1
#elif defined(EVE_SIMD_IS_ARM_NEON) || defined(SPY_SIMD_IS_PPC_VMX) || defined(SPY_SIMD_IS_PPC_VSX)
#  define EVE_ABI_USUAL_FMA  1
#  define EVE_ABI_USUAL_FP16 6
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV)
#  define EVE_ABI_USUAL_FMA  1
#  define EVE_ABI_USUAL_FP16 0
#else
#  define EVE_ABI_USUAL_FMA  0
#  define EVE_ABI_USUAL_FP16 0
#endif

#if defined(EVE_HAS_HARDWARE_FMA)
#  define EVE_ABI_FMA 1
#else
#  define EVE_ABI_FMA 0
#endif

#if !defined(EVE_NATIVE_FP16)
#  define EVE_ABI_NO_FP16     1
#  define EVE_ABI_FP16_CVT    0
#  define EVE_ABI_FP16_SCALAR 0
#  define EVE_ABI_FP16_VECTOR 0
#else
#  define EVE_ABI_NO_FP16 0
#  if defined(SPY_SUPPORTS_FP16_VECTOR_CONVERSION)
#    define EVE_ABI_FP16_CVT 1
#  else
#    define EVE_ABI_FP16_CVT 0
#  endif
#  if defined(SPY_SUPPORTS_FP16_SCALAR_OPS)
#    define EVE_ABI_FP16_SCALAR 1
#  else
#    define EVE_ABI_FP16_SCALAR 0
#  endif
#  if defined(SPY_SUPPORTS_FP16_VECTOR_OPS)
#    define EVE_ABI_FP16_VECTOR 1
#  else
#    define EVE_ABI_FP16_VECTOR 0
#  endif
#endif

#if EVE_ABI_FP16_VECTOR && !EVE_ABI_FP16_CVT
#  error "[EVE] - fp16 vector ops without vector conversion are not encoded in the ABI tag"
#endif

#if EVE_ABI_NO_FP16
#  define EVE_ABI_FP16 6
#elif EVE_ABI_FP16_SCALAR && EVE_ABI_FP16_VECTOR
#  define EVE_ABI_FP16 5
#elif EVE_ABI_FP16_SCALAR && EVE_ABI_FP16_CVT
#  define EVE_ABI_FP16 4
#elif EVE_ABI_FP16_SCALAR
#  define EVE_ABI_FP16 3
#elif EVE_ABI_FP16_VECTOR
#  define EVE_ABI_FP16 2
#elif EVE_ABI_FP16_CVT
#  define EVE_ABI_FP16 1
#else
#  define EVE_ABI_FP16 0
#endif

#define EVE_ABI_FP16_BITS0 0, 0, 0
#define EVE_ABI_FP16_BITS1 0, 0, 1
#define EVE_ABI_FP16_BITS2 0, 1, 0
#define EVE_ABI_FP16_BITS3 0, 1, 1
#define EVE_ABI_FP16_BITS4 1, 0, 0
#define EVE_ABI_FP16_BITS5 1, 0, 1
#define EVE_ABI_FP16_BITS6 1, 1, 0
#define EVE_ABI_FP16_BITS_(n) EVE_ABI_FP16_BITS##n
#define EVE_ABI_FP16_BITS(n)  EVE_ABI_FP16_BITS_(n)

// The usual fp16 support is spelled 0 and swaps its code with the one of 0
#if EVE_ABI_FP16 == EVE_ABI_USUAL_FP16
#  define EVE_ABI_ODD_FP16 EVE_ABI_FP16_BITS(0)
#elif EVE_ABI_FP16 == 0
#  define EVE_ABI_ODD_FP16 EVE_ABI_FP16_BITS(EVE_ABI_USUAL_FP16)
#else
#  define EVE_ABI_ODD_FP16 EVE_ABI_FP16_BITS(EVE_ABI_FP16)
#endif

#if EVE_ABI_FMA == EVE_ABI_USUAL_FMA
#  define EVE_ABI_ODD_FMA 0
#else
#  define EVE_ABI_ODD_FMA 1
#endif

#if defined(EVE_DISABLE_ASSERTS)
#  define EVE_ABI_ASSERTS 0
#else
#  define EVE_ABI_ASSERTS 1
#endif

#if defined(EVE_NO_DENORMALS)
#  define EVE_ABI_NO_DENORMALS 1
#else
#  define EVE_ABI_NO_DENORMALS 0
#endif

#if defined(EVE_NO_NANS)
#  define EVE_ABI_NO_NANS 1
#else
#  define EVE_ABI_NO_NANS 0
#endif

#if defined(EVE_NO_INFINITIES)
#  define EVE_ABI_NO_INFINITIES 1
#else
#  define EVE_ABI_NO_INFINITIES 0
#endif

#if defined(EVE_NO_MINUSZERO)
#  define EVE_ABI_NO_MINUSZERO 1
#else
#  define EVE_ABI_NO_MINUSZERO 0
#endif

#define EVE_ABI_FP_BITS 0, EVE_ABI_NO_MINUSZERO, EVE_ABI_NO_INFINITIES, EVE_ABI_NO_NANS, EVE_ABI_NO_DENORMALS

#if defined(SPY_SIMD_IS_X86_AVX512_BW)
#  define EVE_ABI_AVX512BW 1
#else
#  define EVE_ABI_AVX512BW 0
#endif

#if defined(SPY_SIMD_IS_X86_AVX512_CD)
#  define EVE_ABI_AVX512CD 1
#else
#  define EVE_ABI_AVX512CD 0
#endif

#if defined(SPY_SIMD_IS_X86_AVX512_DQ)
#  define EVE_ABI_AVX512DQ 1
#else
#  define EVE_ABI_AVX512DQ 0
#endif

#if defined(SPY_SIMD_IS_X86_AVX512_VL)
#  define EVE_ABI_AVX512VL 1
#else
#  define EVE_ABI_AVX512VL 0
#endif

#if defined(SPY_SIMD_IS_X86_AVX512_IFMA)
#  define EVE_ABI_IFMA 1
#else
#  define EVE_ABI_IFMA 0
#endif

#if defined(SPY_SIMD_IS_X86_AVX512_VBMI)
#  define EVE_ABI_VBMI 1
#else
#  define EVE_ABI_VBMI 0
#endif

#if defined(SPY_SIMD_IS_X86_AVX512_VBMI2)
#  define EVE_ABI_VBMI2 1
#else
#  define EVE_ABI_VBMI2 0
#endif

#if defined(SPY_SIMD_IS_X86_AVX512_VNNI)
#  define EVE_ABI_VNNI 1
#else
#  define EVE_ABI_VNNI 0
#endif

#if defined(SPY_SIMD_IS_X86_AVX512_BF16)
#  define EVE_ABI_BF16 1
#else
#  define EVE_ABI_BF16 0
#endif

#if defined(SPY_SIMD_IS_X86_AVX512_BITALG)
#  define EVE_ABI_BITALG 1
#else
#  define EVE_ABI_BITALG 0
#endif

#if defined(SPY_SIMD_IS_X86_AVX512_POPCNTDQ)
#  define EVE_ABI_VPOPCNTDQ 1
#else
#  define EVE_ABI_VPOPCNTDQ 0
#endif

#if defined(SPY_SIMD_IS_X86_AVX512_VP2INTERSECT)
#  define EVE_ABI_VP2INTERSECT 1
#else
#  define EVE_ABI_VP2INTERSECT 0
#endif

#if defined(EVE_AVX512_DEFAULT_64_BYTES)
#  define EVE_ABI_W64 1
#else
#  define EVE_ABI_W64 0
#endif

#if EVE_ABI_FMA
#  define EVE_ABI_NO_FMA 0
#else
#  define EVE_ABI_NO_FMA 1
#endif

#if !EVE_ABI_NO_FP16 && !EVE_ABI_FP16_CVT
#  define EVE_ABI_NO_F16C 1
#else
#  define EVE_ABI_NO_F16C 0
#endif

#define EVE_ABI_D00000(tag) tag##A
#define EVE_ABI_D00001(tag) tag##B
#define EVE_ABI_D00010(tag) tag##C
#define EVE_ABI_D00011(tag) tag##D
#define EVE_ABI_D00100(tag) tag##E
#define EVE_ABI_D00101(tag) tag##F
#define EVE_ABI_D00110(tag) tag##G
#define EVE_ABI_D00111(tag) tag##H
#define EVE_ABI_D01000(tag) tag##I
#define EVE_ABI_D01001(tag) tag##J
#define EVE_ABI_D01010(tag) tag##K
#define EVE_ABI_D01011(tag) tag##L
#define EVE_ABI_D01100(tag) tag##M
#define EVE_ABI_D01101(tag) tag##N
#define EVE_ABI_D01110(tag) tag##O
#define EVE_ABI_D01111(tag) tag##P
#define EVE_ABI_D10000(tag) tag##Q
#define EVE_ABI_D10001(tag) tag##R
#define EVE_ABI_D10010(tag) tag##S
#define EVE_ABI_D10011(tag) tag##T
#define EVE_ABI_D10100(tag) tag##U
#define EVE_ABI_D10101(tag) tag##V
#define EVE_ABI_D10110(tag) tag##W
#define EVE_ABI_D10111(tag) tag##X
#define EVE_ABI_D11000(tag) tag##Y
#define EVE_ABI_D11001(tag) tag##Z
#define EVE_ABI_D11010(tag) tag##0
#define EVE_ABI_D11011(tag) tag##1
#define EVE_ABI_D11100(tag) tag##2
#define EVE_ABI_D11101(tag) tag##3
#define EVE_ABI_D11110(tag) tag##4
#define EVE_ABI_D11111(tag) tag##5

#define EVE_ABI_LOOKUP_(a, b, c, d, e) EVE_ABI_D##a##b##c##d##e
#define EVE_ABI_LOOKUP(...)            EVE_ABI_LOOKUP_(__VA_ARGS__)
#define EVE_ABI_DIGIT(tag, ...)        EVE_ABI_LOOKUP(__VA_ARGS__)(tag)
#define EVE_ABI_ANY_(a, b, c, d, e)    (a || b || c || d || e)
#define EVE_ABI_ANY(...)               EVE_ABI_ANY_(__VA_ARGS__)

// Up to five base-32 digits after abi_, A to Z then 0 to 5: no lowercase letter, so that no tag is
// an eve name. The first digit is always there, the others up to the last non zero one.
#define EVE_ABI_BITS1 EVE_ABI_API, EVE_ABI_ASSERTS

#if defined(SPY_SIMD_IS_X86_AVX512)
#  define EVE_ABI_BITS2 EVE_ABI_BF16, EVE_ABI_VNNI, EVE_ABI_VBMI2, EVE_ABI_VBMI, EVE_ABI_IFMA
#  define EVE_ABI_BITS3 EVE_ABI_NO_FP16, EVE_ABI_FP16_VECTOR, EVE_ABI_VP2INTERSECT, EVE_ABI_VPOPCNTDQ, EVE_ABI_BITALG
#  define EVE_ABI_BITS4 0, EVE_ABI_NO_FMA, EVE_ABI_NO_F16C, 0, EVE_ABI_W64
#  define EVE_ABI_BITS5 EVE_ABI_FP_BITS
#else
#  define EVE_ABI_BITS2 EVE_ABI_ODD_FP16, EVE_ABI_ODD_FMA, 0
#  define EVE_ABI_BITS3 EVE_ABI_FP_BITS
#  if defined(EVE_INCOMPLETE_AVX512_SUPPORT)
#    define EVE_ABI_BITS4 0, EVE_ABI_AVX512BW, EVE_ABI_AVX512CD, EVE_ABI_AVX512DQ, EVE_ABI_AVX512VL
#  else
#    define EVE_ABI_BITS4 0, 0, 0, 0, 0
#  endif
#  define EVE_ABI_BITS5 0, 0, 0, 0, 0
#endif

#define EVE_ABI_TAG1 EVE_ABI_DIGIT(abi_, EVE_ABI_BITS1)
#define EVE_ABI_TAG2 EVE_ABI_DIGIT(EVE_ABI_TAG1, EVE_ABI_BITS2)
#define EVE_ABI_TAG3 EVE_ABI_DIGIT(EVE_ABI_TAG2, EVE_ABI_BITS3)
#define EVE_ABI_TAG4 EVE_ABI_DIGIT(EVE_ABI_TAG3, EVE_ABI_BITS4)
#define EVE_ABI_TAG5 EVE_ABI_DIGIT(EVE_ABI_TAG4, EVE_ABI_BITS5)

#if EVE_ABI_ANY(EVE_ABI_BITS5)
#  define EVE_ABI_NAMESPACE EVE_ABI_TAG5
#elif EVE_ABI_ANY(EVE_ABI_BITS4)
#  define EVE_ABI_NAMESPACE EVE_ABI_TAG4
#elif EVE_ABI_ANY(EVE_ABI_BITS3)
#  define EVE_ABI_NAMESPACE EVE_ABI_TAG3
#elif EVE_ABI_ANY(EVE_ABI_BITS2)
#  define EVE_ABI_NAMESPACE EVE_ABI_TAG2
#else
#  define EVE_ABI_NAMESPACE EVE_ABI_TAG1
#endif
