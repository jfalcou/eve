//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_and.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bit_and return type")
{
  using eve::detail::as_integer_t;
  using ui_t = as_integer_t<EVE_TYPE, unsigned>;
  using vi_t = as_integer_t<EVE_VALUE, unsigned>;

  TTS_EXPR_IS((eve::bit_and[ EVE_TYPE() ](EVE_TYPE(), EVE_TYPE()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_and[ EVE_TYPE() ](EVE_TYPE(), EVE_VALUE())) , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_and[ EVE_TYPE() ](EVE_TYPE(), ui_t()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_and[ EVE_TYPE() ](EVE_TYPE(), vi_t()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_and[ EVE_TYPE() ](ui_t(), EVE_TYPE()))  , ui_t  );
              
  TTS_EXPR_IS((eve::bit_and[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), EVE_TYPE()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_and[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), EVE_VALUE())) , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_and[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), ui_t()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_and[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), vi_t()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_and[ eve::logical<EVE_TYPE>() ](ui_t(), EVE_TYPE()))  , ui_t  );
              
  TTS_EXPR_IS((eve::bit_and[ true  ](EVE_TYPE(), EVE_TYPE()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_and[ true  ](EVE_TYPE(), EVE_VALUE())) , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_and[ true  ](EVE_TYPE(), ui_t()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_and[ true  ](EVE_TYPE(), vi_t()))  , (EVE_TYPE));
  TTS_EXPR_IS((eve::bit_and[ true  ](ui_t(), EVE_TYPE()))  , ui_t  );
}

TTS_CASE( "Check eve::bit_and behavior")
{
  using eve::detail::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using ui_t = as_integer_t<EVE_TYPE , unsigned>;
  using vi_t = as_integer_t<EVE_VALUE, unsigned>;

  constexpr auto u  = 0x5555555555555555ULL;
  constexpr auto d  = 0xAAAAAAAAAAAAAAAAULL;

  auto tz = EVE_TYPE(0);

  ui_t uu( static_cast<vi_t>(u) );
  ui_t ud( static_cast<vi_t>(d) );
  auto td = bit_cast(ud, as<EVE_TYPE>());
  auto tu = bit_cast(uu, as<EVE_TYPE>());

  vi_t su( static_cast<vi_t>(u) );
  vi_t sd( static_cast<vi_t>(d) );
  auto vu = bit_cast(su, as<EVE_VALUE>());
  auto vd = bit_cast(sd, as<EVE_VALUE>());

  TTS_EQUAL(eve::bit_and[ true  ](tu,tu),tu);
  TTS_EQUAL(eve::bit_and[ true  ](tu,td),tz);
  TTS_EQUAL(eve::bit_and[ true  ](td,tu),tz);
  TTS_EQUAL(eve::bit_and[ true  ](td,td),td);

  TTS_EQUAL(eve::bit_and[ true  ](tu,vu),tu);
  TTS_EQUAL(eve::bit_and[ true  ](tu,vd),tz);
  TTS_EQUAL(eve::bit_and[ true  ](td,vu),tz);
  TTS_EQUAL(eve::bit_and[ true  ](td,vd),td);

  TTS_EQUAL(eve::bit_and[ true  ](tu,uu),tu);
  TTS_EQUAL(eve::bit_and[ true  ](tu,ud),tz);
  TTS_EQUAL(eve::bit_and[ true  ](td,uu),tz);
  TTS_EQUAL(eve::bit_and[ true  ](td,ud),td);

  TTS_EQUAL(eve::bit_and[ true  ](tu,su),tu);
  TTS_EQUAL(eve::bit_and[ true  ](tu,sd),tz);
  TTS_EQUAL(eve::bit_and[ true  ](td,su),tz);
  TTS_EQUAL(eve::bit_and[ true  ](td,sd),td);

 
  TTS_EQUAL(eve::bit_and[ false  ](tu,tu),tu);
  TTS_EQUAL(eve::bit_and[ false  ](tu,td),tu);
  TTS_EQUAL(eve::bit_and[ false  ](td,tu),td);
  TTS_EQUAL(eve::bit_and[ false  ](td,td),td);

  TTS_EQUAL(eve::bit_and[ false  ](tu,vu),tu);
  TTS_EQUAL(eve::bit_and[ false  ](tu,vd),tu);
  TTS_EQUAL(eve::bit_and[ false  ](td,vu),td);
  TTS_EQUAL(eve::bit_and[ false  ](td,vd),td);

  TTS_EQUAL(eve::bit_and[ false  ](tu,uu),tu);
  TTS_EQUAL(eve::bit_and[ false  ](tu,ud),tu);
  TTS_EQUAL(eve::bit_and[ false  ](td,uu),td);
  TTS_EQUAL(eve::bit_and[ false  ](td,ud),td);

  TTS_EQUAL(eve::bit_and[ false  ](tu,su),tu);
  TTS_EQUAL(eve::bit_and[ false  ](tu,sd),tu);
  TTS_EQUAL(eve::bit_and[ false  ](td,su),td);
  TTS_EQUAL(eve::bit_and[ false  ](td,sd),td); 
}


