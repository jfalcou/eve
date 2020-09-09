//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/allbits.hpp>
#include <eve/constant/nan.hpp>
#include <eve/wide.hpp>

#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>

using eve::fixed;

TTS_CASE("Allbits generation for scalar")
{
  using eve::as_;

  TTS_IEEE_EQUAL( eve::allbits( as_<float>()  ), eve::nan( as_<float>()  ) );
  TTS_IEEE_EQUAL( eve::allbits( as_<double>() ), eve::nan( as_<double>() ) );

  TTS_EQUAL( eve::allbits( as_<std::uint8_t>()  ), static_cast<std::uint8_t>(~0ULL)  );
  TTS_EQUAL( eve::allbits( as_<std::uint16_t>() ), static_cast<std::uint16_t>(~0ULL) );
  TTS_EQUAL( eve::allbits( as_<std::uint32_t>() ), static_cast<std::uint32_t>(~0ULL) );
  TTS_EQUAL( eve::allbits( as_<std::uint64_t>() ), static_cast<std::uint64_t>(~0ULL) );

  TTS_EQUAL( eve::allbits( as_<std::int8_t>()  ), static_cast<std::int8_t>(~0ULL)  );
  TTS_EQUAL( eve::allbits( as_<std::int16_t>() ), static_cast<std::int16_t>(~0ULL) );
  TTS_EQUAL( eve::allbits( as_<std::int32_t>() ), static_cast<std::int32_t>(~0ULL) );
  TTS_EQUAL( eve::allbits( as_<std::int64_t>() ), static_cast<std::int64_t>(~0ULL) );
}

TTS_CASE_TPL( "Allbits generation for wide"
            , fixed<1>
            , fixed<2>
            , fixed<4>
            , fixed<8>
            , fixed<16>
            , fixed<32>
            , fixed<64>
            )
{
  using eve::as_;
  using eve::wide;

  TTS_IEEE_EQUAL( (eve::allbits( as_<wide<float,T>>() ) ), eve::nan( as_<wide<float,T>>()  ) );
  TTS_IEEE_EQUAL( (eve::allbits( as_<wide<double,T>>()) ), eve::nan( as_<wide<double,T>>() ) );

  TTS_EQUAL( (eve::allbits( as_<wide<std::uint8_t,T>>() ) ), (wide<std::uint8_t,T>(~0ULL) ) );
  TTS_EQUAL( (eve::allbits( as_<wide<std::uint16_t,T>>()) ), (wide<std::uint16_t,T>(~0ULL)) );
  TTS_EQUAL( (eve::allbits( as_<wide<std::uint32_t,T>>()) ), (wide<std::uint32_t,T>(~0ULL)) );
  TTS_EQUAL( (eve::allbits( as_<wide<std::uint64_t,T>>()) ), (wide<std::uint64_t,T>(~0ULL)) );

  TTS_EQUAL( (eve::allbits( as_<wide<std::int8_t,T>>() ) ), (wide<std::int8_t,T>(~0ULL) ) );
  TTS_EQUAL( (eve::allbits( as_<wide<std::int16_t,T>>()) ), (wide<std::int16_t,T>(~0ULL)) );
  TTS_EQUAL( (eve::allbits( as_<wide<std::int32_t,T>>()) ), (wide<std::int32_t,T>(~0ULL)) );
  TTS_EQUAL( (eve::allbits( as_<wide<std::int64_t,T>>()) ), (wide<std::int64_t,T>(~0ULL)) );
}
