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

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of rempio2", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  auto [n, x, dx] = eve::rempio2(T());

  TTS_EXPR_IS(n , T);
  TTS_EXPR_IS(x , T);
  TTS_EXPR_IS(dx, T);
};

//==================================================================================================
// The contract: n is the quadrant, x + dx is the distance to the nearest multiple of pi/2.
// The input has to be non negative: the library always calls this on abs(x), and a negative
// argument comes back untouched with a zero quadrant.
//==================================================================================================
TTS_CASE_WITH("Check that rempio2 reduces modulo pi/2",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 100.0)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  auto [n, x, dx] = eve::rempio2(a0);

  // the reference runs in long double, which carries more mantissa than anything under test:
  // computing it in double would leave it less accurate than the double-double reduction itself
  constexpr long double pio2 = 1.57079632679489661923132169163975144l;

  auto quadrant = tts::map([](auto e) -> v_t
                           {
                             long double k = std::nearbyint((long double)(e) / pio2);
                             long double q = std::fmod(k, 4.0l);
                             return static_cast<v_t>(q < 0 ? q + 4 : q);
                           }, a0);
  auto rest     = tts::map([](auto e) -> v_t
                           {
                             long double x = (long double)(e);
                             return static_cast<v_t>(x - std::nearbyint(x / pio2) * pio2);
                           }, a0);

  TTS_EXPECT(eve::all(eve::is_flint(n)));
  TTS_EQUAL(n, quadrant);
  TTS_ULP_EQUAL(x + dx, rest, 4);
};

//==================================================================================================
// The remainder stays in the interval the reduction is meant to produce
//==================================================================================================
TTS_CASE_WITH("Check the range of the rempio2 remainder",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 100.0)))
<typename T>(T const& a0)
{
  auto [n, x, dx] = eve::rempio2(a0);
  auto bound      = eve::pio_4(eve::as(a0)) * T(1.0001);

  TTS_EXPECT(eve::all(eve::abs(x) <= bound));
  TTS_EXPECT(eve::all(n >= T(0)));
  TTS_EXPECT(eve::all(n <  T(4)));
  (void)dx;
};

//==================================================================================================
// Below pi/4 the reduction has nothing to do
//==================================================================================================
TTS_CASE_TPL("Check rempio2 on small inputs", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  auto [n, x, dx] = eve::rempio2[eve::quarter_circle](T(0.5));

  TTS_EQUAL(n, T(0));
  TTS_ULP_EQUAL(x + dx, T(0.5), 1);
};
