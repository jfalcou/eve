//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
// No include guard: test/unit/arch/abi_namespace_table.cpp includes it once per configuration.

#undef EVE_ABI_NAMESPACE
#undef EVE_ABI_EXPECTED
#undef EVE_ABI_API
#undef EVE_ABI_FMA
#undef EVE_ABI_NO_FP16
#undef EVE_ABI_FP16_CVT
#undef EVE_ABI_FP16_SCALAR
#undef EVE_ABI_FP16_VECTOR
#undef EVE_ABI_NO_DENORMALS
#undef EVE_ABI_NO_NANS
#undef EVE_ABI_NO_INFINITIES
#undef EVE_ABI_NO_MINUSZERO
#undef EVE_ABI_ASSERTS
#undef EVE_ABI_AVX512BW
#undef EVE_ABI_AVX512CD
#undef EVE_ABI_AVX512DQ
#undef EVE_ABI_AVX512VL
#undef EVE_ABI_FP_BITS
#undef EVE_ABI_NON_DEFAULT_FP
#undef EVE_ABI_IFMA
#undef EVE_ABI_VBMI
#undef EVE_ABI_VBMI2
#undef EVE_ABI_VNNI
#undef EVE_ABI_BF16
#undef EVE_ABI_BITALG
#undef EVE_ABI_VPOPCNTDQ
#undef EVE_ABI_VP2INTERSECT
#undef EVE_ABI_W64
#undef EVE_ABI_NO_FMA
#undef EVE_ABI_NO_F16C
#undef EVE_ABI_BITS1
#undef EVE_ABI_BITS2
#undef EVE_ABI_BITS3
#undef EVE_ABI_TAG1
#undef EVE_ABI_TAG2
#undef EVE_ABI_TAG3
#undef EVE_ABI_EXPECTED1
#undef EVE_ABI_EXPECTED2
#undef EVE_ABI_EXPECTED3
#undef EVE_ABI_FP16

#if !defined(EVE_SUPPORTS_NATIVE_SIMD)
#  define EVE_ABI_API(next) next(A)
#elif defined(SPY_SIMD_IS_X86_AVX512)
#  define EVE_ABI_API(next) next(J)
#elif defined(EVE_INCOMPLETE_AVX512_SUPPORT)
#  define EVE_ABI_API(next) next(V)
#elif defined(SPY_SIMD_IS_X86_AVX2) && defined(EVE_USE_BMI)
#  define EVE_ABI_API(next) next(I)
#elif defined(SPY_SIMD_IS_X86_AVX2)
#  define EVE_ABI_API(next) next(H)
#elif defined(SPY_SIMD_IS_X86_AVX)
#  define EVE_ABI_API(next) next(G)
#elif defined(SPY_SIMD_IS_X86_SSE4_2)
#  define EVE_ABI_API(next) next(F)
#elif defined(SPY_SIMD_IS_X86_SSE4_1)
#  define EVE_ABI_API(next) next(E)
#elif defined(SPY_SIMD_IS_X86_SSSE3)
#  define EVE_ABI_API(next) next(D)
#elif defined(SPY_SIMD_IS_X86_SSE3)
#  define EVE_ABI_API(next) next(C)
#elif defined(SPY_SIMD_IS_X86_SSE2)
#  define EVE_ABI_API(next) next(B)
#elif defined(SPY_SIMD_IS_ARM_FIXED_SVE2) && __ARM_FEATURE_SVE_BITS == 128
#  define EVE_ABI_API(next) next(P)
#elif defined(SPY_SIMD_IS_ARM_FIXED_SVE2) && __ARM_FEATURE_SVE_BITS == 256
#  define EVE_ABI_API(next) next(Q)
#elif defined(SPY_SIMD_IS_ARM_FIXED_SVE2) && __ARM_FEATURE_SVE_BITS == 512
#  define EVE_ABI_API(next) next(R)
#elif defined(SPY_SIMD_IS_ARM_FIXED_SVE) && __ARM_FEATURE_SVE_BITS == 128
#  define EVE_ABI_API(next) next(M)
#elif defined(SPY_SIMD_IS_ARM_FIXED_SVE) && __ARM_FEATURE_SVE_BITS == 256
#  define EVE_ABI_API(next) next(N)
#elif defined(SPY_SIMD_IS_ARM_FIXED_SVE) && __ARM_FEATURE_SVE_BITS == 512
#  define EVE_ABI_API(next) next(O)
#elif defined(SPY_SIMD_IS_ARM_ASIMD)
#  define EVE_ABI_API(next) next(L)
#elif defined(SPY_SIMD_IS_ARM_NEON)
#  define EVE_ABI_API(next) next(K)
#elif defined(SPY_SIMD_IS_PPC_VSX_3_01)
#  define EVE_ABI_API(next) next(Td)
#elif defined(SPY_SIMD_IS_PPC_VSX_3_00)
#  define EVE_ABI_API(next) next(Tc)
#elif defined(SPY_SIMD_IS_PPC_VSX_2_07)
#  define EVE_ABI_API(next) next(Tb)
#elif defined(SPY_SIMD_IS_PPC_VSX_2_06)
#  define EVE_ABI_API(next) next(Ta)
#elif defined(SPY_SIMD_IS_PPC_VMX_3_01)
#  define EVE_ABI_API(next) next(Sf)
#elif defined(SPY_SIMD_IS_PPC_VMX_3_00)
#  define EVE_ABI_API(next) next(Se)
#elif defined(SPY_SIMD_IS_PPC_VMX_2_07)
#  define EVE_ABI_API(next) next(Sd)
#elif defined(SPY_SIMD_IS_PPC_VMX_2_06)
#  define EVE_ABI_API(next) next(Sc)
#elif defined(SPY_SIMD_IS_PPC_VMX_2_05)
#  define EVE_ABI_API(next) next(Sb)
#elif defined(SPY_SIMD_IS_PPC_VMX_2_03)
#  define EVE_ABI_API(next) next(Sa)
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 64
#  define EVE_ABI_API(next) next(Ua)
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 128
#  define EVE_ABI_API(next) next(Ub)
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 256
#  define EVE_ABI_API(next) next(Uc)
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 512
#  define EVE_ABI_API(next) next(Ud)
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 1024
#  define EVE_ABI_API(next) next(Ue)
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 2048
#  define EVE_ABI_API(next) next(Uf)
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 4096
#  define EVE_ABI_API(next) next(Ug)
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 8192
#  define EVE_ABI_API(next) next(Uh)
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 16384
#  define EVE_ABI_API(next) next(Ui)
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 32768
#  define EVE_ABI_API(next) next(Uj)
#elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 65536
#  define EVE_ABI_API(next) next(Uk)
#else
#  error "[EVE] - Unsupported SIMD extension"
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
#  if defined(SPY_SUPPORTS_FP16_VECTOR_CONVERSION) && !defined(SPY_SIMD_IS_X86_AVX512)
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

