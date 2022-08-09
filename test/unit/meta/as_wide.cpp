//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE_TPL("Check as_wide on scalar", tts::arithmetic_types)
<typename T>(::tts::type<T>)
{
  using eve::as_wide_t;
  using eve::logical;
  using eve::fixed;
  using eve::wide;

  TTS_TYPE_IS ( (as_wide_t<T, fixed<4>>)          , (wide<T,fixed<4>>          ) );
  TTS_TYPE_IS ( (as_wide_t<logical<T>, fixed<4>>) , (logical<wide<T,fixed<4>>> ) );
  TTS_TYPE_IS ( (as_wide_t<kumi::tuple<T,int,float>, fixed<4>>)
              , (wide<kumi::tuple<T,int,float>,fixed<4>> )
              );
};

TTS_CASE_TPL("Check as_wide on wide", tts::arithmetic_types)
<typename T>(::tts::type<T>)
{
  using eve::as_wide_t;
  using eve::logical;
  using eve::fixed;
  using eve::wide;

  TTS_TYPE_IS((as_wide_t<wide<T,fixed<8>>, fixed<4>>)          , (wide<T,fixed<4>>          ) );
  TTS_TYPE_IS((as_wide_t<logical<wide<T,fixed<8>>>, fixed<4>>) , (logical<wide<T,fixed<4>>> ) );
  TTS_TYPE_IS ( (as_wide_t<wide<kumi::tuple<T,int,float>>, fixed<4>>)
              , (wide<kumi::tuple<T,int,float>,fixed<4>> )
              );
};
