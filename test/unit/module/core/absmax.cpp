/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of absmax", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::absmax(T(), T(), T()), T);
  TTS_EXPR_IS(eve::absmax(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::absmax(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::absmax(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::absmax(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::absmax(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::absmax(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::absmax(T(), T(), T()), T);
  TTS_EXPR_IS(eve::absmax(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::absmax(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::absmax(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::absmax(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::absmax(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::absmax(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::absmax(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// absmax tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of absmax on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::abs;
  using eve::absmax;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  auto m    = [](auto a, auto b, auto c) -> v_t { return eve::abs(eve::max(a, b, c)); };

  TTS_ULP_EQUAL(absmax(a0, a1, a2), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(absmax[eve::pedantic](a0, a1, a2), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(absmax[eve::numeric](a0, a1, a2), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(absmax[eve::saturated](a0, a1, a2), map(m, a0, a1, a2), 2);
//  TTS_ULP_EQUAL(absmax(kumi::tuple{a0, a1, a2}), map(m, a0, a1, a2), 2);
//  TTS_ULP_EQUAL(absmax[eve::pedantic](kumi::tuple{a0, a1, a2}), map(m, a0, a1, a2), 2);
//  TTS_ULP_EQUAL(absmax[eve::numeric](kumi::tuple{a0, a1, a2}), map(m, a0, a1, a2), 2);
//  TTS_ULP_EQUAL(absmax[eve::saturated](kumi::tuple{a0, a1, a2}), map(m, a0, a1, a2), 2);

  TTS_IEEE_EQUAL(absmax[t](a0, a1), eve::if_else(t, absmax(a0, a1), a0));
};

TTS_CASE_TPL("Check values of absmax", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::absmax[eve::pedantic](eve::nan(eve::as<T>()), T(1)), eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::absmax[eve::pedantic](eve::nan(eve::as<v_t>()), T(1)),
                 eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::absmax[eve::pedantic](eve::nan(eve::as<T>()), v_t(1)),
                 eve::nan(eve::as<T>()));

  TTS_IEEE_EQUAL(eve::absmax[eve::pedantic](T(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::absmax[eve::pedantic](v_t(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::absmax[eve::pedantic](T(1), eve::nan(eve::as<v_t>())), T(1));

  TTS_EXPECT(eve::all(eve::is_positive(eve::absmax[eve::pedantic](T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::absmax[eve::pedantic](T(0), T(-0.)))));

  TTS_IEEE_EQUAL(eve::absmax[eve::numeric]((eve::nan(eve::as<T>())), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::absmax[eve::numeric]((eve::nan(eve::as<v_t>())), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::absmax[eve::numeric]((eve::nan(eve::as<T>())), v_t(1)), T(1));

  TTS_IEEE_EQUAL(eve::absmax[eve::numeric](T(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::absmax[eve::numeric](v_t(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::absmax[eve::numeric](T(1), eve::nan(eve::as<v_t>())), T(1));

  TTS_EXPECT(eve::all(eve::is_positive(eve::absmax[eve::numeric](T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::absmax[eve::numeric](T(0), T(-0.)))));
  if constexpr( eve::integral_value<T>)
  {
    TTS_IEEE_EQUAL(eve::absmax[eve::saturated](eve::valmin(eve::as<T>()), eve::valmin(eve::as<T>())),  eve::valmax(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::absmax(eve::valmin(eve::as<T>()), eve::valmin(eve::as<T>())),  eve::valmin(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::absmax[eve::numeric][eve::saturated](eve::valmin(eve::as<T>()), eve::valmin(eve::as<T>())),  eve::valmax(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::absmax[eve::numeric](eve::valmin(eve::as<T>()), eve::valmin(eve::as<T>())),  eve::valmin(eve::as<T>()));
  }
};


//==================================================================================================
//===  Tests for masked absmax
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::absmax)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::absmax[mask](a0, a1), eve::if_else(mask, eve::absmax(a0, a1), a0));
  TTS_IEEE_EQUAL(eve::absmax[mask][eve::saturated][eve::pedantic](a0, a1), eve::if_else(mask, eve::absmax[eve::saturated](a0, a1), a0));
};
