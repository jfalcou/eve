//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/abi.hpp>
#include <eve/wide.hpp>
#include <eve/logical.hpp>

template<typename T>
using extra_wide = eve::wide<T,eve::fixed<2*eve::expected_cardinal_v<T>>>;

template<typename T>
using small_wide = eve::wide<T,eve::fixed<eve::expected_cardinal_v<T>/2>>;

template<typename T>
using tiny_wide = eve::wide<T,eve::fixed<1>>;

#if defined(SPY_SIMD_IS_X86)
TTS_CASE_TPL( "Check that wide<T,N,x86*> satisfies native_simd_for_abi with any X86 ABI"
            , TTS_NUMERIC_TYPES
            )
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT((eve::native_simd_for_abi<wide<T>          , eve::x86_128_ , eve::x86_256_> ));
  TTS_EXPECT((eve::native_simd_for_abi<logical<wide<T>> , eve::x86_128_ , eve::x86_256_> ));
}

TTS_CASE_TPL( "Check that wide<T,N,x86*> does not satisfy native_simd_for_abi with other ABI"
            , TTS_NUMERIC_TYPES
            )
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT_NOT((eve::native_simd_for_abi<wide<T>          , eve::arm_64_ , eve::arm_128_> ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<wide<T>          , eve::ppc_> ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<wide<T>> , eve::arm_64_ , eve::arm_128_> ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<wide<T>> , eve::ppc_> ));
}
#elif defined(SPY_SIMD_IS_PPC)
TTS_CASE_TPL( "Check that wide<T,N,ppc*> satisfies native_simd_for_abi with any PPC ABI"
            , TTS_NUMERIC_TYPES
            )
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT((eve::native_simd_for_abi<wide<T>          , eve::ppc_> ));
  TTS_EXPECT((eve::native_simd_for_abi<logical<wide<T>> , eve::ppc_> ));
}

TTS_CASE_TPL( "Check that wide<T,N,ppc*> does not satisfy native_simd_for_abi with other ABI"
            , TTS_NUMERIC_TYPES
            )
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT_NOT((eve::native_simd_for_abi<wide<T>          , eve::arm_64_ , eve::arm_128_  > ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<wide<T>          , eve::x86_128_ , eve::x86_256_ > ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<wide<T>> , eve::arm_64_ , eve::arm_128_  > ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<wide<T>> , eve::x86_128_ , eve::x86_256_ > ));
}
#elif defined(SPY_SIMD_IS_ARM)
TTS_CASE_TPL( "Check that wide<T,N,arm*> satisfies native_simd_for_abi with any ARM ABI"
            , TTS_NUMERIC_TYPES
            )
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT((eve::native_simd_for_abi<wide<T>          , eve::arm_64_ , eve::arm_128_> ));
  TTS_EXPECT((eve::native_simd_for_abi<logical<wide<T>> , eve::arm_64_ , eve::arm_128_> ));
}

TTS_CASE_TPL( "Check that wide<T,N,arm*> does not satisfy native_simd_for_abi with other ABI"
            , TTS_NUMERIC_TYPES
            )
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT_NOT((eve::native_simd_for_abi<wide<T>          , eve::x86_128_ , eve::x86_256_ > ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<wide<T>          , eve::ppc_> ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<wide<T>> , eve::x86_128_ , eve::x86_256_ > ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<wide<T>> , eve::ppc_> ));
}
#endif

TTS_CASE_TPL( "Check that wide<T,k*N> does not satisfy any native_simd_for_abi"
            , TTS_NUMERIC_TYPES
            )
{
  using eve::logical;

  TTS_EXPECT_NOT((eve::native_simd_for_abi<extra_wide<T>, eve::x86_128_ , eve::x86_256_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<extra_wide<T>, eve::arm_64_ , eve::arm_128_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<extra_wide<T>, eve::ppc_>  ));

  TTS_EXPECT_NOT((eve::native_simd_for_abi<small_wide<T>, eve::x86_128_ , eve::x86_256_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<small_wide<T>, eve::arm_64_ , eve::arm_128_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<small_wide<T>, eve::ppc_>  ));

  TTS_EXPECT_NOT((eve::native_simd_for_abi<tiny_wide<T>, eve::x86_128_ , eve::x86_256_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<tiny_wide<T>, eve::arm_64_ , eve::arm_128_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<tiny_wide<T>, eve::ppc_>  ));

  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<extra_wide<T>>, eve::x86_128_ , eve::x86_256_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<extra_wide<T>>, eve::arm_64_ , eve::arm_128_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<extra_wide<T>>, eve::ppc_>  ));

  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<small_wide<T>>, eve::x86_128_ , eve::x86_256_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<small_wide<T>>, eve::arm_64_ , eve::arm_128_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<small_wide<T>>, eve::ppc_>  ));

  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<tiny_wide<T>>, eve::x86_128_ , eve::x86_256_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<tiny_wide<T>>, eve::arm_64_ , eve::arm_128_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<tiny_wide<T>>, eve::ppc_>  ));
}
