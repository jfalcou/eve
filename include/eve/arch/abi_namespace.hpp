//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/predef.hpp>

//==================================================================================================
//! @addtogroup eve_arch
//! @{
//!   @def EVE_ABI_NAMESPACE
//!   @brief Name of the inline namespace that holds all of **EVE**.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   Everything in **EVE** lives in `eve::EVE_ABI_NAMESPACE`, an inline namespace whose name is
//!   derived from the instruction sets and **EVE** options used to compile it, for example
//!   `eve::Hc` for `-mavx2 -mf16c`. Translation units compiled with different options can
//!   therefore be linked into the same program, as their **EVE** symbols never share a name. The
//!   name is kept short on purpose and is not meant to be read.
//!
//!   You can choose the name yourself by defining `EVE_ABI_NAMESPACE` before including **EVE**.
//!   If you give the same name to translation units compiled with different options, keeping them
//!   apart is then up to you.
//!
//!   To protect your own code that depends on compilation options in the same way, put it in an
//!   inline namespace named after the same macro:
//!
//!   @code
//!   namespace mylib::inline EVE_ABI_NAMESPACE
//!   {
//!     float sum(float const* data, std::size_t size);
//!   }
//!   @endcode
//! @}
//==================================================================================================
#if defined(EVE_DOXYGEN_INVOKED)
#  define EVE_ABI_NAMESPACE
#elif !defined(EVE_ABI_NAMESPACE)

#  if !defined(EVE_SUPPORTS_NATIVE_SIMD)
#    define EVE_ABI_API(next) next(A)
#  elif defined(SPY_SIMD_IS_X86_AVX512)
#    define EVE_ABI_API(next) next(J)
#  elif defined(SPY_SIMD_IS_X86_AVX2) && defined(EVE_USE_BMI)
#    define EVE_ABI_API(next) next(I)
#  elif defined(SPY_SIMD_IS_X86_AVX2)
#    define EVE_ABI_API(next) next(H)
#  elif defined(SPY_SIMD_IS_X86_AVX)
#    define EVE_ABI_API(next) next(G)
#  elif defined(SPY_SIMD_IS_X86_SSE4_2)
#    define EVE_ABI_API(next) next(F)
#  elif defined(SPY_SIMD_IS_X86_SSE4_1)
#    define EVE_ABI_API(next) next(E)
#  elif defined(SPY_SIMD_IS_X86_SSSE3)
#    define EVE_ABI_API(next) next(D)
#  elif defined(SPY_SIMD_IS_X86_SSE3)
#    define EVE_ABI_API(next) next(C)
#  elif defined(SPY_SIMD_IS_X86_SSE2)
#    define EVE_ABI_API(next) next(B)
#  elif defined(SPY_SIMD_IS_ARM_FIXED_SVE2) && __ARM_FEATURE_SVE_BITS == 128
#    define EVE_ABI_API(next) next(P)
#  elif defined(SPY_SIMD_IS_ARM_FIXED_SVE2) && __ARM_FEATURE_SVE_BITS == 256
#    define EVE_ABI_API(next) next(Q)
#  elif defined(SPY_SIMD_IS_ARM_FIXED_SVE2) && __ARM_FEATURE_SVE_BITS == 512
#    define EVE_ABI_API(next) next(R)
#  elif defined(SPY_SIMD_IS_ARM_FIXED_SVE) && __ARM_FEATURE_SVE_BITS == 128
#    define EVE_ABI_API(next) next(M)
#  elif defined(SPY_SIMD_IS_ARM_FIXED_SVE) && __ARM_FEATURE_SVE_BITS == 256
#    define EVE_ABI_API(next) next(N)
#  elif defined(SPY_SIMD_IS_ARM_FIXED_SVE) && __ARM_FEATURE_SVE_BITS == 512
#    define EVE_ABI_API(next) next(O)
#  elif defined(SPY_SIMD_IS_ARM_ASIMD)
#    define EVE_ABI_API(next) next(L)
#  elif defined(SPY_SIMD_IS_ARM_NEON)
#    define EVE_ABI_API(next) next(K)
#  elif defined(SPY_SIMD_IS_PPC_VSX_3_01)
#    define EVE_ABI_API(next) next(Td)
#  elif defined(SPY_SIMD_IS_PPC_VSX_3_00)
#    define EVE_ABI_API(next) next(Tc)
#  elif defined(SPY_SIMD_IS_PPC_VSX_2_07)
#    define EVE_ABI_API(next) next(Tb)
#  elif defined(SPY_SIMD_IS_PPC_VSX_2_06)
#    define EVE_ABI_API(next) next(Ta)
#  elif defined(SPY_SIMD_IS_PPC_VMX_3_01)
#    define EVE_ABI_API(next) next(Sf)
#  elif defined(SPY_SIMD_IS_PPC_VMX_3_00)
#    define EVE_ABI_API(next) next(Se)
#  elif defined(SPY_SIMD_IS_PPC_VMX_2_07)
#    define EVE_ABI_API(next) next(Sd)
#  elif defined(SPY_SIMD_IS_PPC_VMX_2_06)
#    define EVE_ABI_API(next) next(Sc)
#  elif defined(SPY_SIMD_IS_PPC_VMX_2_05)
#    define EVE_ABI_API(next) next(Sb)
#  elif defined(SPY_SIMD_IS_PPC_VMX_2_03)
#    define EVE_ABI_API(next) next(Sa)
#  elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 64
#    define EVE_ABI_API(next) next(Ua)
#  elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 128
#    define EVE_ABI_API(next) next(Ub)
#  elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 256
#    define EVE_ABI_API(next) next(Uc)
#  elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 512
#    define EVE_ABI_API(next) next(Ud)
#  elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 1024
#    define EVE_ABI_API(next) next(Ue)
#  elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 2048
#    define EVE_ABI_API(next) next(Uf)
#  elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 4096
#    define EVE_ABI_API(next) next(Ug)
#  elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 8192
#    define EVE_ABI_API(next) next(Uh)
#  elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 16384
#    define EVE_ABI_API(next) next(Ui)
#  elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 32768
#    define EVE_ABI_API(next) next(Uj)
#  elif defined(SPY_SIMD_IS_RISCV_FIXED_RVV) && __riscv_v_fixed_vlen == 65536
#    define EVE_ABI_API(next) next(Uk)
#  else
#    error "[EVE] - Unsupported SIMD extension"
#  endif

