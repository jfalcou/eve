//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/abi.hpp>
#include <eve/wide.hpp>
#include <eve/logical.hpp>

template<typename T> using extra_wide = eve::wide<T,eve::fixed<2*eve::expected_cardinal_v<T>>>;
template<typename T> using tiny_wide  = eve::wide<T,eve::fixed<1>>;

#if !defined(EVE_NO_SIMD)
#if defined(SPY_SIMD_IS_X86)
TTS_CASE_TPL( "Check that wide<T,N> satisfies native_simd_for_abi with any X86 ABI"
            , ::tts::arithmetic_types
            )
<typename T>(::tts::type<T>)
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT((eve::native_simd_for_abi<wide<T>          , eve::x86_128_ , eve::x86_256_, eve::x86_512_> ));
  TTS_EXPECT((eve::native_simd_for_abi<logical<wide<T>> , eve::x86_128_ , eve::x86_256_, eve::x86_512_> ));
};

TTS_CASE_TPL( "Check that wide<T,N> does not satisfy native_simd_for_abi with other ABI"
            , ::tts::arithmetic_types
            )
<typename T>(::tts::type<T>)
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT_NOT((eve::native_simd_for_abi<wide<T>          , eve::arm_64_ , eve::arm_128_> ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<wide<T>          , eve::ppc_> ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<wide<T>> , eve::arm_64_ , eve::arm_128_> ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<wide<T>> , eve::ppc_> ));
};
#elif defined(SPY_SIMD_IS_PPC)
TTS_CASE_TPL( "Check that wide<T,N,ppc*> satisfies native_simd_for_abi with any PPC ABI"
            , ::tts::arithmetic_types
            )
<typename T>(::tts::type<T>)
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT((eve::native_simd_for_abi<wide<T>          , eve::ppc_> ));
  TTS_EXPECT((eve::native_simd_for_abi<logical<wide<T>> , eve::ppc_> ));
};

TTS_CASE_TPL( "Check that wide<T,N,ppc*> does not satisfy native_simd_for_abi with other ABI"
            , ::tts::arithmetic_types
            )
<typename T>(::tts::type<T>)
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT_NOT((eve::native_simd_for_abi<wide<T>          , eve::arm_64_ , eve::arm_128_  > ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<wide<T>          , eve::x86_128_ , eve::x86_256_, eve::x86_512_ > ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<wide<T>> , eve::arm_64_ , eve::arm_128_  > ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<wide<T>> , eve::x86_128_ , eve::x86_256_, eve::x86_512_ > ));
};
#elif defined(SPY_SIMD_IS_ARM_FIXED_SVE)
TTS_CASE_TPL( "Check that wide<T,N> satisfies native_simd_for_abi with any ARM SVE ABI"
            , TTS_NUMERIC_TYPES
            )
<typename T>(::tts::type<T>)
{
  using eve::wide;
  using eve::logical;

  if constexpr( eve::current_api.width == 128)
  {
    TTS_EXPECT((eve::native_simd_for_abi<wide<T>          , eve::arm_sve_128_> ));
    TTS_EXPECT((eve::native_simd_for_abi<logical<wide<T>> , eve::arm_sve_128_> ));
  }
  else if constexpr( eve::current_api.width == 256)
  {
    TTS_EXPECT((eve::native_simd_for_abi<wide<T>          , eve::arm_sve_256_> ));
    TTS_EXPECT((eve::native_simd_for_abi<logical<wide<T>> , eve::arm_sve_256_> ));
  }
  else if constexpr( eve::current_api.width == 512)
  {
    TTS_EXPECT((eve::native_simd_for_abi<wide<T>          , eve::arm_sve_512_> ));
    TTS_EXPECT((eve::native_simd_for_abi<logical<wide<T>> , eve::arm_sve_512_> ));
  }
};
#elif defined(SPY_SIMD_IS_ARM)
TTS_CASE_TPL( "Check that wide<T,N> satisfies native_simd_for_abi with any ARM ABI"
            , ::tts::arithmetic_types
            )
