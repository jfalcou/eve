//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE_TPL( "Check as_logical on scalar"
            , TTS_SIGNED_NUMERIC_TYPES, TTS_UNSIGNED_NUMERIC_TYPES
            )
<typename T>(::tts::type<T>)
{
  using eve::as_logical_t;
  using eve::logical;
  using eve::fixed;

  TTS_TYPE_IS(as_logical_t<T>                         , logical<T>);
  TTS_TYPE_IS(as_logical_t<logical<T>>                , logical<T>);
  TTS_TYPE_IS((as_logical_t<kumi::tuple<T,int,float>>), logical<T>);
};

TTS_CASE_TPL("Check as_wide on wide"
            , TTS_SIGNED_NUMERIC_TYPES, TTS_UNSIGNED_NUMERIC_TYPES
            )
<typename T>(::tts::type<T>)
{
  using eve::as_logical_t;
  using eve::logical;
  using eve::wide;
  using eve::fixed;

  TTS_TYPE_IS(as_logical_t<wide<T>>                                   , logical<wide<T>>);
  TTS_TYPE_IS(as_logical_t<logical<wide<T>>>                          , logical<wide<T>>);
  TTS_TYPE_IS((as_logical_t<wide<kumi::tuple<T,int,float>,fixed<4>>>) , (logical<wide<T,fixed<4>>>));
};
