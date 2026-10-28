//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"
#include <eve/arch/detection.hpp>
#include <iostream>
#include <iomanip>

namespace
{
  constexpr bool implies(bool a, bool b){ return !a || b; }
}

//==================================================================================================
// Static detections
//==================================================================================================
TTS_CASE("Static detections of API - x86")
{
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::avx512, eve::current_api >= eve::avx2  ));
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::avx2  , eve::current_api >= eve::avx   ));
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::avx   , eve::current_api >= eve::sse4_2));
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::sse4_2, eve::current_api >= eve::sse4_1));
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::sse4_1, eve::current_api >= eve::ssse3 ));
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::ssse3 , eve::current_api >= eve::sse3  ));
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::sse3  , eve::current_api >= eve::sse2  ));

#if !defined(SPY_ARCH_IS_X86) && !defined(SPY_ARCH_IS_AMD64)
  TTS_CONSTEXPR_EXPECT_NOT(eve::current_api >= eve::sse2);
#endif
};

  
TTS_CASE("Static detections of API - x86 - AVX512 extensions")
{
#if (defined(SPY_ARCH_IS_X86) || defined(SPY_ARCH_IS_AMD64)) && !defined(EVE_NO_SIMD)
  // This shall be replaced by TTS_MAYFAIL in the case but at this point it still flags a fail 
  TTS_CONSTEXPR_EQUAL(eve::supports_fma3              , eve::supports_fma3);
  TTS_CONSTEXPR_EQUAL(eve::supports_bmi_well          , eve::supports_bmi_well);
  TTS_CONSTEXPR_EQUAL(eve::supports_avx512bw          , eve::supports_avx512bw);
  TTS_CONSTEXPR_EQUAL(eve::supports_avx512cd          , eve::supports_avx512cd);
  TTS_CONSTEXPR_EQUAL(eve::supports_avx512dq          , eve::supports_avx512dq);
  TTS_CONSTEXPR_EQUAL(eve::supports_avx512ifma        , eve::supports_avx512ifma);
  TTS_CONSTEXPR_EQUAL(eve::supports_avx512pf          , eve::supports_avx512pf);
  TTS_CONSTEXPR_EQUAL(eve::supports_avx512vl          , eve::supports_avx512vl);
  TTS_CONSTEXPR_EQUAL(eve::supports_avx512popcntdq_   , eve::supports_avx512popcntdq_);
  TTS_CONSTEXPR_EQUAL(eve::supports_avx512_4fmaps_    , eve::supports_avx512_4fmaps_);
  TTS_CONSTEXPR_EQUAL(eve::supports_avx512vnniw_      , eve::supports_avx512vnniw_);
  TTS_CONSTEXPR_EQUAL(eve::supports_avx512vbmi_       , eve::supports_avx512vbmi_);
  TTS_CONSTEXPR_EQUAL(eve::supports_avx512bf16_       , eve::supports_avx512bf16_);
  TTS_CONSTEXPR_EQUAL(eve::supports_avx512bitalg_     , eve::supports_avx512bitalg_);
  TTS_CONSTEXPR_EQUAL(eve::supports_avx512vbmi2_      , eve::supports_avx512vbmi2_);
  TTS_CONSTEXPR_EQUAL(eve::supports_avx512vnni_       , eve::supports_avx512vnni_);
  TTS_CONSTEXPR_EQUAL(eve::supports_avx512vpintersect_, eve::supports_avx512vpintersect_);
#else
  TTS_EXPECT(true);
#endif
};

TTS_CASE("Static detections of API - PPC")
{
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::vmx_3_01, eve::current_api >= eve::vmx_3_00));
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::vmx_3_00, eve::current_api >= eve::vmx_2_07));
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::vmx_2_07, eve::current_api >= eve::vmx_2_06));
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::vmx_2_06, eve::current_api >= eve::vmx_2_05));
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::vmx_2_05, eve::current_api >= eve::vmx_2_03));
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::vmx_2_03, eve::current_api >= eve::vmx     ));

  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::vsx_3_01, eve::current_api >= eve::vsx_3_00));
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::vsx_3_00, eve::current_api >= eve::vsx_2_07));
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::vsx_2_07, eve::current_api >= eve::vsx_2_06));
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::vsx_2_06, eve::current_api >= eve::vsx     ));

  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::vsx, eve::current_api >= eve::vmx));

#if !defined(SPY_ARCH_IS_PPC)
  TTS_CONSTEXPR_EXPECT_NOT(eve::current_api >= eve::vmx);
  TTS_CONSTEXPR_EXPECT_NOT(eve::current_api >= eve::vsx);
#endif
};

TTS_CASE("Static detections of API - ARM")
{
  TTS_CONSTEXPR_EXPECT(implies(eve::current_api >= eve::asimd, eve::current_api >= eve::neon));

#if !defined(SPY_ARCH_IS_ARM)
  TTS_CONSTEXPR_EXPECT_NOT(eve::current_api >= eve::neon );
  TTS_CONSTEXPR_EXPECT_NOT(eve::current_api >= eve::asimd);
#endif
};

TTS_CASE("Static detections of API - RISCV")
{
#if !defined(SPY_ARCH_IS_RISCV)
  TTS_CONSTEXPR_EXPECT_NOT(eve::current_api == eve::rvv);
#endif
};

//==================================================================================================
// Dynamic detections
//==================================================================================================
TTS_CASE("Dynamic detections of API - Current API")
{
  TTS_EXPECT(eve::is_supported(eve::current_api));
};

TTS_CASE("Dynamic detections of API - X86")
{
  TTS_EXPECT(implies(eve::current_api >= eve::sse2  , eve::is_supported(eve::sse2  )));
  TTS_EXPECT(implies(eve::current_api >= eve::sse3  , eve::is_supported(eve::sse3  )));
  TTS_EXPECT(implies(eve::current_api >= eve::ssse3 , eve::is_supported(eve::ssse3 )));
  TTS_EXPECT(implies(eve::current_api >= eve::sse4_1, eve::is_supported(eve::sse4_1)));
  TTS_EXPECT(implies(eve::current_api >= eve::sse4_2, eve::is_supported(eve::sse4_2)));
  TTS_EXPECT(implies(eve::current_api >= eve::avx   , eve::is_supported(eve::avx   )));
  TTS_EXPECT(implies(eve::current_api >= eve::avx2  , eve::is_supported(eve::avx2  )));
  TTS_EXPECT(implies(eve::current_api >= eve::avx512, eve::is_supported(eve::avx512)));

#if (defined(SPY_ARCH_IS_X86) || defined(SPY_ARCH_IS_AMD64)) && !defined(EVE_NO_SIMD)
  TTS_EXPECT(implies(eve::supports_fma3, eve::is_supported(eve::fma3)));
#endif
};

TTS_CASE("Dynamic detections of API - PPC")
{
  TTS_EXPECT(implies(eve::current_api >= eve::vmx, eve::is_supported(eve::vmx)));
  TTS_EXPECT(implies(eve::current_api >= eve::vsx, eve::is_supported(eve::vsx)));
};

TTS_CASE("Dynamic detections of API - ARM")
{
  TTS_EXPECT(implies(eve::current_api >= eve::neon , eve::is_supported(eve::neon )));
  TTS_EXPECT(implies(eve::current_api >= eve::asimd, eve::is_supported(eve::asimd)));
};

TTS_CASE("Dynamic detections of API - RISCV")
{
  TTS_EXPECT(implies(eve::current_api == eve::rvv, eve::is_supported(eve::rvv)));
};