#if defined(EVE_DISABLE_ASSERTS)
#  define EVE_ABI_ASSERTS 0
#else
#  define EVE_ABI_ASSERTS 1
#endif

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

#define EVE_ABI_D00000(tag) tag##a
#define EVE_ABI_D00001(tag) tag##b
#define EVE_ABI_D00010(tag) tag##c
#define EVE_ABI_D00011(tag) tag##d
#define EVE_ABI_D00100(tag) tag##e
#define EVE_ABI_D00101(tag) tag##f
#define EVE_ABI_D00110(tag) tag##g
#define EVE_ABI_D00111(tag) tag##h
#define EVE_ABI_D01000(tag) tag##i
#define EVE_ABI_D01001(tag) tag##j
#define EVE_ABI_D01010(tag) tag##k
#define EVE_ABI_D01011(tag) tag##l
#define EVE_ABI_D01100(tag) tag##m
#define EVE_ABI_D01101(tag) tag##n
#define EVE_ABI_D01110(tag) tag##o
#define EVE_ABI_D01111(tag) tag##p
#define EVE_ABI_D10000(tag) tag##q
#define EVE_ABI_D10001(tag) tag##r
#define EVE_ABI_D10010(tag) tag##s
#define EVE_ABI_D10011(tag) tag##t
#define EVE_ABI_D10100(tag) tag##u
#define EVE_ABI_D10101(tag) tag##v
#define EVE_ABI_D10110(tag) tag##w
#define EVE_ABI_D10111(tag) tag##x
#define EVE_ABI_D11000(tag) tag##y
#define EVE_ABI_D11001(tag) tag##z
#define EVE_ABI_D11010(tag) tag##A
#define EVE_ABI_D11011(tag) tag##B
#define EVE_ABI_D11100(tag) tag##C
#define EVE_ABI_D11101(tag) tag##D
#define EVE_ABI_D11110(tag) tag##E
#define EVE_ABI_D11111(tag) tag##F

