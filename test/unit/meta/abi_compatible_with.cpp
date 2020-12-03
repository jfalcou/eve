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

TTS_CASE_TPL( "Check that wide<T,N> satisfies abi_compatible_with with their own ABI"
            , TTS_NUMERIC_TYPES
            )
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT((eve::abi_compatible_with<wide<T>          , typename wide<T>::abi_type>          ));
  TTS_EXPECT((eve::abi_compatible_with<logical<wide<T>> , typename logical<wide<T>>::abi_type> ));
}

#if defined(SPY_SIMD_IS_X86)
TTS_CASE_TPL( "Check that wide<T,N,x86*> satisfies abi_compatible_with with any X86 ABI"
            , TTS_NUMERIC_TYPES
            )
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT((eve::abi_compatible_with<wide<T>          , eve::x86_128_ , eve::x86_256_> ));
  TTS_EXPECT((eve::abi_compatible_with<logical<wide<T>> , eve::x86_128_ , eve::x86_256_> ));
}

TTS_CASE_TPL( "Check that wide<T,N,x86*> does not satisfy abi_compatible_with with other ABI"
            , TTS_NUMERIC_TYPES
            )
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT_NOT((eve::abi_compatible_with<wide<T>          , eve::arm_64_ , eve::arm_128_> ));
  TTS_EXPECT_NOT((eve::abi_compatible_with<wide<T>          , eve::ppc_> ));
  TTS_EXPECT_NOT((eve::abi_compatible_with<logical<wide<T>> , eve::arm_64_ , eve::arm_128_> ));
  TTS_EXPECT_NOT((eve::abi_compatible_with<logical<wide<T>> , eve::ppc_> ));
}
#elif defined(SPY_SIMD_IS_PPC)
TTS_CASE_TPL( "Check that wide<T,N,ppc*> satisfies abi_compatible_with with any PPC ABI"
            , TTS_NUMERIC_TYPES
            )
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT((eve::abi_compatible_with<wide<T>          , eve::ppc_> ));
  TTS_EXPECT((eve::abi_compatible_with<logical<wide<T>> , eve::ppc_> ));
}

TTS_CASE_TPL( "Check that wide<T,N,ppc*> does not satisfy abi_compatible_with with other ABI"
            , TTS_NUMERIC_TYPES
            )
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT_NOT((eve::abi_compatible_with<wide<T>          , eve::arm_64_ , eve::arm_128_  > ));
  TTS_EXPECT_NOT((eve::abi_compatible_with<wide<T>          , eve::x86_128_ , eve::x86_256_ > ));
  TTS_EXPECT_NOT((eve::abi_compatible_with<logical<wide<T>> , eve::arm_64_ , eve::arm_128_  > ));
  TTS_EXPECT_NOT((eve::abi_compatible_with<logical<wide<T>> , eve::x86_128_ , eve::x86_256_ > ));
}
#elif defined(SPY_SIMD_IS_ARM)
TTS_CASE_TPL( "Check that wide<T,N,arm*> satisfies abi_compatible_with with any ARM ABI"
            , TTS_NUMERIC_TYPES
            )
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT((eve::abi_compatible_with<wide<T>          , eve::arm_64_ , eve::arm_128_> ));
  TTS_EXPECT((eve::abi_compatible_with<logical<wide<T>> , eve::arm_64_ , eve::arm_128_> ));
}

TTS_CASE_TPL( "Check that wide<T,N,arm*> does not satisfy abi_compatible_with with other ABI"
            , TTS_NUMERIC_TYPES
            )
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT_NOT((eve::abi_compatible_with<wide<T>          , eve::x86_128_ , eve::x86_256_ > ));
  TTS_EXPECT_NOT((eve::abi_compatible_with<wide<T>          , eve::ppc_> ));
  TTS_EXPECT_NOT((eve::abi_compatible_with<logical<wide<T>> , eve::x86_128_ , eve::x86_256_ > ));
  TTS_EXPECT_NOT((eve::abi_compatible_with<logical<wide<T>> , eve::ppc_> ));
}
#endif
