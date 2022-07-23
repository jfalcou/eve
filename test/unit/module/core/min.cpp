/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of min", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::min(T(), T(), T()), T);
  TTS_EXPR_IS(eve::min(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::min(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::min(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::min(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::min(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::min(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::min(T(), T(), T()), T);
  TTS_EXPR_IS(eve::min(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::min(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::min(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::min(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::min(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::min(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::min(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// min tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of min on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmin),
                            tts::randoms(eve::valmin, eve::valmin),
                            tts::randoms(eve::valmin, eve::valmin),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::abs;
  using eve::min;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  auto m    = [](auto a, auto b, auto c) -> v_t { return std::min(std::min(a, b), c); };
  TTS_ULP_EQUAL(min((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(min)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric(min)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);

  TTS_IEEE_EQUAL(min[t](a0, a1), eve::if_else(t, min(a0, a1), a0));
};

TTS_CASE_TPL("Check values of min", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::pedantic(eve::min)(eve::nan(eve::as<T>()), T(1)), eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::pedantic(eve::min)(eve::nan(eve::as<v_t>()), T(1)), eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::pedantic(eve::min)(eve::nan(eve::as<T>()), v_t(1)), eve::nan(eve::as<T>()));

  TTS_IEEE_EQUAL(eve::pedantic(eve::min)(T(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::pedantic(eve::min)(v_t(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::pedantic(eve::min)(T(1), eve::nan(eve::as<v_t>())), T(1));

  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic(eve::min)(T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic(eve::min)(T(0), T(-0.)))));

  TTS_IEEE_EQUAL(eve::numeric(eve::min)((eve::nan(eve::as<T>())), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::min)((eve::nan(eve::as<v_t>())), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::min)((eve::nan(eve::as<T>())), v_t(1)), T(1));

  TTS_IEEE_EQUAL(eve::numeric(eve::min)(T(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::min)(v_t(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::min)(T(1), eve::nan(eve::as<v_t>())), T(1));

  TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::min)(T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::min)(T(0), T(-0.)))));
};

TTS_CASE_WITH("Check predicate version of min",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmin),
                            tts::randoms(eve::valmin, eve::valmin)))
<typename T>(T const& a0, T const& a1)
{
  TTS_EXPR_IS(eve::min(eve::is_less), eve::callable_min_);
  TTS_EQUAL(eve::min(eve::is_less)(a0, a1), eve::min(a0, a1));

  auto pred = [](auto a, auto b) { return eve::abs(a) < eve::abs(b);};
  TTS_EQUAL(eve::min(pred)(a0, a1), eve::if_else(pred(a1,a0),a1,a0));

  // Check for stability a la Stepanov
  using e_t = eve::element_type_t<T>;
  using w_t = eve::wide<kumi::tuple<e_t,e_t>, eve::cardinal_t<T>>;

  w_t a { [](auto i, auto) { return i%2 ? i+1 : 0; }
        , [](auto i, auto) { return i+1; }
        };

  w_t b { [](auto i, auto) { return i%2 ? i : 0; }
        , [](auto i, auto) { return -(i+1); }
        };

  w_t ref { [=](auto i, auto) { return i%2 ? b.get(i) : a.get(i); } };

  auto less_1st = [](auto a, auto b) { return get<0>(a) < get<0>(b); };
  TTS_EQUAL( eve::min(less_1st)(a,b), ref );
};