#define EVE_ABI_LOOKUP_(a, b, c, d, e) EVE_ABI_D##a##b##c##d##e
#define EVE_ABI_LOOKUP(...)            EVE_ABI_LOOKUP_(__VA_ARGS__)
#define EVE_ABI_DIGIT(tag, ...)        EVE_ABI_LOOKUP(__VA_ARGS__)(tag)

#define EVE_ABI_STR(x)                 #x
#define EVE_ABI_CHR_(a, b, c, d, e)    "abcdefghijklmnopqrstuvwxyzABCDEF"[a * 16 + b * 8 + c * 4 + d * 2 + e]
#define EVE_ABI_CHR(...)               EVE_ABI_CHR_(__VA_ARGS__)

#define EVE_ABI_FP_BITS 0, EVE_ABI_NO_MINUSZERO, EVE_ABI_NO_INFINITIES, EVE_ABI_NO_NANS, EVE_ABI_NO_DENORMALS

#if EVE_ABI_NO_DENORMALS || EVE_ABI_NO_NANS || EVE_ABI_NO_INFINITIES || EVE_ABI_NO_MINUSZERO
#  define EVE_ABI_NON_DEFAULT_FP 1
#else
#  define EVE_ABI_NON_DEFAULT_FP 0
#endif

#if defined(SPY_SIMD_IS_X86_AVX512)

#  if defined(SPY_SIMD_IS_X86_AVX512_IFMA)
#    define EVE_ABI_IFMA 1
#  else
#    define EVE_ABI_IFMA 0
#  endif

#  if defined(SPY_SIMD_IS_X86_AVX512_VBMI)
#    define EVE_ABI_VBMI 1
#  else
#    define EVE_ABI_VBMI 0
#  endif

#  if defined(SPY_SIMD_IS_X86_AVX512_VBMI2)
#    define EVE_ABI_VBMI2 1
#  else
#    define EVE_ABI_VBMI2 0
#  endif

#  if defined(SPY_SIMD_IS_X86_AVX512_VNNI)
#    define EVE_ABI_VNNI 1
#  else
#    define EVE_ABI_VNNI 0
#  endif

#  if defined(SPY_SIMD_IS_X86_AVX512_BF16)
#    define EVE_ABI_BF16 1
#  else
#    define EVE_ABI_BF16 0
#  endif

#  if defined(SPY_SIMD_IS_X86_AVX512_BITALG)
#    define EVE_ABI_BITALG 1
#  else
#    define EVE_ABI_BITALG 0
#  endif

#  if defined(SPY_SIMD_IS_X86_AVX512_POPCNTDQ)
#    define EVE_ABI_VPOPCNTDQ 1
#  else
#    define EVE_ABI_VPOPCNTDQ 0
#  endif

#  if defined(SPY_SIMD_IS_X86_AVX512_VP2INTERSECT)
#    define EVE_ABI_VP2INTERSECT 1
#  else
#    define EVE_ABI_VP2INTERSECT 0
#  endif

#  if defined(EVE_AVX512_DEFAULT_64_BYTES)
#    define EVE_ABI_W64 1
#  else
#    define EVE_ABI_W64 0
#  endif

#  if EVE_ABI_FMA
#    define EVE_ABI_NO_FMA 0
#  else
#    define EVE_ABI_NO_FMA 1
#  endif

#  if !EVE_ABI_NO_FP16 && !defined(SPY_SUPPORTS_FP16_VECTOR_CONVERSION)
#    define EVE_ABI_NO_F16C 1
#  else
#    define EVE_ABI_NO_F16C 0
#  endif

#  define EVE_ABI_BITS1 EVE_ABI_BF16, EVE_ABI_VNNI, EVE_ABI_VBMI2, EVE_ABI_VBMI, EVE_ABI_IFMA
#  define EVE_ABI_BITS2 EVE_ABI_NO_FP16, EVE_ABI_FP16_VECTOR, EVE_ABI_VP2INTERSECT, EVE_ABI_VPOPCNTDQ, EVE_ABI_BITALG
#  define EVE_ABI_BITS3 0, EVE_ABI_NO_FMA, EVE_ABI_NO_F16C, EVE_ABI_ASSERTS, EVE_ABI_W64

#  define EVE_ABI_TAG1 EVE_ABI_API(EVE_ABI_LOOKUP(EVE_ABI_BITS1))
#  define EVE_ABI_TAG2 EVE_ABI_DIGIT(EVE_ABI_TAG1, EVE_ABI_BITS2)
#  define EVE_ABI_TAG3 EVE_ABI_DIGIT(EVE_ABI_TAG2, EVE_ABI_BITS3)

