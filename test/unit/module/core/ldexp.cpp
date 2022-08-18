//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of ldexp", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::ldexp;
  using eve::pedantic;
  using v_t  = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<T, signed>;
  using u_t  = eve::as_integer_t<T, unsigned>;
  using si_t = eve::as_integer_t<v_t, signed>;
  using su_t = eve::as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(eve::ldexp(T(), i_t()), T);
  TTS_EXPR_IS(ldexp(T(), u_t()), T);
  TTS_EXPR_IS(ldexp(T(), si_t()), T);
  TTS_EXPR_IS(ldexp(T(), su_t()), T);
  TTS_EXPR_IS(ldexp(T(), int()), T);

  TTS_EXPR_IS(ldexp(T(), T()), T);
  TTS_EXPR_IS(ldexp(T(), v_t()), T);
  TTS_EXPR_IS(ldexp(v_t(), v_t()), v_t);
  TTS_EXPR_IS(ldexp(v_t(), T()), T);

  TTS_EXPR_IS(pedantic(ldexp)(T(), i_t()), T);
  TTS_EXPR_IS(pedantic(ldexp)(T(), u_t()), T);
  TTS_EXPR_IS(pedantic(ldexp)(T(), si_t()), T);
  TTS_EXPR_IS(pedantic(ldexp)(T(), su_t()), T);
  TTS_EXPR_IS(pedantic(ldexp)(T(), int()), T);

  TTS_EXPR_IS(pedantic(ldexp)(T(), T()), T);
  TTS_EXPR_IS(pedantic(ldexp)(T(), v_t()), T);
  TTS_EXPR_IS(pedantic(ldexp)(v_t(), v_t()), v_t);
  TTS_EXPR_IS(pedantic(ldexp)(v_t(), T()), T);
};

//==================================================================================================
// ldexp  simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of ldexps on floatings",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-50, +50), tts::randoms(-50, +50), tts::logicals(0, 3)))
<typename T, typename U>(T const& a0, T const& a11, U const& t)
{
  using v_t = eve::element_type_t<T>;
  auto a1   = eve::trunc(a11);
  TTS_EQUAL(eve::ldexp(a0, a1),
            map([](auto e, auto f) { return v_t(std::ldexp(e, int(f))); }, a0, a1));
  TTS_EQUAL(eve::ldexp[t](a0, a1), eve::if_else(t, eve::ldexp(a0, a1), a0));
  //  TTS_EQUAL( eve::pedantic(eve::ldexp[t])(a0, a1), eve::if_else(t, eve::pedantic(eve::ldexp)(a0,
  //  a1), a0));
};

