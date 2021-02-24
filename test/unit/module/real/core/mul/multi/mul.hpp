//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/mul.hpp>
#include <eve/function/saturated/mul.hpp>


TTS_CASE_TPL("Check eve::mul return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::mul(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::mul(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::mul(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::mul(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::mul(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::mul(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::mul(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::mul(v_t(), v_t(), v_t()), v_t);
  if constexpr(eve::simd_value<T>)
  {
    TTS_EXPR_IS(eve::mul(int(), int(), T()  ), T);
    TTS_EXPR_IS(eve::mul(T(), int(), float() ), T);
  }

}

TTS_CASE_TPL("Check eve::mul behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::mul(T{0},   T{0}, T{0})  , T(0));
  TTS_EQUAL(eve::mul(T{1},   T{1}, v_t{1}), T(1));
  TTS_EQUAL(eve::mul(T{2}, v_t{2}, T{4})  , T(16));
  TTS_EQUAL(eve::mul(T{2}, v_t{2}, v_t{4} ), T(16));

  TTS_EQUAL(eve::mul(v_t{0},   T{0}, v_t{1}),   T(0));
  TTS_EQUAL(eve::mul(v_t{1},   T{1},   T{4}),   T(4));
  TTS_EQUAL(eve::mul(v_t{2}, v_t{2}, v_t{1}), v_t(4));
  TTS_EQUAL(eve::mul(v_t{2}, v_t{2},   T{1}),   T(4));

  TTS_EQUAL(eve::saturated(eve::mul)(T{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::saturated(eve::mul)(T{1}, T{1}, T{1}), T(1));
  TTS_EQUAL(eve::saturated(eve::mul)(T{2}, T{2}, T{4}), T(16));
  TTS_EQUAL(eve::saturated(eve::mul)(v_t{2}, v_t{2}, T{1}), T(4));


  TTS_EQUAL(eve::saturated(eve::mul)(v_t{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::saturated(eve::mul)(v_t{1}, T{1}, T{4}), T(4));
  TTS_EQUAL(eve::saturated(eve::mul)(v_t{2}, T{2}, T{1}), T(4));
  TTS_EQUAL(eve::saturated(eve::mul)(v_t{2}, v_t{2}, T{1}), T(4));

}
