//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of csc"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::csc(T())  , T);
  TTS_EXPR_IS( eve::csc(v_t()), v_t);
};

//==================================================================================================
// csc  tests
//==================================================================================================
auto mquarter_c  = []<typename T>(eve::as<T> const & tgt){  return -eve::pio_4(tgt); };
auto quarter_c   = []<typename T>(eve::as<T> const & tgt){  return  eve::pio_4(tgt); };
auto mhalf_c = []<typename T>(eve::as<T> const & tgt){  return -eve::pio_2(tgt); };
auto half_c  = []<typename T>(eve::as<T> const & tgt){  return  eve::pio_2(tgt); };
auto mmed   = []<typename T>(eve::as<T> const & tgt){  return -eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt); };
auto med    = []<typename T>(eve::as<T> const & tgt){  return  eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt); };

EVE_TEST( "Check behavior of csc on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mquarter_c, quarter_c)
                             , eve::test::randoms(mhalf_c, half_c)
                             , eve::test::randoms(mmed, med)
                             , eve::test::randoms(eve::valmin, eve::valmax))
                             )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using eve::csc;
  using eve::diff;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { return 1.0/std::sin(double(e)); };
  TTS_ULP_EQUAL(eve::quarter_circle(csc)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(csc)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(csc)(a1)           , map(ref, a1), 2);
  TTS_ULP_EQUAL(csc(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(csc(a1)                       , map(ref, a1), 2);
  TTS_ULP_EQUAL(csc(a2)                       , map(ref, a2), 2);
  TTS_ULP_EQUAL(csc(a3)                       , map(ref, a3), 2);
  TTS_ULP_EQUAL(diff(csc)(a0), map([](auto e) -> v_t { return  -eve::csc(e)*eve::cot(e);}, a0), 2);
};
