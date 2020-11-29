//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/fnma.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/eps.hpp>

TTS_CASE_TPL("Check eve::pedantic(eve::fnma) return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::pedantic(eve::fnma)(T()   , T()   , T()   ) , T);
  TTS_EXPR_IS(eve::pedantic(eve::fnma)(T()   , T()   , v_t() ) , T);
  TTS_EXPR_IS(eve::pedantic(eve::fnma)(T()   , v_t() , T()   ) , T);
  TTS_EXPR_IS(eve::pedantic(eve::fnma)(T()   , v_t() , v_t() ) , T);
  TTS_EXPR_IS(eve::pedantic(eve::fnma)(v_t() , T()   , T()   ) , T);
  TTS_EXPR_IS(eve::pedantic(eve::fnma)(v_t() , T()   , v_t() ) , T);
  TTS_EXPR_IS(eve::pedantic(eve::fnma)(v_t() , v_t() , T()   ) , T);
}

TTS_CASE_TPL("Check eve::pedantic(eve::fnma) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::pedantic(eve::fnma)(T( 0), T(0), T(0)), T( 0));
  TTS_EQUAL(eve::pedantic(eve::fnma)(T( 0), T(0), T(7)), T( 7));
  TTS_EQUAL(eve::pedantic(eve::fnma)(T( 2), T(0), T(7)), T( 7));
  TTS_EQUAL(eve::pedantic(eve::fnma)(T( 0), T(5), T(7)), T( 7));
  TTS_EQUAL(eve::pedantic(eve::fnma)(T(-2), T(5), T(7)), T(17));

  if constexpr(eve::floating_value<T>)
  {
    T e = eve::eps(eve::as<T>());
    TTS_EQUAL(eve::pedantic(eve::fnma)(eve::inc(e), eve::dec(e), T(-1)), -eve::sqr(e));
  }
}
