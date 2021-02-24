//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/manhattan.hpp>
//#include <eve/function/saturated/manhattan.hpp>


TTS_CASE_TPL("Check eve::manhattan return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::manhattan(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::manhattan(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::manhattan(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::manhattan(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::manhattan(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::manhattan(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::manhattan(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::manhattan(v_t(), v_t(), v_t()), v_t);
  if constexpr(eve::simd_value<T>)
  {
    TTS_EXPR_IS(eve::manhattan(int(), int(), T()  ), T);
    TTS_EXPR_IS(eve::manhattan(T(), int(), float() ), T);
  }

}

TTS_CASE_TPL("Check eve::manhattan behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::manhattan(T{0},   T{0}, T{0})  , T(0));
  TTS_EQUAL(eve::manhattan(T{1},   T{1}, v_t{1}), T(3));
  TTS_EQUAL(eve::manhattan(T{2}, v_t{2}, T{4})  , T(8));
  TTS_EQUAL(eve::manhattan(T{2}, v_t{2}, v_t{4} ), T(8));

  TTS_EQUAL(eve::manhattan(v_t{0},   T{0}, v_t{1}),   T(1));
  TTS_EQUAL(eve::manhattan(v_t{1},   T{1},   T{4}),   T(6));
  TTS_EQUAL(eve::manhattan(v_t{2}, v_t{2}, v_t{1}), v_t(5));
  TTS_EQUAL(eve::manhattan(v_t{2}, v_t{2},   T{1}),   T(5));

//   TTS_EQUAL(eve::saturated(eve::manhattan)(T{0}, T{0}, T{0}), T(0));
//   TTS_EQUAL(eve::saturated(eve::manhattan)(T{1}, T{1}, T{1}), T(3));
//   TTS_EQUAL(eve::saturated(eve::manhattan)(T{2}, T{2}, T{4}), T(8));
//   TTS_EQUAL(eve::saturated(eve::manhattan)(v_t{2}, v_t{2}, T{1}), T(5));


//   TTS_EQUAL(eve::saturated(eve::manhattan)(v_t{0}, T{0}, T{0}), T(0));
//   TTS_EQUAL(eve::saturated(eve::manhattan)(v_t{1}, T{1}, T{4}), T(6));
//   TTS_EQUAL(eve::saturated(eve::manhattan)(v_t{2}, T{2}, T{1}), T(5));
//   TTS_EQUAL(eve::saturated(eve::manhattan)(v_t{2}, v_t{2}, T{1}), T(5));

}
