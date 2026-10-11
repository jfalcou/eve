//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of reldist", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::reldist(T()  , T()  ), T  );
  TTS_EXPR_IS(eve::reldist(T()  , v_t()), T  );
  TTS_EXPR_IS(eve::reldist(v_t(), T()  ), T  );
  TTS_EXPR_IS(eve::reldist(v_t(), v_t()), v_t);
};

//==================================================================================================
// reldist(x, y) is |x-y| divided by the largest of |x|, |y| and 1
//==================================================================================================
TTS_CASE_WITH("Check behavior of reldist",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100.0, 100.0), tts::randoms(-100.0, 100.0)))
<typename T>(T const& a0, T const& a1)
{
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::reldist(a0, a1),
                tts::map([](auto x, auto y) -> v_t
                         {
                           auto d = x < y ? y - x : x - y;
                           auto ax = x < 0 ? -x : x;
                           auto ay = y < 0 ? -y : y;
                           auto m  = ax < ay ? ay : ax;
                           return d / (m < 1 ? v_t(1) : m);
                         }, a0, a1),
                2);
};

//==================================================================================================
// The properties the definition is meant to give
//==================================================================================================
TTS_CASE_TPL("Check the properties of reldist", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::reldist(T(3)   , T(3)   ), T(0));
  TTS_EQUAL(eve::reldist(T(0)   , T(0)   ), T(0));
  TTS_EQUAL(eve::reldist(T(0)   , T(1)   ), T(1));
  TTS_EQUAL(eve::reldist(T(-0.5), T(0.5) ), T(1));

  // symmetric in its arguments, and never above 2
  TTS_EQUAL(eve::reldist(T(4), T(1)), eve::reldist(T(1), T(4)));
  TTS_EXPECT(eve::all(eve::reldist(T(100), T(-100)) <= T(2)));
};

//==================================================================================================
// masked reldist
//==================================================================================================
TTS_CASE_WITH("Check behavior of reldist[mask]",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100.0, 100.0), tts::randoms(-100.0, 100.0),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, M const& mask)
{
  TTS_IEEE_EQUAL(eve::reldist[mask](a0, a1), eve::if_else(mask, eve::reldist(a0, a1), a0));
};
