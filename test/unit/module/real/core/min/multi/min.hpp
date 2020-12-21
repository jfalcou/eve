//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/min.hpp>
#include <eve/function/pedantic/min.hpp>
#include <eve/function/numeric/min.hpp>


TTS_CASE_TPL("Check eve::min return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::min(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::min(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::min(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::min(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::min(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::min(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::min(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::min(v_t(), v_t(), v_t()), v_t);
  if constexpr(eve::simd_value<T>)
  {
    TTS_EXPR_IS(eve::min(int(), int(), T()  ), T);
    TTS_EXPR_IS(eve::min(T(), int(), float() ), T);
  }

}

TTS_CASE_TPL("Check eve::min behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::min(T{0},   T{0}, T{0})  , T(0));
  TTS_EQUAL(eve::min(T{1},   T{1}, v_t{1}), T(1));
  TTS_EQUAL(eve::min(T{2}, v_t{2}, T{4})  , T(2));
  TTS_EQUAL(eve::min(T{7}, v_t{2}, v_t{1} ), T(1));

  TTS_EQUAL(eve::min(v_t{0},   T{0}, v_t{1}),   T(0));
  TTS_EQUAL(eve::min(v_t{1},   T{1},   T{4}),   T(1));
  TTS_EQUAL(eve::min(v_t{2}, v_t{2}, v_t{1}), v_t(1));
  TTS_EQUAL(eve::min(v_t{2}, v_t{2},   T{1}),   T(1));

  TTS_EQUAL(eve::pedantic(eve::min)(T{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::pedantic(eve::min)(T{1}, T{1}, T{1}), T(1));
  TTS_EQUAL(eve::pedantic(eve::min)(T{2}, T{2}, T{4}), T(2));
  TTS_EQUAL(eve::pedantic(eve::min)(v_t{2}, v_t{0}, T{1}), T(0));


  TTS_EQUAL(eve::pedantic(eve::min)(v_t{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::pedantic(eve::min)(v_t{1}, T{1}, T{4}), T(1));
  TTS_EQUAL(eve::pedantic(eve::min)(v_t{2}, T{2}, T{1}), T(1));
  TTS_EQUAL(eve::pedantic(eve::min)(v_t{2}, v_t{2}, T{1}), T(1));

  TTS_EQUAL(eve::numeric(eve::min)(T{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::numeric(eve::min)(T{1}, T{1}, T{1}), T(1));
  TTS_EQUAL(eve::numeric(eve::min)(T{2}, T{2}, T{4}), T(2));
  TTS_EQUAL(eve::numeric(eve::min)(v_t{2}, v_t{0}, T{1}), T(0));


  TTS_EQUAL(eve::numeric(eve::min)(v_t{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::numeric(eve::min)(v_t{1}, T{1}, T{4}), T(1));
  TTS_EQUAL(eve::numeric(eve::min)(v_t{2}, T{2}, T{1}), T(1));
  TTS_EQUAL(eve::numeric(eve::min)(v_t{2}, v_t{2}, T{1}), T(1));
}
