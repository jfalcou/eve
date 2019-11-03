//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <tts/tests/types.hpp>
#include <tuple>
#include <vector>

TTS_CASE_TPL("Check as_wide on scalar", TTS_SIGNED_NUMERIC_TYPES, TTS_UNSIGNED_NUMERIC_TYPES  )
{
  using eve::as_wide_t;
  using eve::logical;
  using eve::fixed;
  using eve::wide;

  TTS_TYPE_IS((as_wide_t<T, fixed<4>>)          , (wide<T,fixed<4>>          ) );
  TTS_TYPE_IS((as_wide_t<logical<T>, fixed<4>>) , (logical<wide<T,fixed<4>>> ) );
}

TTS_CASE_TPL("Check as_wide on wide", TTS_SIGNED_NUMERIC_TYPES, TTS_UNSIGNED_NUMERIC_TYPES)
{
  using eve::as_wide_t;
  using eve::logical;
  using eve::fixed;
  using eve::wide;

  TTS_TYPE_IS((as_wide_t<wide<T,fixed<8>>, fixed<4>>)          , (wide<T,fixed<4>>          ) );
  TTS_TYPE_IS((as_wide_t<logical<wide<T,fixed<8>>>, fixed<4>>) , (logical<wide<T,fixed<4>>> ) );
}

TTS_CASE("Check as_wide on third party types")
{
  using eve::as_wide_t;
  using eve::logical;
  using eve::fixed;
  using eve::wide;

  TTS_TYPE_IS(  (as_wide_t<std::vector<std::uint8_t>, fixed<4>>)
              , (std::vector<wide<std::uint8_t,fixed<4>>>)
              );

  TTS_TYPE_IS(  (as_wide_t<std::pair<int,float>, fixed<4>>)
              , (std::pair<wide<int,fixed<4>>,wide<float,fixed<4>>>)
              );

  TTS_TYPE_IS(  (as_wide_t<std::tuple<int,logical<double>, float>, fixed<4>>)
              , (std::tuple<wide<int,fixed<4>>,logical<wide<double,fixed<4>>>, wide<float,fixed<4>>>)
              );


}