#  if defined(EVE_HAS_HARDWARE_FMA)
#    define EVE_ABI_FMA 1
#  else
#    define EVE_ABI_FMA 0
#  endif

#  if !defined(EVE_NATIVE_FP16)
#    define EVE_ABI_NO_FP16     1
#    define EVE_ABI_FP16_CVT    0
#    define EVE_ABI_FP16_SCALAR 0
#    define EVE_ABI_FP16_VECTOR 0
#  else
#    define EVE_ABI_NO_FP16 0
#    if defined(SPY_SUPPORTS_FP16_VECTOR_CONVERSION) && !defined(SPY_SIMD_IS_X86_AVX512)
#      define EVE_ABI_FP16_CVT 1
#    else
#      define EVE_ABI_FP16_CVT 0
#    endif
#    if defined(SPY_SUPPORTS_FP16_SCALAR_OPS)
#      define EVE_ABI_FP16_SCALAR 1
#    else
#      define EVE_ABI_FP16_SCALAR 0
#    endif
#    if defined(SPY_SUPPORTS_FP16_VECTOR_OPS)
#      define EVE_ABI_FP16_VECTOR 1
#    else
#      define EVE_ABI_FP16_VECTOR 0
#    endif
#  endif

#  if defined(EVE_NO_DENORMALS)
#    define EVE_ABI_NO_DENORMALS 1
#  else
#    define EVE_ABI_NO_DENORMALS 0
#  endif

#  if defined(EVE_NO_NANS)
#    define EVE_ABI_NO_NANS 1
#  else
#    define EVE_ABI_NO_NANS 0
#  endif

#  if defined(EVE_NO_INFINITIES)
#    define EVE_ABI_NO_INFINITIES 1
#  else
#    define EVE_ABI_NO_INFINITIES 0
#  endif

