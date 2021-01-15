//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/add.hpp>
#include <eve/function/saturated/add.hpp>


TTS_CASE_TPL("Check eve::add return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::add(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::add(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::add(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::add(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::add(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::add(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::add(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::add(v_t(), v_t(), v_t()), v_t);
  if constexpr(eve::simd_value<T>)
  {
    TTS_EXPR_IS(eve::add(int(), int(), T()  ), T);
    TTS_EXPR_IS(eve::add(T(), int(), float() ), T);
  }

}

TTS_CASE_TPL("Check eve::add behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::add(T{0},   T{0}, T{0})  , T(0));
  TTS_EQUAL(eve::add(T{1},   T{1}, v_t{1}), T(3));
  TTS_EQUAL(eve::add(T{2}, v_t{2}, T{4})  , T(8));
  TTS_EQUAL(eve::add(T{2}, v_t{2}, v_t{4} ), T(8));

  TTS_EQUAL(eve::add(v_t{0},   T{0}, v_t{1}),   T(1));
  TTS_EQUAL(eve::add(v_t{1},   T{1},   T{4}),   T(6));
  TTS_EQUAL(eve::add(v_t{2}, v_t{2}, v_t{1}), v_t(5));
  TTS_EQUAL(eve::add(v_t{2}, v_t{2},   T{1}),   T(5));

  TTS_EQUAL(eve::saturated(eve::add)(T{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::saturated(eve::add)(T{1}, T{1}, T{1}), T(3));
  TTS_EQUAL(eve::saturated(eve::add)(T{2}, T{2}, T{4}), T(8));
  TTS_EQUAL(eve::saturated(eve::add)(v_t{2}, v_t{2}, T{1}), T(5));


  TTS_EQUAL(eve::saturated(eve::add)(v_t{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::saturated(eve::add)(v_t{1}, T{1}, T{4}), T(6));
  TTS_EQUAL(eve::saturated(eve::add)(v_t{2}, T{2}, T{1}), T(5));
  TTS_EQUAL(eve::saturated(eve::add)(v_t{2}, v_t{2}, T{1}), T(5));

}