<typename T>(::tts::type<T>)
{
  using eve::wide;
  using eve::logical;

  if constexpr( eve::current_api >= eve::asimd )
  {
    TTS_EXPECT((eve::native_simd_for_abi<wide<T>          , eve::arm_64_ , eve::arm_128_> ));
    TTS_EXPECT((eve::native_simd_for_abi<logical<wide<T>> , eve::arm_64_ , eve::arm_128_> ));
  }
  else
  {
    if constexpr( std::same_as<T,double> )
    {
      TTS_EXPECT_NOT((eve::native_simd_for_abi<wide<T>          , eve::arm_64_ , eve::arm_128_> ));
      TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<wide<T>> , eve::arm_64_ , eve::arm_128_> ));
    }
    else
    {
      TTS_EXPECT((eve::native_simd_for_abi<wide<T>          , eve::arm_64_ , eve::arm_128_> ));
      TTS_EXPECT((eve::native_simd_for_abi<logical<wide<T>> , eve::arm_64_ , eve::arm_128_> ));
    }
  }
};

TTS_CASE_TPL( "Check that wide<T,N> does not satisfy native_simd_for_abi with other ABI"
            , ::tts::arithmetic_types
            )
<typename T>(::tts::type<T>)
{
  using eve::wide;
  using eve::logical;

  TTS_EXPECT_NOT((eve::native_simd_for_abi<wide<T>          , eve::x86_128_ , eve::x86_256_, eve::x86_512_ > ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<wide<T>          , eve::ppc_> ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<wide<T>> , eve::x86_128_ , eve::x86_256_, eve::x86_512_ > ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<wide<T>> , eve::ppc_> ));
};
#endif
#endif

TTS_CASE_TPL( "Check that wide<T,k*N> does not satisfy any native_simd_for_abi"
            , ::tts::arithmetic_types
            )
<typename T>(::tts::type<T>)
{
  using eve::logical;

  TTS_EXPECT_NOT((eve::native_simd_for_abi<extra_wide<T>, eve::x86_128_, eve::x86_256_, eve::x86_512_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<extra_wide<T>, eve::arm_64_ , eve::arm_128_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<extra_wide<T>, eve::arm_sve_128_, eve::arm_sve_256_, eve::arm_sve_512_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<extra_wide<T>, eve::ppc_>  ));

  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<extra_wide<T>>, eve::x86_128_ , eve::x86_256_, eve::x86_512_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<extra_wide<T>>, eve::arm_64_ , eve::arm_128_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<extra_wide<T>>, eve::arm_sve_128_, eve::arm_sve_256_, eve::arm_sve_512_>  ));
  TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<extra_wide<T>>, eve::ppc_>  ));

  if constexpr( eve::cardinal_v<tiny_wide<T>> != 1)
  {
    TTS_EXPECT_NOT((eve::native_simd_for_abi<tiny_wide<T>, eve::x86_128_ , eve::x86_256_, eve::x86_512_> ));
    TTS_EXPECT_NOT((eve::native_simd_for_abi<tiny_wide<T>, eve::arm_64_ , eve::arm_128_>  ));
    TTS_EXPECT_NOT((eve::native_simd_for_abi<tiny_wide<T>, eve::arm_sve_128_, eve::arm_sve_256_, eve::arm_sve_512_> ));
    TTS_EXPECT_NOT((eve::native_simd_for_abi<tiny_wide<T>, eve::ppc_>  ));

    TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<tiny_wide<T>>, eve::x86_128_ , eve::x86_256_, eve::x86_512_>  ));
    TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<tiny_wide<T>>, eve::arm_64_ , eve::arm_128_>  ));
    TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<tiny_wide<T>>, eve::arm_sve_128_, eve::arm_sve_256_, eve::arm_sve_512_> ));
    TTS_EXPECT_NOT((eve::native_simd_for_abi<logical<tiny_wide<T>>, eve::ppc_>  ));
  }
};
