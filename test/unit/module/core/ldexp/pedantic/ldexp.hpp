//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/ldexp.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/valmax.hpp>


TTS_CASE_TPL("Check eve::pedantic(eve::ldexp) return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::detail::as_integer_t<T, signed>;
  using u_t = eve::detail::as_integer_t<T, unsigned>;
  using si_t = eve::detail::as_integer_t<v_t, signed>;
  using su_t = eve::detail::as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(eve::pedantic(eve::ldexp)(T(), i_t())  , T);
  TTS_EXPR_IS(eve::pedantic(eve::ldexp)(T(), u_t())  , T);
  TTS_EXPR_IS(eve::pedantic(eve::ldexp)(T(), si_t()) , T);
  TTS_EXPR_IS(eve::pedantic(eve::ldexp)(T(), su_t()) , T);
}

TTS_CASE_TPL("Check eve::pedantic(eve::ldexp) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::detail::as_integer_t<T, signed>;
  using si_t = eve::detail::as_integer_t<v_t, signed>;

  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic(eve::ldexp)(T(-0.0), i_t(0)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic(eve::ldexp)(T( 0.0), i_t(0)))));

  TTS_EQUAL(eve::pedantic(eve::ldexp)(T(0), i_t(2)), T(0));
  TTS_EQUAL(eve::pedantic(eve::ldexp)(T(1), i_t(2)), T(4));
  TTS_EQUAL(eve::pedantic(eve::ldexp)(T(0), si_t(2)),T(0));
  TTS_EQUAL(eve::pedantic(eve::ldexp)(T(1), si_t(2)),T(4));
  TTS_EQUAL(eve::pedantic(eve::ldexp)(T( 0 ), i_t(0)), T(0));
  TTS_EQUAL(eve::pedantic(eve::ldexp)(T(-0.), i_t(0)), T(0));
  TTS_EQUAL(eve::pedantic(eve::ldexp)(T( 1 ), i_t(2)), T(4));
  TTS_EQUAL(eve::pedantic(eve::ldexp)(T(-2 ), i_t(2)), T(-8));
  TTS_EQUAL(eve::pedantic(eve::ldexp)(T(-1 ), si_t(2)),T(-4));
  TTS_EQUAL(eve::pedantic(eve::ldexp)(T(-2 ), si_t(2)),T(-8));

  TTS_EQUAL(eve::pedantic(eve::ldexp)(eve::valmax(eve::as<T>())/4, si_t(2))     , eve::valmax(eve::as<T>()));
  TTS_EQUAL(eve::pedantic(eve::ldexp)(eve::valmax(eve::as<T>())/4, i_t(2))      , eve::valmax(eve::as<T>()));
  TTS_EQUAL(eve::pedantic(eve::ldexp)(eve::mindenormal(eve::as<T>()), i_t(2))  , eve::mindenormal(eve::as<T>())*4);
  TTS_EQUAL(eve::pedantic(eve::ldexp)(eve::mindenormal(eve::as<T>()), si_t(2)) , eve::mindenormal(eve::as<T>())*4);
}
