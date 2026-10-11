//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of quadrant", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::quadrant(T())  , T  );
  TTS_EXPR_IS(eve::quadrant(v_t()), v_t);
};

//==================================================================================================
// On integers, quadrant keeps the two low bits
//==================================================================================================
TTS_CASE_WITH("Check behavior of quadrant on integers",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  // the mathematical modulo, which is what keeping the two low bits amounts to
  TTS_EQUAL(eve::quadrant(a0),
            tts::map([](auto e) -> v_t { return static_cast<v_t>(((e % 4) + 4) % 4); }, a0));
};

//==================================================================================================
// On floating values, it is the same cycle of four
//==================================================================================================
TTS_CASE_TPL("Check behavior of quadrant on floating values", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::quadrant(T(0)), T(0));
  TTS_EQUAL(eve::quadrant(T(1)), T(1));
  TTS_EQUAL(eve::quadrant(T(2)), T(2));
  TTS_EQUAL(eve::quadrant(T(3)), T(3));
  TTS_EQUAL(eve::quadrant(T(4)), T(0));
  TTS_EQUAL(eve::quadrant(T(5)), T(1));
  TTS_EQUAL(eve::quadrant(T(8)), T(0));
  TTS_EQUAL(eve::quadrant(T(-4)), T(0));
};

//==================================================================================================
// masked quadrant
//==================================================================================================
TTS_CASE_WITH("Check behavior of quadrant[mask]",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 100.0), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::quadrant[mask](a0), eve::if_else(mask, eve::quadrant(a0), a0));
};