#  if defined(EVE_NO_MINUSZERO)
#    define EVE_ABI_NO_MINUSZERO 1
#  else
#    define EVE_ABI_NO_MINUSZERO 0
#  endif

#  define EVE_ABI_D00000(tag) tag##a
#  define EVE_ABI_D00001(tag) tag##b
#  define EVE_ABI_D00010(tag) tag##c
#  define EVE_ABI_D00011(tag) tag##d
#  define EVE_ABI_D00100(tag) tag##e
#  define EVE_ABI_D00101(tag) tag##f
#  define EVE_ABI_D00110(tag) tag##g
#  define EVE_ABI_D00111(tag) tag##h
#  define EVE_ABI_D01000(tag) tag##i
#  define EVE_ABI_D01001(tag) tag##j
#  define EVE_ABI_D01010(tag) tag##k
#  define EVE_ABI_D01011(tag) tag##l
#  define EVE_ABI_D01100(tag) tag##m
#  define EVE_ABI_D01101(tag) tag##n
#  define EVE_ABI_D01110(tag) tag##o
#  define EVE_ABI_D01111(tag) tag##p
#  define EVE_ABI_D10000(tag) tag##q
#  define EVE_ABI_D10001(tag) tag##r
#  define EVE_ABI_D10010(tag) tag##s
#  define EVE_ABI_D10011(tag) tag##t
#  define EVE_ABI_D10100(tag) tag##u
#  define EVE_ABI_D10101(tag) tag##v
#  define EVE_ABI_D10110(tag) tag##w
#  define EVE_ABI_D10111(tag) tag##x
#  define EVE_ABI_D11000(tag) tag##y
#  define EVE_ABI_D11001(tag) tag##z
#  define EVE_ABI_D11010(tag) tag##A
#  define EVE_ABI_D11011(tag) tag##B
#  define EVE_ABI_D11100(tag) tag##C
#  define EVE_ABI_D11101(tag) tag##D
#  define EVE_ABI_D11110(tag) tag##E
#  define EVE_ABI_D11111(tag) tag##F

#  define EVE_ABI_LOOKUP_(a, b, c, d, e) EVE_ABI_D##a##b##c##d##e
#  define EVE_ABI_LOOKUP(...)            EVE_ABI_LOOKUP_(__VA_ARGS__)
#  define EVE_ABI_DIGIT(tag, ...)        EVE_ABI_LOOKUP(__VA_ARGS__)(tag)

#  define EVE_ABI_FP_BITS 0, EVE_ABI_NO_MINUSZERO, EVE_ABI_NO_INFINITIES, EVE_ABI_NO_NANS, EVE_ABI_NO_DENORMALS

#  if EVE_ABI_NO_DENORMALS || EVE_ABI_NO_NANS || EVE_ABI_NO_INFINITIES || EVE_ABI_NO_MINUSZERO
#    define EVE_ABI_HAS_FP_SEMANTICS 1
#  else
#    define EVE_ABI_HAS_FP_SEMANTICS 0
#  endif

#  if defined(SPY_SIMD_IS_X86_AVX512)

#    if defined(SPY_SIMD_IS_X86_AVX512_IFMA)
#      define EVE_ABI_IFMA 1
#    else
#      define EVE_ABI_IFMA 0
#    endif

#    if defined(SPY_SIMD_IS_X86_AVX512_VBMI)
#      define EVE_ABI_VBMI 1
#    else
#      define EVE_ABI_VBMI 0
#    endif

#    if defined(SPY_SIMD_IS_X86_AVX512_VBMI2)
#      define EVE_ABI_VBMI2 1
#    else
#      define EVE_ABI_VBMI2 0
#    endif

#    if defined(SPY_SIMD_IS_X86_AVX512_VNNI)
#      define EVE_ABI_VNNI 1
#    else
#      define EVE_ABI_VNNI 0
#    endif

#    if defined(SPY_SIMD_IS_X86_AVX512_BF16)
#      define EVE_ABI_BF16 1
#    else
#      define EVE_ABI_BF16 0
#    endif