//==================================================================================================
// ldexp  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of ldexp on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100.0, 100.0)))
<typename T>(T a0)
{
  using eve::ldexp;
  TTS_EQUAL(ldexp(a0, 0), a0);
  TTS_EQUAL(ldexp(a0, 1), 2 * a0);
  TTS_EQUAL(ldexp(a0, -1), a0 / 2);

  using v_t  = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<T, signed>;
  using si_t = eve::as_integer_t<v_t, signed>;

  TTS_EXPECT(eve::all(eve::is_negative(ldexp(T(-0.0), i_t(0)))));
  TTS_EXPECT(eve::all(eve::is_positive(ldexp(T(0.0), i_t(0)))));

  TTS_EQUAL(ldexp(T(0), i_t(0)), T(0));
  TTS_EQUAL(ldexp(T(-0.), i_t(0)), T(0));
  TTS_EQUAL(ldexp(T(0), i_t(2)), T(0));
  TTS_EQUAL(ldexp(T(1), i_t(2)), T(4));
  TTS_EQUAL(ldexp(T(0), si_t(2)), T(0));
  TTS_EQUAL(ldexp(T(1), si_t(2)), T(4));
  TTS_EQUAL(ldexp(T(-1), i_t(2)), T(-4));
  TTS_EQUAL(ldexp(T(-2), i_t(2)), T(-8));
  TTS_EQUAL(ldexp(T(-1), si_t(2)), T(-4));
  TTS_EQUAL(ldexp(T(-2), si_t(2)), T(-8));
  TTS_EQUAL(ldexp(T(0), si_t(0)), T(0));
  TTS_EQUAL(ldexp(T(0), si_t(1)), T(0));
  TTS_EQUAL(ldexp(T(0), si_t(1000)), T(0));

  TTS_EQUAL((ldexp)(1.0, 0), 1.0);
  TTS_EQUAL((ldexp)(T(1.0), 0), T(1.0));
  TTS_EQUAL((ldexp)(1.0, 1), 2.0);
  TTS_EQUAL((ldexp)(1.0, -1), 0.5);

  using eve::pedantic;

  TTS_EQUAL(pedantic(ldexp)(a0, 0), a0);
  TTS_EQUAL(pedantic(ldexp)(a0, 1), 2 * a0);
  TTS_EQUAL(pedantic(ldexp)(a0, -1), a0 / 2);
  TTS_EQUAL(pedantic(ldexp)(eve::valmax(eve::as<T>()) / 4, si_t(2)), eve::valmax(eve::as<T>()));
  TTS_EQUAL(pedantic(ldexp)(eve::valmax(eve::as<T>()) / 4, i_t(2)), eve::valmax(eve::as<T>()));
  TTS_EQUAL(pedantic(ldexp)(eve::mindenormal(eve::as<T>()), i_t(2)),
            eve::mindenormal(eve::as<T>()) * 4);
  TTS_EQUAL(pedantic(ldexp)(eve::mindenormal(eve::as<T>()), si_t(2)),
            eve::mindenormal(eve::as<T>()) * 4);
  TTS_EQUAL(pedantic(ldexp)(T(0), si_t(0)), T(0));
  TTS_EQUAL(pedantic(ldexp)(T(0), si_t(1)), T(0));
  TTS_EQUAL(pedantic(ldexp)(T(0), si_t(1000)), T(0));
  TTS_EQUAL(pedantic(ldexp)(T(-0.0), si_t(0)), T(0));
  TTS_EQUAL(pedantic(ldexp)(T(-0.0), si_t(1)), T(0));
  TTS_EQUAL(pedantic(ldexp)(T(-0.0), si_t(1000)), T(0));

  TTS_EQUAL(pedantic(ldexp)(1.0, 0), 1.0);
  TTS_EQUAL(pedantic(ldexp)(1.0, 1), 2.0);
  TTS_EQUAL(pedantic(ldexp)(1.0, -1), 0.5);
  TTS_EQUAL(pedantic(ldexp)(eve::valmax(eve::as<T>()) / 4, si_t(2)), eve::valmax(eve::as<T>()));
  TTS_EQUAL(pedantic(ldexp)(eve::valmax(eve::as<T>()) / 4, i_t(2)), eve::valmax(eve::as<T>()));
  TTS_EQUAL(pedantic(ldexp)(eve::mindenormal(eve::as<T>()), i_t(2)),
            eve::mindenormal(eve::as<T>()) * 4);
  TTS_EQUAL(pedantic(ldexp)(eve::mindenormal(eve::as<T>()), si_t(2)),
            eve::mindenormal(eve::as<T>()) * 4);
  TTS_EQUAL(pedantic(ldexp)(eve::smallestposval(eve::as<T>()), i_t(-2)),
            eve::smallestposval(eve::as<T>()) / 4);
  TTS_EQUAL(pedantic(ldexp)(eve::smallestposval(eve::as<T>()), si_t(-2)),
            eve::smallestposval(eve::as<T>()) / 4);
  TTS_EQUAL(pedantic(ldexp)(T(0), si_t(0)), T(0));
  TTS_EQUAL(pedantic(ldexp)(T(0), si_t(1)), T(0));
  TTS_EQUAL(pedantic(ldexp)(T(0), si_t(1000)), T(0));
  TTS_EQUAL(pedantic(ldexp)(T(-0.0), si_t(0)), T(0));
  TTS_EQUAL(pedantic(ldexp)(T(-0.0), si_t(1)), T(0));
  TTS_EQUAL(pedantic(ldexp)(T(-0.0), si_t(1000)), T(0));

  TTS_EQUAL(pedantic(ldexp)(1.0, 0), 1.0);
  TTS_EQUAL(pedantic(ldexp)(T(1.0), 0), T(1.0));
  TTS_EQUAL(pedantic(ldexp)(1.0, 1), 2.0);
  TTS_EQUAL(pedantic(ldexp)(1.0, -1), 0.5);
};


//==================================================================================================
// Tests for masked ldexp
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::ldexp)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::ldexp[mask](a0, 4),
            eve::if_else(mask, eve::ldexp(a0, 4), a0));
};
