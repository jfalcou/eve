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
TTS_CASE_TPL("Check return types of maxmag", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::maxmag(T(), T(), T()), T);
  TTS_EXPR_IS(eve::maxmag(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::maxmag(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::maxmag(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::maxmag(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::maxmag(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::maxmag(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::maxmag(T(), T(), T()), T);
  TTS_EXPR_IS(eve::maxmag(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::maxmag(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::maxmag(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::maxmag(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::maxmag(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::maxmag(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::maxmag(v_t(), v_t(), v_t()), v_t);
};

auto vmin = tts::constant(
    []<typename T>(eve::as<T> const& tgt)
    {
      {
        constexpr auto sign = std::is_signed_v<T> ? 1 : 0;
        return eve::valmin(tgt) + sign;
      }
    });
//==================================================================================================
// maxmag tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of maxmag on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(vmin, eve::valmax),
                            tts::randoms(vmin, eve::valmax),
                            tts::randoms(vmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& mask)
{
  using eve::abs;
  using eve::maxmag;
  using v_t = eve::element_type_t<T>;
  auto m    = [](auto a, auto b, auto c) -> v_t { return maxmag(maxmag(b, c), a); };
  TTS_ULP_EQUAL(maxmag((a0), (a1), (a2)), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::maxmag[eve::pedantic]((a0), (a1), (a2)), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::maxmag[eve::numeric]((a0), (a1), (a2)), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::maxmag[eve::saturated]((a0), (a1), (a2)), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(maxmag(kumi::tuple{(a0), (a1), (a2)}), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::maxmag[eve::pedantic](kumi::tuple{(a0), (a1), (a2)}), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::maxmag[eve::numeric](kumi::tuple{(a0), (a1), (a2)}), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::maxmag[eve::saturated](kumi::tuple{(a0), (a1), (a2)}), tts::map(m, a0, a1, a2), 2);

  TTS_IEEE_EQUAL(maxmag[mask](a0, a1), eve::if_else(mask, maxmag(a0, a1), a0));
  auto k = (eve::unsigned_value<v_t>) ? v_t(0) : v_t(T::size()/2);
  v_t v(-100);
  auto t = [v, k](auto p){ return (p == T::size()-1) ? v : v_t(p/2-k); };
  constexpr auto s = 3*T::size()/2;
  auto tup = kumi::generate<s>(t);
  TTS_ULP_EQUAL(maxmag(tup), v, 0.5);
};

TTS_CASE_TPL("Check values of maxmag", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::maxmag[eve::pedantic](eve::nan(eve::as<T>()), T(1)), eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::maxmag[eve::pedantic](eve::nan(eve::as<v_t>()), T(1)),
                 eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::maxmag[eve::pedantic](eve::nan(eve::as<T>()), v_t(1)),
                 eve::nan(eve::as<T>()));

  TTS_IEEE_EQUAL(eve::maxmag[eve::pedantic](T(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::maxmag[eve::pedantic](v_t(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::maxmag[eve::pedantic](T(1), eve::nan(eve::as<v_t>())), T(1));

  TTS_EXPECT(eve::all(eve::is_positive(eve::maxmag[eve::pedantic](T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::maxmag[eve::pedantic](T(0), T(-0.)))));

  TTS_IEEE_EQUAL(eve::maxmag[eve::numeric]((eve::nan(eve::as<T>())), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::maxmag[eve::numeric]((eve::nan(eve::as<v_t>())), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::maxmag[eve::numeric]((eve::nan(eve::as<T>())), v_t(1)), T(1));

  TTS_IEEE_EQUAL(eve::maxmag[eve::numeric](T(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::maxmag[eve::numeric](v_t(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::maxmag[eve::numeric](T(1), eve::nan(eve::as<v_t>())), T(1));

  TTS_EXPECT(eve::all(eve::is_positive(eve::maxmag[eve::numeric](T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::maxmag[eve::numeric](T(0), T(-0.)))));
};


//==================================================================================================
//==  Tests for masked maxmag
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::maxmag)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::maxmag[mask](a0, a1),
            eve::if_else(mask, eve::maxmag(a0, a1), a0));
};
