//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_ornot.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::bit_ornot return type", EVE_TYPE)
{
  using eve::detail::as_integer_t;
  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T, unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS((eve::bit_ornot[ T() ](T(), T()))  , T);
  TTS_EXPR_IS((eve::bit_ornot[ T() ](T(), v_t())) , T);
  TTS_EXPR_IS((eve::bit_ornot[ T() ](T(), ui_t()))  , T);
  TTS_EXPR_IS((eve::bit_ornot[ T() ](T(), vi_t()))  , T);
  TTS_EXPR_IS((eve::bit_ornot[ T() ](ui_t(), T()))  , ui_t  );

  TTS_EXPR_IS((eve::bit_ornot[ eve::logical<T>() ](T(), T()))  , T);
  TTS_EXPR_IS((eve::bit_ornot[ eve::logical<T>() ](T(), v_t())) , T);
  TTS_EXPR_IS((eve::bit_ornot[ eve::logical<T>() ](T(), ui_t()))  , T);
  TTS_EXPR_IS((eve::bit_ornot[ eve::logical<T>() ](T(), vi_t()))  , T);
  TTS_EXPR_IS((eve::bit_ornot[ eve::logical<T>() ](ui_t(), T()))  , ui_t  );

  TTS_EXPR_IS((eve::bit_ornot[ true  ](T(), T()))  , T);
  TTS_EXPR_IS((eve::bit_ornot[ true  ](T(), v_t())) , T);
  TTS_EXPR_IS((eve::bit_ornot[ true  ](T(), ui_t()))  , T);
  TTS_EXPR_IS((eve::bit_ornot[ true  ](T(), vi_t()))  , T);
  TTS_EXPR_IS((eve::bit_ornot[ true  ](ui_t(), T()))  , ui_t  );
}

TTS_CASE_TPL( "Check eve::bit_ornot behavior", EVE_TYPE)
{
  using eve::detail::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T , unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  constexpr auto u  = 0xAAAAAAAAAAAAAAAAULL;
  constexpr auto d  = 0x6666666666666666ULL;
  constexpr auto m  = 0x7777777777777777ULL;
  constexpr auto n  = 0xBBBBBBBBBBBBBBBBULL;

  ui_t uu( static_cast<vi_t>(u) );
  ui_t ud( static_cast<vi_t>(d) );
  ui_t um( static_cast<vi_t>(m) );
  ui_t un( static_cast<vi_t>(n) );
  auto td = bit_cast(ud, as<T>());
  auto tu = bit_cast(uu, as<T>());
  auto tm = bit_cast(um, as<T>());
  auto tn = bit_cast(un, as<T>());

  vi_t su( static_cast<vi_t>(u) );
  vi_t sd( static_cast<vi_t>(d) );
  auto vu = bit_cast(su, as<v_t>());
  auto vd = bit_cast(sd, as<v_t>());

  TTS_EQUAL(eve::bit_ornot[ true  ](tu,td),tn);
  TTS_EQUAL(eve::bit_ornot[ true  ](td,tu),tm);
  TTS_EQUAL(eve::bit_ornot[ true  ](tu,vd),tn);
  TTS_EQUAL(eve::bit_ornot[ true  ](td,vu),tm);
  TTS_EQUAL(eve::bit_ornot[ true  ](tu,ud),tn);
  TTS_EQUAL(eve::bit_ornot[ true  ](td,uu),tm);
  TTS_EQUAL(eve::bit_ornot[ true  ](tu,sd),tn);
  TTS_EQUAL(eve::bit_ornot[ true  ](td,su),tm);

  TTS_EQUAL(eve::bit_ornot[ false  ](tu,td),tu);
  TTS_EQUAL(eve::bit_ornot[ false  ](td,tu),td);
  TTS_EQUAL(eve::bit_ornot[ false  ](tu,vd),tu);
  TTS_EQUAL(eve::bit_ornot[ false  ](td,vu),td);
  TTS_EQUAL(eve::bit_ornot[ false  ](tu,ud),tu);
  TTS_EQUAL(eve::bit_ornot[ false  ](td,uu),td);
  TTS_EQUAL(eve::bit_ornot[ false  ](tu,sd),tu);
  TTS_EQUAL(eve::bit_ornot[ false  ](td,su),td);


}


