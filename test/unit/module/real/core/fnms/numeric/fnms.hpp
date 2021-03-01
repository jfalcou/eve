//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/numeric/fnms.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE_TPL("Check eve::numeric(eve::fnms) return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::numeric(eve::fnms)(T()   , T()   , T()   ) , T);
  TTS_EXPR_IS(eve::numeric(eve::fnms)(T()   , T()   , v_t() ) , T);
  TTS_EXPR_IS(eve::numeric(eve::fnms)(T()   , v_t() , T()   ) , T);
  TTS_EXPR_IS(eve::numeric(eve::fnms)(T()   , v_t() , v_t() ) , T);
  TTS_EXPR_IS(eve::numeric(eve::fnms)(v_t() , T()   , T()   ) , T);
  TTS_EXPR_IS(eve::numeric(eve::fnms)(v_t() , T()   , v_t() ) , T);
  TTS_EXPR_IS(eve::numeric(eve::fnms)(v_t() , v_t() , T()   ) , T);
}

TTS_CASE_TPL("Check eve::numeric(eve::fnms) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::numeric(eve::fnms)(T(0), T(0), T(0)), T(  0));
  TTS_EQUAL(eve::numeric(eve::fnms)(T(0), T(0), T(7)), T(- 7));
  TTS_EQUAL(eve::numeric(eve::fnms)(T(2), T(0), T(7)), T(- 7));
  TTS_EQUAL(eve::numeric(eve::fnms)(T(0), T(5), T(7)), T(- 7));
  TTS_EQUAL(eve::numeric(eve::fnms)(T(2), T(5), T(7)), T(-17));

  if constexpr(eve::floating_value<T>)
  {
    T e = eve::eps(eve::as<T>());
    TTS_EQUAL(eve::numeric(eve::fnms)(eve::inc(e), eve::oneminus(e), T(-1)), eve::sqr(e));
    TTS_EQUAL(eve::numeric(eve::fnms)(eve::valmax(eve::as<T>()), T(2), eve::valmin(eve::as<T>())), -eve::valmax(eve::as<T>()));
  }
}
