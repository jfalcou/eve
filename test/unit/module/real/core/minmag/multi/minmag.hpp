//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/min.hpp>
#include <eve/function/pedantic/minmag.hpp>
#include <eve/function/numeric/minmag.hpp>


TTS_CASE_TPL("Check eve::minmag return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::minmag(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::minmag(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::minmag(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::minmag(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::minmag(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::minmag(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::minmag(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::minmag(v_t(), v_t(), v_t()), v_t);
  if constexpr(eve::simd_value<T>)
  {
    TTS_EXPR_IS(eve::minmag(int(), int(), T()  ), T);
    TTS_EXPR_IS(eve::minmag(T(), int(), float() ), T);
  }

}

TTS_CASE_TPL("Check eve::minmag behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::minmag(T{0},   T{0}, T{0})  , T(0));
  TTS_EQUAL(eve::minmag(T{1},   T{1}, v_t{1}), T(1));
  TTS_EQUAL(eve::minmag(T{2}, v_t{2}, T{4})  , T(2));
  TTS_EQUAL(eve::minmag(T{7}, v_t{2}, v_t{1} ), T(1));

  TTS_EQUAL(eve::minmag(v_t{0},   T{0}, v_t{1}),   T(0));
  TTS_EQUAL(eve::minmag(v_t{1},   T{1},   T{4}),   T(1));
  TTS_EQUAL(eve::minmag(v_t{2}, v_t{2}, v_t{1}), v_t(1));
  TTS_EQUAL(eve::minmag(v_t{2}, v_t{2},   T{1}),   T(1));

  TTS_EQUAL(eve::pedantic(eve::minmag)(T{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::pedantic(eve::minmag)(T{1}, T{1}, T{1}), T(1));
  TTS_EQUAL(eve::pedantic(eve::minmag)(T{2}, T{2}, T{4}), T(2));
  TTS_EQUAL(eve::pedantic(eve::minmag)(v_t{2}, v_t{0}, T{1}), T(0));


  TTS_EQUAL(eve::pedantic(eve::minmag)(v_t{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::pedantic(eve::minmag)(v_t{1}, T{1}, T{4}), T(1));
  TTS_EQUAL(eve::pedantic(eve::minmag)(v_t{2}, T{2}, T{1}), T(1));
  TTS_EQUAL(eve::pedantic(eve::minmag)(v_t{2}, v_t{2}, T{1}), T(1));

  TTS_EQUAL(eve::numeric(eve::minmag)(T{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::numeric(eve::minmag)(T{1}, T{1}, T{1}), T(1));
  TTS_EQUAL(eve::numeric(eve::minmag)(T{2}, T{2}, T{4}), T(2));
  TTS_EQUAL(eve::numeric(eve::minmag)(v_t{2}, v_t{0}, T{1}), T(0));


  TTS_EQUAL(eve::numeric(eve::minmag)(v_t{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::numeric(eve::minmag)(v_t{1}, T{1}, T{4}), T(1));
  TTS_EQUAL(eve::numeric(eve::minmag)(v_t{2}, T{2}, T{1}), T(1));
  TTS_EQUAL(eve::numeric(eve::minmag)(v_t{2}, v_t{2}, T{1}), T(1));
}
