//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/max.hpp>
#include <eve/function/pedantic/max.hpp>
#include <eve/function/numeric/max.hpp>


TTS_CASE_TPL("Check eve::max return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::max(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::max(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::max(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::max(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::max(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::max(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::max(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::max(v_t(), v_t(), v_t()), v_t);
  if constexpr(eve::simd_value<T>)
  {
    TTS_EXPR_IS(eve::max(int(), int(), T()  ), T);
    TTS_EXPR_IS(eve::max(T(), int(), float() ), T);
  }

}

TTS_CASE_TPL("Check eve::max behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::max(T{0},   T{0}, T{0})  , T(0));
  TTS_EQUAL(eve::max(T{1},   T{1}, v_t{1}), T(1));
  TTS_EQUAL(eve::max(T{2}, v_t{2}, T{4})  , T(4));
  TTS_EQUAL(eve::max(T{7}, v_t{2}, v_t{1} ), T(7));

  TTS_EQUAL(eve::max(v_t{0},   T{0}, v_t{1}),   T(1));
  TTS_EQUAL(eve::max(v_t{1},   T{1},   T{4}),   T(4));
  TTS_EQUAL(eve::max(v_t{2}, v_t{2}, v_t{1}), v_t(2));
  TTS_EQUAL(eve::max(v_t{2}, v_t{2},   T{1}),   T(2));

  TTS_EQUAL(eve::pedantic(eve::max)(T{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::pedantic(eve::max)(T{1}, T{1}, T{1}), T(1));
  TTS_EQUAL(eve::pedantic(eve::max)(T{2}, T{2}, T{4}), T(4));
  TTS_EQUAL(eve::pedantic(eve::max)(v_t{2}, v_t{0}, T{1}), T(2));


  TTS_EQUAL(eve::pedantic(eve::max)(v_t{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::pedantic(eve::max)(v_t{1}, T{1}, T{4}), T(4));
  TTS_EQUAL(eve::pedantic(eve::max)(v_t{2}, T{2}, T{1}), T(2));
  TTS_EQUAL(eve::pedantic(eve::max)(v_t{2}, v_t{2}, T{1}), T(2));

  TTS_EQUAL(eve::numeric(eve::max)(T{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::numeric(eve::max)(T{1}, T{1}, T{1}), T(1));
  TTS_EQUAL(eve::numeric(eve::max)(T{2}, T{2}, T{4}), T(4));
  TTS_EQUAL(eve::numeric(eve::max)(v_t{2}, v_t{0}, T{1}), T(2));


  TTS_EQUAL(eve::numeric(eve::max)(v_t{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::numeric(eve::max)(v_t{1}, T{1}, T{4}), T(4));
  TTS_EQUAL(eve::numeric(eve::max)(v_t{2}, T{2}, T{1}), T(2));
  TTS_EQUAL(eve::numeric(eve::max)(v_t{2}, v_t{2}, T{1}), T(2));
}
