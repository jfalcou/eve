//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/gather.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <tts/tests/relation.hpp>

TTS_CASE("Check eve::gather behavior with 32 bits indexes")
{
  constexpr auto alg = EVE_TYPE::static_alignment;
  alignas(alg) EVE_VALUE data[EVE_CARDINAL];

  for(std::size_t i = 0;i<EVE_CARDINAL;++i) data[i] = EVE_VALUE(1) + i;

  eve::wide<std::int32_t, eve::fixed<EVE_CARDINAL>> maps([](auto i, auto c) { return i%3 ? i : c-i-1; });
  EVE_TYPE ref( [&](auto i, auto) { return data[maps[i]]; } );

  const EVE_VALUE* cdata = &data[0];
  TTS_EQUAL( ref, eve::gather(eve::as_aligned<alg>(cdata    ), maps) );
  TTS_EQUAL( ref, eve::gather(eve::as_aligned<alg>(&data[0]), maps) );
}

TTS_CASE("Check eve::gather behavior with 64 bits indexes")
{
  constexpr auto alg = EVE_TYPE::static_alignment;
  alignas(alg) EVE_VALUE data[EVE_CARDINAL];

  for(std::size_t i = 0;i<EVE_CARDINAL;++i) data[i] = EVE_VALUE(1) + i;

  eve::wide<std::int64_t, eve::fixed<EVE_CARDINAL>> maps([](auto i, auto c) { return i%3 ? i : c-i-1; });
  EVE_TYPE ref( [&](auto i, auto) { return data[maps[i]]; } );

  const EVE_VALUE* cdata = &data[0];
  TTS_EQUAL( ref, eve::gather(eve::as_aligned<alg>(cdata    ), maps) );
  TTS_EQUAL( ref, eve::gather(eve::as_aligned<alg>(&data[0]), maps) );
}
