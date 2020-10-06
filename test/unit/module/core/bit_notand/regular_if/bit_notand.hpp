//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_notand.hpp>
#include <type_traits>

TTS_CASE("Check eve::bit_notand return type")
{
  using eve::detail::as_integer_t;
  using ui_t = as_integer_t<EVE_TYPE, unsigned>;
  using vi_t = as_integer_t<EVE_VALUE, unsigned>;

  TTS_EXPR_IS((eve::bit_notand[ EVE_TYPE() ](EVE_TYPE(), EVE_TYPE()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_notand[ EVE_TYPE() ](EVE_TYPE(), EVE_VALUE())) , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_notand[ EVE_TYPE() ](EVE_TYPE(), ui_t()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_notand[ EVE_TYPE() ](EVE_TYPE(), vi_t()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_notand[ EVE_TYPE() ](ui_t(), EVE_TYPE()))  , ui_t  );

  TTS_EXPR_IS((eve::bit_notand[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), EVE_TYPE()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_notand[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), EVE_VALUE())) , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_notand[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), ui_t()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_notand[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), vi_t()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_notand[ eve::logical<EVE_TYPE>() ](ui_t(), EVE_TYPE()))  , ui_t  );

  TTS_EXPR_IS((eve::bit_notand[ true  ](EVE_TYPE(), EVE_TYPE()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_notand[ true  ](EVE_TYPE(), EVE_VALUE())) , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_notand[ true  ](EVE_TYPE(), ui_t()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_notand[ true  ](EVE_TYPE(), vi_t()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_notand[ true  ](ui_t(), EVE_TYPE()))  , ui_t  );
}

TTS_CASE( "Check eve::bit_notand behavior")
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

  TTS_EQUAL(eve::bit_notand[ true  ](tu,tu),tz);
  TTS_EQUAL(eve::bit_notand[ true  ](tu,td),td);
  TTS_EQUAL(eve::bit_notand[ true  ](td,tu),tu);
  TTS_EQUAL(eve::bit_notand[ true  ](td,td),tz);

  TTS_EQUAL(eve::bit_notand[ true  ](tu,vu),tz);
  TTS_EQUAL(eve::bit_notand[ true  ](tu,vd),td);
  TTS_EQUAL(eve::bit_notand[ true  ](td,vu),tu);
  TTS_EQUAL(eve::bit_notand[ true  ](td,vd),tz);

  TTS_EQUAL(eve::bit_notand[ true  ](tu,uu),tz);
  TTS_EQUAL(eve::bit_notand[ true  ](tu,ud),td);
  TTS_EQUAL(eve::bit_notand[ true  ](td,uu),tu);
  TTS_EQUAL(eve::bit_notand[ true  ](td,ud),tz);

  TTS_EQUAL(eve::bit_notand[ true  ](tu,su),tz);
  TTS_EQUAL(eve::bit_notand[ true  ](tu,sd),td);
  TTS_EQUAL(eve::bit_notand[ true  ](td,su),tu);
  TTS_EQUAL(eve::bit_notand[ true  ](td,sd),tz);


  TTS_EQUAL(eve::bit_notand[ false  ](tu,tu),tu);
  TTS_EQUAL(eve::bit_notand[ false  ](tu,td),tu);
  TTS_EQUAL(eve::bit_notand[ false  ](td,tu),td);
  TTS_EQUAL(eve::bit_notand[ false  ](td,td),td);

  TTS_EQUAL(eve::bit_notand[ false  ](tu,vu),tu);
  TTS_EQUAL(eve::bit_notand[ false  ](tu,vd),tu);
  TTS_EQUAL(eve::bit_notand[ false  ](td,vu),td);
  TTS_EQUAL(eve::bit_notand[ false  ](td,vd),td);

  TTS_EQUAL(eve::bit_notand[ false  ](tu,uu),tu);
  TTS_EQUAL(eve::bit_notand[ false  ](tu,ud),tu);
  TTS_EQUAL(eve::bit_notand[ false  ](td,uu),td);
  TTS_EQUAL(eve::bit_notand[ false  ](td,ud),td);

  TTS_EQUAL(eve::bit_notand[ false  ](tu,su),tu);
  TTS_EQUAL(eve::bit_notand[ false  ](tu,sd),tu);
  TTS_EQUAL(eve::bit_notand[ false  ](td,su),td);
  TTS_EQUAL(eve::bit_notand[ false  ](td,sd),td);
}


