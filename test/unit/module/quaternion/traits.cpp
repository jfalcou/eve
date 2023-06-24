//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/quaternion.hpp>


TTS_CASE_TPL( "Check eve::like behavior for eve::quaternion"
            , eve::test::scalar::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using eve::wide;
  using eve::fixed;
  using eve::quaternion;

  TTS_CONSTEXPR_EXPECT((eve::like<T                        , quaternion<T>>));
  TTS_CONSTEXPR_EXPECT((eve::like<int                      , quaternion<T>>));
  TTS_CONSTEXPR_EXPECT((eve::like<quaternion<T>            , quaternion<T>>));
  TTS_CONSTEXPR_EXPECT((eve::like<wide<T>                  , quaternion<T>>));
  TTS_CONSTEXPR_EXPECT((eve::like<wide<T,fixed<1>>         , quaternion<T>>));
  TTS_CONSTEXPR_EXPECT((eve::like<wide<quaternion<T>>      , quaternion<T>>));
  TTS_CONSTEXPR_EXPECT((eve::like<wide<quaternion<T>,fixed<1>>, quaternion<T>>));
  TTS_CONSTEXPR_EXPECT_NOT((eve::like<wide<int>            , quaternion<T>>));
};

TTS_CASE_TPL( "Check quaternion basic operator overload properties"
            , eve::test::scalar::ieee_reals
            )
<typename T>(tts::type<T>)
{
  T                                st;
  eve::quaternion<T>               ct;
  eve::wide<T>                    wst;
  eve::wide<eve::as_integer_t<T>>  wi;
  eve::wide<eve::quaternion<T>>   wct;

  // scalar quaternion operator supports
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

  // wide quaternion operator support
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
