/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of minmag", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::minmag(T(), T(), T()), T);
  TTS_EXPR_IS(eve::minmag(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::minmag(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::minmag(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::minmag(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::minmag(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::minmag(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::minmag(T(), T(), T()), T);
  TTS_EXPR_IS(eve::minmag(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::minmag(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::minmag(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::minmag(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::minmag(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::minmag(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::minmag(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// minmag tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of minmag on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmin),
                            tts::randoms(eve::valmin, eve::valmin),
                            tts::randoms(eve::valmin, eve::valmin),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::abs;
  using eve::minmag;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  auto m    = [](auto a, auto b, auto c) -> v_t { return minmag(minmag(a, b), c); };
  TTS_ULP_EQUAL(minmag((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(minmag)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric(minmag)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::saturated(minmag)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);

  TTS_IEEE_EQUAL(minmag[t](a0, a1), eve::if_else(t, minmag(a0, a1), a0));
};

TTS_CASE_TPL("Check values of minmag", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(eve::nan(eve::as<T>()), T(1)), eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(eve::nan(eve::as<v_t>()), T(1)),
                 eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(eve::nan(eve::as<T>()), v_t(1)),
                 eve::nan(eve::as<T>()));

  TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(T(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(v_t(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(T(1), eve::nan(eve::as<v_t>())), T(1));

  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic(eve::minmag)(T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic(eve::minmag)(T(0), T(-0.)))));

  TTS_IEEE_EQUAL(eve::numeric(eve::minmag)((eve::nan(eve::as<T>())), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::minmag)((eve::nan(eve::as<v_t>())), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::minmag)((eve::nan(eve::as<T>())), v_t(1)), T(1));

  TTS_IEEE_EQUAL(eve::numeric(eve::minmag)(T(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::minmag)(v_t(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::minmag)(T(1), eve::nan(eve::as<v_t>())), T(1));

  TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::minmag)(T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::minmag)(T(0), T(-0.)))));
};
