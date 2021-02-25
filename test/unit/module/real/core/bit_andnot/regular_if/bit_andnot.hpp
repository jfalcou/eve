//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_and.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::bit_andnot return type", EVE_TYPE)
{
  using eve::as_integer_t;
  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T, unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS((eve::bit_andnot[ T() ](T(), T()))  , T);
  TTS_EXPR_IS((eve::bit_andnot[ T() ](T(), v_t())) , T);
  TTS_EXPR_IS((eve::bit_andnot[ T() ](T(), ui_t()))  , T);
  TTS_EXPR_IS((eve::bit_andnot[ T() ](T(), vi_t()))  , T);
  TTS_EXPR_IS((eve::bit_andnot[ T() ](ui_t(), T()))  , ui_t  );

  TTS_EXPR_IS((eve::bit_andnot[ eve::logical<T>() ](T(), T()))  , T);
  TTS_EXPR_IS((eve::bit_andnot[ eve::logical<T>() ](T(), v_t())) , T);
  TTS_EXPR_IS((eve::bit_andnot[ eve::logical<T>() ](T(), ui_t()))  , T);
  TTS_EXPR_IS((eve::bit_andnot[ eve::logical<T>() ](T(), vi_t()))  , T);
  TTS_EXPR_IS((eve::bit_andnot[ eve::logical<T>() ](ui_t(), T()))  , ui_t  );

  TTS_EXPR_IS((eve::bit_andnot[ true  ](T(), T()))  , T);
  TTS_EXPR_IS((eve::bit_andnot[ true  ](T(), v_t())) , T);
  TTS_EXPR_IS((eve::bit_andnot[ true  ](T(), ui_t()))  , T);
  TTS_EXPR_IS((eve::bit_andnot[ true  ](T(), vi_t()))  , T);
  TTS_EXPR_IS((eve::bit_andnot[ true  ](ui_t(), T()))  , ui_t  );
}

TTS_CASE_TPL( "Check eve::bit_andnot behavior", EVE_TYPE)
{
  using eve::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using v_t =  eve::element_type_t<T>;
  using ui_t = as_integer_t<T , unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  constexpr auto u  = 0x5555555555555555ULL;
  constexpr auto d  = 0xAAAAAAAAAAAAAAAAULL;

  auto tz = T(0);

  ui_t uu( static_cast<vi_t>(u) );
  ui_t ud( static_cast<vi_t>(d) );
  auto td = bit_cast(ud, as<T>());
  auto tu = bit_cast(uu, as<T>());

  vi_t su( static_cast<vi_t>(u) );
  vi_t sd( static_cast<vi_t>(d) );
  auto vu = bit_cast(su, as<v_t>());
  auto vd = bit_cast(sd, as<v_t>());

  TTS_EQUAL(eve::bit_andnot[ true  ](tu,tu),tz);
  TTS_EQUAL(eve::bit_andnot[ true  ](tu,td),tu);
  TTS_EQUAL(eve::bit_andnot[ true  ](td,tu),td);
  TTS_EQUAL(eve::bit_andnot[ true  ](td,td),tz);

  TTS_EQUAL(eve::bit_andnot[ true  ](tu,vu),tz);
  TTS_EQUAL(eve::bit_andnot[ true  ](tu,vd),tu);
  TTS_EQUAL(eve::bit_andnot[ true  ](td,vu),td);
  TTS_EQUAL(eve::bit_andnot[ true  ](td,vd),tz);

  TTS_EQUAL(eve::bit_andnot[ true  ](tu,uu),tz);
  TTS_EQUAL(eve::bit_andnot[ true  ](tu,ud),tu);
  TTS_EQUAL(eve::bit_andnot[ true  ](td,uu),td);
  TTS_EQUAL(eve::bit_andnot[ true  ](td,ud),tz);

  TTS_EQUAL(eve::bit_andnot[ true  ](tu,su),tz);
  TTS_EQUAL(eve::bit_andnot[ true  ](tu,sd),tu);
  TTS_EQUAL(eve::bit_andnot[ true  ](td,su),td);
  TTS_EQUAL(eve::bit_andnot[ true  ](td,sd),tz);


  TTS_EQUAL(eve::bit_andnot[ false  ](tu,tu),tu);
  TTS_EQUAL(eve::bit_andnot[ false  ](tu,td),tu);
  TTS_EQUAL(eve::bit_andnot[ false  ](td,tu),td);
  TTS_EQUAL(eve::bit_andnot[ false  ](td,td),td);

  TTS_EQUAL(eve::bit_andnot[ false  ](tu,vu),tu);
  TTS_EQUAL(eve::bit_andnot[ false  ](tu,vd),tu);
  TTS_EQUAL(eve::bit_andnot[ false  ](td,vu),td);
  TTS_EQUAL(eve::bit_andnot[ false  ](td,vd),td);

  TTS_EQUAL(eve::bit_andnot[ false  ](tu,uu),tu);
  TTS_EQUAL(eve::bit_andnot[ false  ](tu,ud),tu);
  TTS_EQUAL(eve::bit_andnot[ false  ](td,uu),td);
  TTS_EQUAL(eve::bit_andnot[ false  ](td,ud),td);

  TTS_EQUAL(eve::bit_andnot[ false  ](tu,su),tu);
  TTS_EQUAL(eve::bit_andnot[ false  ](tu,sd),tu);
  TTS_EQUAL(eve::bit_andnot[ false  ](td,su),td);
  TTS_EQUAL(eve::bit_andnot[ false  ](td,sd),td);
}
