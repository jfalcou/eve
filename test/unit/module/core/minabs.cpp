/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of minabs", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::minabs(T(), T(), T()), T);
  TTS_EXPR_IS(eve::minabs(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::minabs(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::minabs(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::minabs(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::minabs(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::minabs(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::minabs(T(), T(), T()), T);
  TTS_EXPR_IS(eve::minabs(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::minabs(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::minabs(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::minabs(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::minabs(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::minabs(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::minabs(v_t(), v_t(), v_t()), v_t);
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
// minabs tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of minabs on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(vmin, eve::valmax),
                            tts::randoms(vmin, eve::valmax),
                            tts::randoms(vmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::abs;
  using eve::minabs;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  auto m    = [](auto a, auto b, auto c) -> v_t
  { return eve::min(eve::abs(a), eve::abs(b), eve::abs(c)); };
  TTS_ULP_EQUAL(minabs((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(minabs)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric(minabs)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::saturated(minabs)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);

  TTS_IEEE_EQUAL(minabs[t](a0, a1), eve::if_else(t, minabs(a0, a1), a0));
};

TTS_CASE_TPL("Check values of minabs", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::pedantic(eve::minabs)(eve::nan(eve::as<T>()), T(1)), eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::pedantic(eve::minabs)(eve::nan(eve::as<v_t>()), T(1)),
                 eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::pedantic(eve::minabs)(eve::nan(eve::as<T>()), v_t(1)),
                 eve::nan(eve::as<T>()));

  TTS_IEEE_EQUAL(eve::pedantic(eve::minabs)(T(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::pedantic(eve::minabs)(v_t(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::pedantic(eve::minabs)(T(1), eve::nan(eve::as<v_t>())), T(1));

  TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic(eve::minabs)(T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic(eve::minabs)(T(0), T(-0.)))));

  TTS_IEEE_EQUAL(eve::numeric(eve::minabs)((eve::nan(eve::as<T>())), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::minabs)((eve::nan(eve::as<v_t>())), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::minabs)((eve::nan(eve::as<T>())), v_t(1)), T(1));

  TTS_IEEE_EQUAL(eve::numeric(eve::minabs)(T(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::minabs)(v_t(1), eve::nan(eve::as<T>())), T(1));
  TTS_IEEE_EQUAL(eve::numeric(eve::minabs)(T(1), eve::nan(eve::as<v_t>())), T(1));

  TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::minabs)(T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::minabs)(T(0), T(-0.)))));
};
