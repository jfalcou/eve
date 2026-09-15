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

  // pi/2 split into three exactly representable doubles, the Cody-Waite way: the reference then
  // lands below eps(double), so it stays sharper than the reduction it checks on every target.
  // Using long double instead would collapse to plain double on MSVC and several ARM ABIs.
  constexpr double p1 = 1.57079632673412561417e+00;
  constexpr double p2 = 6.07710050650619224932e-11;
  constexpr double p3 = 2.02226624879595063154e-21;
  constexpr double pio2 = 1.5707963267948966;

  auto quadrant = tts::map([=](auto e) -> v_t
                           {
                             double q = std::fmod(std::nearbyint(double(e) / pio2), 4.0);
                             return static_cast<v_t>(q < 0 ? q + 4 : q);
                           }, a0);
  auto rest     = tts::map([=](auto e) -> v_t
                           {
                             double v = double(e);
                             double k = std::nearbyint(v / pio2);
                             return static_cast<v_t>(((v - k * p1) - k * p2) - k * p3);
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
