//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/bitwise_select.hpp>
#include <eve/constant/constant.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tts.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE( "Check bitwise_select return type" )
{
  TTS_EXPR_IS(eve::bitwise_select(std::uint32_t(), float(), float() ) , float );
  TTS_EXPR_IS(eve::bitwise_select(std::uint64_t(), double(), double() ) , double );

  TTS_EXPR_IS(eve::bitwise_select(std::uint8_t() , std::int8_t() , std::int8_t()  ) , std::int8_t  );
  TTS_EXPR_IS(eve::bitwise_select(std::uint16_t(), std::int16_t(), std::int16_t() ) , std::int16_t );
  TTS_EXPR_IS(eve::bitwise_select(std::uint32_t(), std::int32_t(), std::int32_t() ) , std::int32_t );
  TTS_EXPR_IS(eve::bitwise_select(std::uint64_t(), std::int64_t(), std::int64_t() ) , std::int64_t );

  TTS_EXPR_IS(eve::bitwise_select(std::uint8_t() , std::uint8_t() , std::uint8_t()  ) , std::uint8_t  );
  TTS_EXPR_IS(eve::bitwise_select(std::uint16_t(), std::uint16_t(), std::uint16_t() ) , std::uint16_t );
  TTS_EXPR_IS(eve::bitwise_select(std::uint32_t(), std::uint32_t(), std::uint32_t() ) , std::uint32_t );
  TTS_EXPR_IS(eve::bitwise_select(std::uint64_t(), std::uint64_t(), std::uint64_t() ) , std::uint64_t );
}

TTS_CASE( "Check bitwise_select behavior" )
{
  TTS_EQUAL ( eve::bitwise_select( std::uint8_t(0b10101010)
                                 , std::uint8_t(0b10101010)
                                 , std::uint8_t(0b01010101)
                                 )
            , std::uint8_t(0b11111111)
            );

  TTS_EQUAL ( eve::bitwise_select( std::uint16_t(0b1010101010101010)
                                 , std::uint16_t(0b1010101010101010)
                                 , std::uint16_t(0b0101010101010101)
                                 )
            , std::uint16_t(0b1111111111111111)
            );

  TTS_EQUAL ( eve::bitwise_select( std::uint32_t(0xAAAAAAAA)
                                 , std::uint32_t(0xAAAAAAAA)
                                 , std::uint32_t(0x55555555)
                                 )
            , std::uint32_t(0xFFFFFFFF)
            );

  TTS_EQUAL ( eve::bitwise_select( std::uint64_t(0xAAAAAAAAAAAAAAAAULL)
                                 , std::uint64_t(0xAAAAAAAAAAAAAAAAULL)
                                 , std::uint64_t(0x5555555555555555ULL)
                                 )
            , std::uint64_t(0xFFFFFFFFFFFFFFFFULL)
            );

  TTS_IEEE_EQUAL ( eve::bitwise_select( std::uint32_t(0xAAAAAAAA)
                                      , (eve::Constant<float,0xAAAAAAAA>())
                                      , (eve::Constant<float,0x55555555>())
                                      )
                  , eve::Nan<float>()
                  );
  TTS_IEEE_EQUAL ( eve::bitwise_select( std::uint64_t(0xAAAAAAAAAAAAAAAAULL)
                                      , (eve::Constant<double,0xAAAAAAAAAAAAAAAAULL>())
                                      , (eve::Constant<double,0x5555555555555555ULL>())
                                      )
                  , eve::Nan<double>()
                  );
}
