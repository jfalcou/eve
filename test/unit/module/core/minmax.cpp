/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
#include "test.hpp"
#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of minmax", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::minmax(T()  , T()  ), (kumi::tuple<T,T>)     );
  TTS_EXPR_IS(eve::minmax(T()  , v_t()), (kumi::tuple<T,T>)     );
  TTS_EXPR_IS(eve::minmax(v_t(), T()  ), (kumi::tuple<T,T>)     );
  TTS_EXPR_IS(eve::minmax(v_t(), v_t()), (kumi::tuple<v_t,v_t>) );
};

//==================================================================================================
// minmax tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of minmax on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, M const& m)
{
  auto[mn , mx] = eve::minmax(a0,a1);
  auto[mmn,mmx] = eve::minmax[m](a0,a1);
  TTS_IEEE_EQUAL (mn , eve::min(a0,a1)    );
  TTS_IEEE_EQUAL (mx , eve::max(a0,a1)    );
  TTS_IEEE_EQUAL (mmn, eve::min[m](a0,a1) );
  TTS_IEEE_EQUAL (mmx, eve::max[m](a0,a1) );
};

TTS_CASE_WITH ( "Check predicate version of minmax",
                eve::test::simd::all_types,
                tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                              , tts::randoms(eve::valmin, eve::valmax)
                              )
              )
<typename T>(T const& a0, T const& a1)
{
  TTS_EXPR_IS(eve::minmax(eve::is_less), eve::callable_minmax_);

  auto[mn,mx] = eve::minmax(a0, a1);

  auto[pn,px] = eve::minmax(eve::is_less)(a0, a1);
  TTS_EQUAL(pn, mn);
  TTS_EQUAL(px, mx);

  auto[rn,rx] = eve::minmax(eve::is_greater)(a0, a1);
  TTS_EQUAL(pn, rx);
  TTS_EQUAL(px, rn);

  auto pred = [](auto a, auto b) { return eve::abs(a) < eve::abs(b); };
  auto[amn,amx] = eve::minmax(pred)(a0, a1);

  TTS_EQUAL(eve::if_else(pred(a1, a0), a1, a0), amn);
  TTS_EQUAL(eve::if_else(pred(a1, a0), a0, a1), amx);

  // Check for stability a la Stepanov
  using e_t = eve::element_type_t<T>;
  using w_t = eve::wide<kumi::tuple<e_t, e_t>, eve::cardinal_t<T>>;

  w_t a {[](auto i, auto) { return i % 2 ? i / 2 + 1 : 0; }, [](auto i, auto) { return i + 1; }};
  w_t b {[](auto i, auto) { return i % 2 ? i / 2 : 0; }, [](auto i, auto) { return -(i + 1); }};

  auto less_1st = [](auto x, auto y) { return get<0>(x) < get<0>(y); };
  auto[smn,smx] = eve::minmax(less_1st)(a,b);

  TTS_EQUAL(smn, eve::min(less_1st)(a,b));
  TTS_EQUAL(smx, eve::max(less_1st)(a,b));
};
