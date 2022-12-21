//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/complex.hpp>


TTS_CASE_TPL( "Check eve::like behavior for eve::complex"
            , eve::test::scalar::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using eve::wide;
  using eve::fixed;
  using eve::complex;

  TTS_CONSTEXPR_EXPECT((eve::like<T                        , complex<T>>));
  TTS_CONSTEXPR_EXPECT((eve::like<int                      , complex<T>>));
  TTS_CONSTEXPR_EXPECT((eve::like<complex<T>               , complex<T>>));
  TTS_CONSTEXPR_EXPECT((eve::like<wide<T>                  , complex<T>>));
  TTS_CONSTEXPR_EXPECT((eve::like<wide<T,fixed<1>>         , complex<T>>));
  TTS_CONSTEXPR_EXPECT((eve::like<wide<complex<T>>         , complex<T>>));
  TTS_CONSTEXPR_EXPECT((eve::like<wide<complex<T>,fixed<1>>, complex<T>>));
  TTS_CONSTEXPR_EXPECT_NOT((eve::like<wide<int>            , complex<T>>));
};

TTS_CASE_TPL( "Check complex basic operator overload properties"
            , eve::test::scalar::ieee_reals
            )
<typename T>(tts::type<T>)
{
  T                                st;
  eve::complex<T>                  ct;
  eve::wide<T>                    wst;
  eve::wide<eve::as_integer_t<T>>  wi;
  eve::wide<eve::complex<T>>      wct;

  // scalar complex operator supports
  TTS_EXPECT_COMPILES     ( ct, st , { ct +  st; });
  TTS_EXPECT_COMPILES     ( ct     , { ct +  ct; });
  TTS_EXPECT_COMPILES     ( ct, wst, { ct + wst; });
  TTS_EXPECT_COMPILES     ( ct, wct, { ct + wct; });
  TTS_EXPECT_NOT_COMPILES ( ct, wi , { ct +  wi; });
  TTS_EXPECT_COMPILES     ( ct, st , { ct -  st; });
  TTS_EXPECT_COMPILES     ( ct     , { ct -  ct; });
  TTS_EXPECT_COMPILES     ( ct, wst, { ct - wst; });
  TTS_EXPECT_COMPILES     ( ct, wct, { ct - wct; });
  TTS_EXPECT_NOT_COMPILES ( ct, wi , { ct -  wi; });
  TTS_EXPECT_COMPILES     ( ct, st , { ct *  st; });
  TTS_EXPECT_COMPILES     ( ct     , { ct *  ct; });
  TTS_EXPECT_COMPILES     ( ct, wst, { ct * wst; });
  TTS_EXPECT_COMPILES     ( ct, wct, { ct * wct; });
  TTS_EXPECT_NOT_COMPILES ( ct, wi , { ct *  wi; });
  TTS_EXPECT_COMPILES     ( ct, st , { ct /  st; });
  TTS_EXPECT_COMPILES     ( ct     , { ct /  ct; });
  TTS_EXPECT_COMPILES     ( ct, wst, { ct / wst; });
  TTS_EXPECT_COMPILES     ( ct, wct, { ct / wct; });
  TTS_EXPECT_NOT_COMPILES ( ct, wi , { ct /  wi; });

  TTS_EXPECT_COMPILES     ( ct, st , {  st + ct; });
  TTS_EXPECT_COMPILES     ( ct     , {  ct + ct; });
  TTS_EXPECT_COMPILES     ( ct, wst, { wst + ct; });
  TTS_EXPECT_COMPILES     ( ct, wct, { wct + ct; });
  TTS_EXPECT_NOT_COMPILES ( ct, wi , { wi  + ct; });
  TTS_EXPECT_COMPILES     ( ct, st , {  st - ct; });
  TTS_EXPECT_COMPILES     ( ct     , {  ct - ct; });
  TTS_EXPECT_COMPILES     ( ct, wst, { wst - ct; });
  TTS_EXPECT_COMPILES     ( ct, wct, { wct - ct; });
  TTS_EXPECT_NOT_COMPILES ( ct, wi , { wi  - ct; });
  TTS_EXPECT_COMPILES     ( ct, st , {  st * ct; });
  TTS_EXPECT_COMPILES     ( ct     , {  ct * ct; });
  TTS_EXPECT_COMPILES     ( ct, wst, { wst * ct; });
  TTS_EXPECT_COMPILES     ( ct, wct, { wct * ct; });
  TTS_EXPECT_NOT_COMPILES ( ct, wi , { wi  * ct; });
  TTS_EXPECT_COMPILES     ( ct, st , {  st / ct; });
  TTS_EXPECT_COMPILES     ( ct     , {  ct / ct; });
  TTS_EXPECT_COMPILES     ( ct, wst, { wst / ct; });
  TTS_EXPECT_COMPILES     ( ct, wct, { wct / ct; });
  TTS_EXPECT_NOT_COMPILES ( ct, wi , { wi  / ct; });

  // wide complex operator support
  TTS_EXPECT_COMPILES     ( wct,  st, { wct +  st; });
  TTS_EXPECT_COMPILES     ( wct,  ct, { wct +  ct; });
  TTS_EXPECT_COMPILES     ( wct, wst, { wct + wst; });
  TTS_EXPECT_COMPILES     ( wct     , { wct + wct; });
  TTS_EXPECT_NOT_COMPILES ( wct, wi , { wct +  wi; });
  TTS_EXPECT_COMPILES     ( wct,  st, { wct -  st; });
  TTS_EXPECT_COMPILES     ( wct,  ct, { wct -  ct; });
  TTS_EXPECT_COMPILES     ( wct, wst, { wct - wst; });
  TTS_EXPECT_COMPILES     ( wct     , { wct - wct; });
  TTS_EXPECT_NOT_COMPILES ( wct, wi , { wct -  wi; });
  TTS_EXPECT_COMPILES     ( wct,  st, { wct *  st; });
  TTS_EXPECT_COMPILES     ( wct,  ct, { wct *  ct; });
  TTS_EXPECT_COMPILES     ( wct, wst, { wct * wst; });
  TTS_EXPECT_COMPILES     ( wct     , { wct * wct; });
  TTS_EXPECT_NOT_COMPILES ( wct, wi , { wct *  wi; });
  TTS_EXPECT_COMPILES     ( wct,  st, { wct /  st; });
  TTS_EXPECT_COMPILES     ( wct,  ct, { wct /  ct; });
  TTS_EXPECT_COMPILES     ( wct, wst, { wct / wst; });
  TTS_EXPECT_COMPILES     ( wct     , { wct / wct; });
  TTS_EXPECT_NOT_COMPILES ( wct, wi , { wct /  wi; });

  TTS_EXPECT_COMPILES     ( wct, st , {  st + wct; });
  TTS_EXPECT_COMPILES     ( wct, ct , {  ct + wct; });
  TTS_EXPECT_COMPILES     ( wct, wst, { wst + wct; });
  TTS_EXPECT_COMPILES     ( wct     , { wct + wct; });
  TTS_EXPECT_NOT_COMPILES ( wct, wi , { wi  + wct; });
  TTS_EXPECT_COMPILES     ( wct, st , {  st - wct; });
  TTS_EXPECT_COMPILES     ( wct, ct , {  ct - wct; });
  TTS_EXPECT_COMPILES     ( wct, wst, { wst - wct; });
  TTS_EXPECT_COMPILES     ( wct     , { wct - wct; });
  TTS_EXPECT_NOT_COMPILES ( wct, wi , { wi  - wct; });
  TTS_EXPECT_COMPILES     ( wct, st , {  st * wct; });
  TTS_EXPECT_COMPILES     ( wct, ct , {  ct * wct; });
  TTS_EXPECT_COMPILES     ( wct, wst, { wst * wct; });
  TTS_EXPECT_COMPILES     ( wct     , { wct * wct; });
  TTS_EXPECT_NOT_COMPILES ( wct, wi , { wi  * wct; });
  TTS_EXPECT_COMPILES     ( wct, st , {  st / wct; });
  TTS_EXPECT_COMPILES     ( wct, ct , {  ct / wct; });
  TTS_EXPECT_COMPILES     ( wct, wst, { wst / wct; });
  TTS_EXPECT_COMPILES     ( wct     , { wct / wct; });
  TTS_EXPECT_NOT_COMPILES ( wct, wi , { wi  / wct; });
};
