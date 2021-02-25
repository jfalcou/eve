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
#include <tuple>
#include <array>

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

  TTS_TYPE_IS(  (as_wide_t<std::array<double,7>, fixed<2>>)
              , (std::array<wide<double,fixed<2>>,7>)
              );

  TTS_TYPE_IS(  (as_wide_t<std::pair<double,std::uint8_t>,fixed<4>>)
              , (std::pair<wide<double,fixed<4>>,eve::wide<std::uint8_t,fixed<4>>>)
              );

  TTS_TYPE_IS(  (as_wide_t<std::tuple<int,logical<double>, float>, fixed<8>>)
              , (std::tuple<wide<int,fixed<8>>,logical<wide<double,fixed<8>>>, wide<float,fixed<8>>>)
              );
}
