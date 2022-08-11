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
TTS_CASE_TPL("Check return types of maxabs", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::maxabs(T(), T(), T()), T);
  TTS_EXPR_IS(eve::maxabs(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::maxabs(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::maxabs(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::maxabs(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::maxabs(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::maxabs(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::maxabs(T(), T(), T()), T);
  TTS_EXPR_IS(eve::maxabs(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::maxabs(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::maxabs(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::maxabs(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::maxabs(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::maxabs(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::maxabs(v_t(), v_t(), v_t()), v_t);
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
// maxabs tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of maxabs on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(vmin, eve::valmax),
                            tts::randoms(vmin, eve::valmax),
                            tts::randoms(vmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::abs;
  using eve::maxabs;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  auto m    = [](auto a, auto b, auto c) -> v_t
  { return eve::max(eve::abs(a), eve::abs(b), eve::abs(c)); };
  TTS_ULP_EQUAL(maxabs((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(maxabs)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric(maxabs)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::saturated(maxabs)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);

  TTS_IEEE_EQUAL(maxabs[t](a0, a1), eve::if_else(t, maxabs(a0, a1), a0));
};

TTS_CASE_TPL("Check values of maxabs", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::pedantic(eve::maxabs)(eve::nan(eve::as<T>()), T(1)), eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::pedantic(eve::maxabs)(eve::nan(eve::as<v_t>()), T(1)),
                 eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::pedantic(eve::maxabs)(eve::nan(eve::as<T>()), v_t(1)),
                 eve::nan(eve::as<T>()));

  TTS_IEEE_EQUAL(eve::pedantic(eve::maxabs)(T(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::pedantic(eve::maxabs)(v_t(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::pedantic(eve::maxabs)(T(1), eve::nan(eve::as<v_t>())), T(1));

  TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic(eve::maxabs)(T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic(eve::maxabs)(T(0), T(-0.)))));

  TTS_IEEE_EQUAL(eve::numeric(eve::maxabs)((eve::nan(eve::as<T>())), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::maxabs)((eve::nan(eve::as<v_t>())), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::maxabs)((eve::nan(eve::as<T>())), v_t(1)), T(1));

  TTS_IEEE_EQUAL(eve::numeric(eve::maxabs)(T(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::maxabs)(v_t(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::maxabs)(T(1), eve::nan(eve::as<v_t>())), T(1));

  TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::maxabs)(T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::maxabs)(T(0), T(-0.)))));
};
