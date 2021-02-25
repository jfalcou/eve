//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/maxmag.hpp>
#include <eve/function/pedantic/maxmag.hpp>
#include <eve/function/numeric/maxmag.hpp>


TTS_CASE_TPL("Check eve::maxmag return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::maxmag(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::maxmag(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::maxmag(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::maxmag(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::maxmag(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::maxmag(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::maxmag(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::maxmag(v_t(), v_t(), v_t()), v_t);
  if constexpr(eve::simd_value<T>)
  {
    TTS_EXPR_IS(eve::maxmag(int(), int(), T()  ), T);
    TTS_EXPR_IS(eve::maxmag(T(), int(), float() ), T);
  }

}

TTS_CASE_TPL("Check eve::maxmag behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::maxmag(T{0},   T{0}, T{0})  , T(0));
  TTS_EQUAL(eve::maxmag(T{1},   T{1}, v_t{1}), T(1));
  TTS_EQUAL(eve::maxmag(T{2}, v_t{2}, T{4})  , T(4));
  TTS_EQUAL(eve::maxmag(T{7}, v_t{2}, v_t{1} ), T(7));

  TTS_EQUAL(eve::maxmag(v_t{0},   T{0}, v_t{1}),   T(1));
  TTS_EQUAL(eve::maxmag(v_t{1},   T{1},   T{4}),   T(4));
  TTS_EQUAL(eve::maxmag(v_t{2}, v_t{2}, v_t{1}), v_t(2));
  TTS_EQUAL(eve::maxmag(v_t{2}, v_t{2},   T{1}),   T(2));

  TTS_EQUAL(eve::pedantic(eve::maxmag)(T{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::pedantic(eve::maxmag)(T{1}, T{1}, T{1}), T(1));
  TTS_EQUAL(eve::pedantic(eve::maxmag)(T{2}, T{2}, T{4}), T(4));
  TTS_EQUAL(eve::pedantic(eve::maxmag)(v_t{2}, v_t{0}, T{1}), T(2));


  TTS_EQUAL(eve::pedantic(eve::maxmag)(v_t{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::pedantic(eve::maxmag)(v_t{1}, T{1}, T{4}), T(4));
  TTS_EQUAL(eve::pedantic(eve::maxmag)(v_t{2}, T{2}, T{1}), T(2));
  TTS_EQUAL(eve::pedantic(eve::maxmag)(v_t{2}, v_t{2}, T{1}), T(2));

  TTS_EQUAL(eve::numeric(eve::maxmag)(T{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::numeric(eve::maxmag)(T{1}, T{1}, T{1}), T(1));
  TTS_EQUAL(eve::numeric(eve::maxmag)(T{2}, T{2}, T{4}), T(4));
  TTS_EQUAL(eve::numeric(eve::maxmag)(v_t{2}, v_t{0}, T{1}), T(2));


  TTS_EQUAL(eve::numeric(eve::maxmag)(v_t{0}, T{0}, T{0}), T(0));
  TTS_EQUAL(eve::numeric(eve::maxmag)(v_t{1}, T{1}, T{4}), T(4));
  TTS_EQUAL(eve::numeric(eve::maxmag)(v_t{2}, T{2}, T{1}), T(2));
  TTS_EQUAL(eve::numeric(eve::maxmag)(v_t{2}, v_t{2}, T{1}), T(2));
}
