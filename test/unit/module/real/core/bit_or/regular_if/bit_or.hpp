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

TTS_CASE_TPL("Check eve::bit_or return type", EVE_TYPE)
{
  using eve::as_integer_t;
  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T, unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS((eve::bit_or[ T() ](T(), T()))  , T);
  TTS_EXPR_IS((eve::bit_or[ T() ](T(), v_t())) , T);
  TTS_EXPR_IS((eve::bit_or[ T() ](T(), ui_t()))  , T);
  TTS_EXPR_IS((eve::bit_or[ T() ](T(), vi_t()))  , T);
  TTS_EXPR_IS((eve::bit_or[ T() ](ui_t(), T()))  , ui_t  );

  TTS_EXPR_IS((eve::bit_or[ eve::logical<T>() ](T(), T()))  , T);
  TTS_EXPR_IS((eve::bit_or[ eve::logical<T>() ](T(), v_t())) , T);
  TTS_EXPR_IS((eve::bit_or[ eve::logical<T>() ](T(), ui_t()))  , T);
  TTS_EXPR_IS((eve::bit_or[ eve::logical<T>() ](T(), vi_t()))  , T);
  TTS_EXPR_IS((eve::bit_or[ eve::logical<T>() ](ui_t(), T()))  , ui_t  );

  TTS_EXPR_IS((eve::bit_or[ true  ](T(), T()))  , T);
  TTS_EXPR_IS((eve::bit_or[ true  ](T(), v_t())) , T);
  TTS_EXPR_IS((eve::bit_or[ true  ](T(), ui_t()))  , T);
  TTS_EXPR_IS((eve::bit_or[ true  ](T(), vi_t()))  , T);
  TTS_EXPR_IS((eve::bit_or[ true  ](ui_t(), T()))  , ui_t  );
}

TTS_CASE_TPL( "Check eve::bit_or behavior", EVE_TYPE)
{
  using eve::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using v_t =  eve::element_type_t<T>;
  using ui_t = as_integer_t<T , unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  constexpr auto u  = 0x5555555555555555ULL;

  auto tz = T(0);
  auto vz = v_t(0);

  ui_t uu( static_cast<vi_t>(u) );
  ui_t uz( static_cast<vi_t>(0) );
  auto tu = bit_cast(uu, as<T>());

  vi_t su( static_cast<vi_t>(u) );
  auto vu = bit_cast(su, as<v_t>());

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