#  define EVE_ABI_EXPECTED1 EVE_ABI_API(EVE_ABI_STR), EVE_ABI_CHR(EVE_ABI_BITS1)
#  define EVE_ABI_EXPECTED2 EVE_ABI_EXPECTED1, EVE_ABI_CHR(EVE_ABI_BITS2)
#  define EVE_ABI_EXPECTED3 EVE_ABI_EXPECTED2, EVE_ABI_CHR(EVE_ABI_BITS3)

#  if EVE_ABI_NON_DEFAULT_FP
#    define EVE_ABI_NAMESPACE EVE_ABI_DIGIT(EVE_ABI_TAG3, EVE_ABI_FP_BITS)
#    define EVE_ABI_EXPECTED  EVE_ABI_EXPECTED3, EVE_ABI_CHR(EVE_ABI_FP_BITS)
#  elif EVE_ABI_W64 || EVE_ABI_ASSERTS || EVE_ABI_NO_FMA || EVE_ABI_NO_F16C
#    define EVE_ABI_NAMESPACE EVE_ABI_TAG3
#    define EVE_ABI_EXPECTED  EVE_ABI_EXPECTED3
#  elif EVE_ABI_BITALG || EVE_ABI_VPOPCNTDQ || EVE_ABI_VP2INTERSECT || EVE_ABI_FP16_VECTOR || EVE_ABI_NO_FP16
#    define EVE_ABI_NAMESPACE EVE_ABI_TAG2
#    define EVE_ABI_EXPECTED  EVE_ABI_EXPECTED2
#  else
#    define EVE_ABI_NAMESPACE EVE_ABI_TAG1
#    define EVE_ABI_EXPECTED  EVE_ABI_EXPECTED1
#  endif

#else

#  if EVE_ABI_FP16_VECTOR && !EVE_ABI_FP16_CVT
#    error "[EVE] - fp16 vector ops without vector conversion are not encoded in the ABI tag"
#  endif

#  if EVE_ABI_NO_FP16
#    define EVE_ABI_FP16 1, 1, 0
#  elif EVE_ABI_FP16_SCALAR && EVE_ABI_FP16_VECTOR
#    define EVE_ABI_FP16 1, 0, 1
#  elif EVE_ABI_FP16_SCALAR && EVE_ABI_FP16_CVT
#    define EVE_ABI_FP16 1, 0, 0
#  elif EVE_ABI_FP16_SCALAR
#    define EVE_ABI_FP16 0, 1, 1
#  elif EVE_ABI_FP16_VECTOR
#    define EVE_ABI_FP16 0, 1, 0
#  elif EVE_ABI_FP16_CVT
#    define EVE_ABI_FP16 0, 0, 1
#  else
#    define EVE_ABI_FP16 0, 0, 0
#  endif

#  define EVE_ABI_BITS1 EVE_ABI_FP16, EVE_ABI_FMA, EVE_ABI_ASSERTS
#  define EVE_ABI_TAG1      EVE_ABI_API(EVE_ABI_LOOKUP(EVE_ABI_BITS1))
#  define EVE_ABI_EXPECTED1 EVE_ABI_API(EVE_ABI_STR), EVE_ABI_CHR(EVE_ABI_BITS1)

#  if defined(EVE_INCOMPLETE_AVX512_SUPPORT)
#    define EVE_ABI_BITS2     0, EVE_ABI_AVX512BW, EVE_ABI_AVX512CD, EVE_ABI_AVX512DQ, EVE_ABI_AVX512VL
#    define EVE_ABI_TAG2      EVE_ABI_DIGIT(EVE_ABI_TAG1, EVE_ABI_BITS2)
#    define EVE_ABI_EXPECTED2 EVE_ABI_EXPECTED1, EVE_ABI_CHR(EVE_ABI_BITS2)
#  else
#    define EVE_ABI_TAG2      EVE_ABI_TAG1
#    define EVE_ABI_EXPECTED2 EVE_ABI_EXPECTED1
#  endif

#  if EVE_ABI_NON_DEFAULT_FP
#    define EVE_ABI_NAMESPACE EVE_ABI_DIGIT(EVE_ABI_TAG2, EVE_ABI_FP_BITS)
#    define EVE_ABI_EXPECTED  EVE_ABI_EXPECTED2, EVE_ABI_CHR(EVE_ABI_FP_BITS)
#  else
#    define EVE_ABI_NAMESPACE EVE_ABI_TAG2
#    define EVE_ABI_EXPECTED  EVE_ABI_EXPECTED2
#  endif

#endif
