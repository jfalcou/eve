//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_notand.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::bit_notand return type", EVE_TYPE)
{
  using eve::as_integer_t;
  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T, unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS((eve::bit_notand[ T() ](T(), T()))  , T);
  TTS_EXPR_IS((eve::bit_notand[ T() ](T(), v_t())) , T);
  TTS_EXPR_IS((eve::bit_notand[ T() ](T(), ui_t()))  , T);
  TTS_EXPR_IS((eve::bit_notand[ T() ](T(), vi_t()))  , T);
  TTS_EXPR_IS((eve::bit_notand[ T() ](ui_t(), T()))  , ui_t  );

  TTS_EXPR_IS((eve::bit_notand[ eve::logical<T>() ](T(), T()))  , T);
  TTS_EXPR_IS((eve::bit_notand[ eve::logical<T>() ](T(), v_t())) , T);
  TTS_EXPR_IS((eve::bit_notand[ eve::logical<T>() ](T(), ui_t()))  , T);
  TTS_EXPR_IS((eve::bit_notand[ eve::logical<T>() ](T(), vi_t()))  , T);
  TTS_EXPR_IS((eve::bit_notand[ eve::logical<T>() ](ui_t(), T()))  , ui_t  );

  TTS_EXPR_IS((eve::bit_notand[ true  ](T(), T()))  , T);
  TTS_EXPR_IS((eve::bit_notand[ true  ](T(), v_t())) , T);
  TTS_EXPR_IS((eve::bit_notand[ true  ](T(), ui_t()))  , T);
  TTS_EXPR_IS((eve::bit_notand[ true  ](T(), vi_t()))  , T);
  TTS_EXPR_IS((eve::bit_notand[ true  ](ui_t(), T()))  , ui_t  );
}

TTS_CASE_TPL( "Check eve::bit_notand behavior", EVE_TYPE)
{
  using eve::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using v_t = eve::element_type_t<T>;
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