#    if defined(SPY_SIMD_IS_X86_AVX512_BITALG)
#      define EVE_ABI_BITALG 1
#    else
#      define EVE_ABI_BITALG 0
#    endif

#    if defined(SPY_SIMD_IS_X86_AVX512_POPCNTDQ)
#      define EVE_ABI_VPOPCNTDQ 1
#    else
#      define EVE_ABI_VPOPCNTDQ 0
#    endif

#    if defined(SPY_SIMD_IS_X86_AVX512_VP2INTERSECT)
#      define EVE_ABI_VP2INTERSECT 1
#    else
#      define EVE_ABI_VP2INTERSECT 0
#    endif

#    if defined(EVE_AVX512_DEFAULT_64_BYTES)
#      define EVE_ABI_W64 1
#    else
#      define EVE_ABI_W64 0
#    endif

#    define EVE_ABI_BITS1 EVE_ABI_BF16, EVE_ABI_VNNI, EVE_ABI_VBMI2, EVE_ABI_VBMI, EVE_ABI_IFMA
#    define EVE_ABI_BITS2 EVE_ABI_NO_FP16, EVE_ABI_FP16_VECTOR, EVE_ABI_VP2INTERSECT, EVE_ABI_VPOPCNTDQ, EVE_ABI_BITALG
#    define EVE_ABI_BITS3 0, 0, 0, 0, EVE_ABI_W64

#    define EVE_ABI_TAG1 EVE_ABI_API(EVE_ABI_LOOKUP(EVE_ABI_BITS1))
#    define EVE_ABI_TAG2 EVE_ABI_DIGIT(EVE_ABI_TAG1, EVE_ABI_BITS2)
#    define EVE_ABI_TAG3 EVE_ABI_DIGIT(EVE_ABI_TAG2, EVE_ABI_BITS3)

#    if EVE_ABI_HAS_FP_SEMANTICS
#      define EVE_ABI_NAMESPACE EVE_ABI_DIGIT(EVE_ABI_TAG3, EVE_ABI_FP_BITS)
#    elif EVE_ABI_W64
#      define EVE_ABI_NAMESPACE EVE_ABI_TAG3
#    elif EVE_ABI_BITALG || EVE_ABI_VPOPCNTDQ || EVE_ABI_VP2INTERSECT || EVE_ABI_FP16_VECTOR || EVE_ABI_NO_FP16
#      define EVE_ABI_NAMESPACE EVE_ABI_TAG2
#    else
#      define EVE_ABI_NAMESPACE EVE_ABI_TAG1
#    endif

#  else

#    define EVE_ABI_BITS1 EVE_ABI_NO_FP16, EVE_ABI_FP16_SCALAR, EVE_ABI_FP16_VECTOR, EVE_ABI_FP16_CVT, EVE_ABI_FMA
#    define EVE_ABI_TAG1  EVE_ABI_API(EVE_ABI_LOOKUP(EVE_ABI_BITS1))

#    if EVE_ABI_HAS_FP_SEMANTICS
#      define EVE_ABI_NAMESPACE EVE_ABI_DIGIT(EVE_ABI_TAG1, EVE_ABI_FP_BITS)
#    else
#      define EVE_ABI_NAMESPACE EVE_ABI_TAG1
#    endif

#  endif

#endif

//==================================================================================================
//! @addtogroup eve_arch
//! @{
//!   @def EVE_NAMESPACE
//!   @brief Opens the namespace that holds all of **EVE**, `eve::EVE_ABI_NAMESPACE`, for customization
//!   purposes.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   `EVE_NAMESPACE` expands to `namespace eve::inline EVE_ABI_NAMESPACE`. On recent compilers, you can
//!   simply reopen `namespace eve` or `namespace eve::_`. If your compiler doesn't implement
//!   [CWG 2061](https://cplusplus.github.io/CWG/issues/2061.html), use `EVE_NAMESPACE` or
//!   `EVE_NAMESPACE::_` instead as a workaround.
//! @}
//==================================================================================================
#if defined(EVE_DOXYGEN_INVOKED)
#  define EVE_NAMESPACE namespace eve
#else
#  define EVE_NAMESPACE namespace eve::inline EVE_ABI_NAMESPACE
#endif
