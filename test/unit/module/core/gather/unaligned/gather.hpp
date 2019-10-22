//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/gather.hpp>
#include <tts/tests/relation.hpp>

TTS_CASE("Check eve::gather behavior with 32 bits indexes")
{
  Value data[Cardinal];
  for(std::size_t i = 0;i<Cardinal;++i) data[i] = Value(1) + i;

  eve::wide<std::int32_t, eve::fixed<Cardinal>> maps([](auto i, auto c) { return i%3 ? i : c-i-1; });
  Type ref( [&](auto i, auto) { return data[maps[i]]; } );

  const Value* cdata = &data[0];
  TTS_EQUAL( ref, eve::gather(cdata   , maps) );
  TTS_EQUAL( ref, eve::gather(&data[0], maps) );
}

TTS_CASE("Check eve::gather behavior with 64 bits indexes")
{
  Value data[Cardinal];
  for(std::size_t i = 0;i<Cardinal;++i) data[i] = Value(1) + i;

  eve::wide<std::int64_t, eve::fixed<Cardinal>> maps([](auto i, auto c) { return i%3 ? i : c-i-1; });
  Type ref( [&](auto i, auto) { return data[maps[i]]; } );

  const Value* cdata = &data[0];
  TTS_EQUAL( ref, eve::gather(cdata   , maps) );
  TTS_EQUAL( ref, eve::gather(&data[0], maps) );
}
