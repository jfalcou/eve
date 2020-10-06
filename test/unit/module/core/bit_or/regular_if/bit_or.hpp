//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_or.hpp>
#include <type_traits>

TTS_CASE("Check eve::bit_or return type")
{
  using eve::detail::as_integer_t;
  using ui_t = as_integer_t<EVE_TYPE, unsigned>;
  using vi_t = as_integer_t<EVE_VALUE, unsigned>;

  TTS_EXPR_IS((eve::bit_or[ EVE_TYPE() ](EVE_TYPE(), EVE_TYPE()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_or[ EVE_TYPE() ](EVE_TYPE(), EVE_VALUE())) , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_or[ EVE_TYPE() ](EVE_TYPE(), ui_t()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_or[ EVE_TYPE() ](EVE_TYPE(), vi_t()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_or[ EVE_TYPE() ](ui_t(), EVE_TYPE()))  , ui_t  );

  TTS_EXPR_IS((eve::bit_or[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), EVE_TYPE()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_or[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), EVE_VALUE())) , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_or[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), ui_t()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_or[ eve::logical<EVE_TYPE>() ](EVE_TYPE(), vi_t()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_or[ eve::logical<EVE_TYPE>() ](ui_t(), EVE_TYPE()))  , ui_t  );

  TTS_EXPR_IS((eve::bit_or[ true  ](EVE_TYPE(), EVE_TYPE()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_or[ true  ](EVE_TYPE(), EVE_VALUE())) , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_or[ true  ](EVE_TYPE(), ui_t()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_or[ true  ](EVE_TYPE(), vi_t()))  , EVE_TYPE);
  TTS_EXPR_IS((eve::bit_or[ true  ](ui_t(), EVE_TYPE()))  , ui_t  );
}

TTS_CASE( "Check eve::bit_or behavior")
{
  using eve::detail::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using ui_t = as_integer_t<EVE_TYPE , unsigned>;
  using vi_t = as_integer_t<EVE_VALUE, unsigned>;

  constexpr auto u  = 0x5555555555555555ULL;

  auto tz = EVE_TYPE(0);
  auto vz = EVE_VALUE(0);

  ui_t uu( static_cast<vi_t>(u) );
  ui_t uz( static_cast<vi_t>(0) );
  auto tu = bit_cast(uu, as<EVE_TYPE>());

  vi_t su( static_cast<vi_t>(u) );
  auto vu = bit_cast(su, as<EVE_VALUE>());

  TTS_EQUAL(eve::bit_or[ true  ](tu,tu),tu);
  TTS_EQUAL(eve::bit_or[ true  ](tu,tz),tu);
  TTS_EQUAL(eve::bit_or[ true  ](tz,tu),tu);
  TTS_EQUAL(eve::bit_or[ true  ](tz,tz),tz);

  TTS_EQUAL(eve::bit_or[ true  ](tu,vu),tu);
  TTS_EQUAL(eve::bit_or[ true  ](tu,vz),tu);
  TTS_EQUAL(eve::bit_or[ true  ](tz,vu),tu);
  TTS_EQUAL(eve::bit_or[ true  ](tz,vz),tz);

  TTS_EQUAL(eve::bit_or[ true  ](tu,uu),tu);
  TTS_EQUAL(eve::bit_or[ true  ](tu,uz),tu);
  TTS_EQUAL(eve::bit_or[ true  ](tz,uu),tu);
  TTS_EQUAL(eve::bit_or[ true  ](tz,uz),tz);

  TTS_EQUAL(eve::bit_or[ false  ](tu,vu),tu);
  TTS_EQUAL(eve::bit_or[ false  ](tu,vz),tu);
  TTS_EQUAL(eve::bit_or[ false  ](tz,vu),tz);
  TTS_EQUAL(eve::bit_or[ false  ](tz,vz),tz);

  TTS_EQUAL(eve::bit_or[ false  ](tu,tu),tu);
  TTS_EQUAL(eve::bit_or[ false  ](tu,tz),tu);
  TTS_EQUAL(eve::bit_or[ false  ](tz,tu),tz);
  TTS_EQUAL(eve::bit_or[ false  ](tz,tz),tz);

  TTS_EQUAL(eve::bit_or[ false  ](tu,vu),tu);
  TTS_EQUAL(eve::bit_or[ false  ](tu,vz),tu);
  TTS_EQUAL(eve::bit_or[ false  ](tz,vu),tz);
  TTS_EQUAL(eve::bit_or[ false  ](tz,vz),tz);

  TTS_EQUAL(eve::bit_or[ false  ](tu,uu),tu);
  TTS_EQUAL(eve::bit_or[ false  ](tu,uz),tu);
  TTS_EQUAL(eve::bit_or[ false  ](tz,uu),tz);
  TTS_EQUAL(eve::bit_or[ false  ](tz,uz),tz);

  TTS_EQUAL(eve::bit_or[ false  ](tu,vu),tu);
  TTS_EQUAL(eve::bit_or[ false  ](tu,vz),tu);
  TTS_EQUAL(eve::bit_or[ false  ](tz,vu),tz);
  TTS_EQUAL(eve::bit_or[ false  ](tz,vz),tz);
}


