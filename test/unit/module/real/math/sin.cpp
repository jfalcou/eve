//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/diff/sin.hpp>
#include <cmath>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of sin"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sin(T())  , T);
  TTS_EXPR_IS( eve::sin(v_t()), v_t);
};

//==================================================================================================
// sin  tests
//==================================================================================================
auto mrest  = []<typename T>(eve::as<T> const & tgt){  return -eve::pio_4(tgt); };
auto rest   = []<typename T>(eve::as<T> const & tgt){  return  eve::pio_4(tgt); };
auto msmall = []<typename T>(eve::as<T> const & tgt){  return -eve::pio_2(tgt); };
auto small  = []<typename T>(eve::as<T> const & tgt){  return  eve::pio_2(tgt); };
auto mfull_circle= []<typename T>(eve::as<T> const & tgt){  return -eve::pi(tgt);    };
auto full_circle = []<typename T>(eve::as<T> const & tgt){  return  eve::pi(tgt);    };
auto mmed   = []<typename T>(eve::as<T> const & tgt){  return -eve::detail::Rempio2_limit(eve::medium_type(), tgt); };
auto med    = []<typename T>(eve::as<T> const & tgt){  return  eve::detail::Rempio2_limit(eve::medium_type(), tgt); };

EVE_TEST( "Check behavior of sin on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mrest, rest)
                             , eve::test::randoms(msmall, small)
                             , eve::test::randoms(mfull_circle, full_circle)
                             , eve::test::randoms(mmed, med)
                             , eve::test::randoms(eve::valmin, eve::valmax))
                             )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3, T const& a4)
{
  using eve::detail::map;
  using eve::sin;
  using eve::diff;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { return std::sin(e); };
  TTS_ULP_EQUAL(eve::quarter_circle(sin)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::small(sin)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::small(sin)(a1)           , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::full_circle(sin)(a0)          , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::full_circle(sin)(a1)          , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::full_circle(sin)(a2)          , map(ref, a2), 2);
  TTS_ULP_EQUAL(eve::medium(sin)(a0)          , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::medium(sin)(a1)          , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::medium(sin)(a2)          , map(ref, a2), 2);
  TTS_ULP_EQUAL(eve::medium(sin)(a3)          , map(ref, a3), 2);
  TTS_ULP_EQUAL(eve::big(sin)(a0)             , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::big(sin)(a1)             , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::big(sin)(a2)             , map(ref, a2), 2);
  TTS_ULP_EQUAL(eve::big(sin)(a3)             , map(ref, a3), 2);
  TTS_ULP_EQUAL(eve::big(sin)(a4)             , map(ref, a4), 2);
  TTS_ULP_EQUAL(sin(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(sin(a1)                       , map(ref, a1), 2);
  TTS_ULP_EQUAL(sin(a2)                       , map(ref, a2), 2);
  TTS_ULP_EQUAL(sin(a3)                       , map(ref, a3), 2);
  TTS_ULP_EQUAL(sin(a4)                       , map(ref, a4), 2);
  TTS_ULP_EQUAL(diff(sin)(a0), map([](auto e) -> v_t { return  std::cos(e); }, a0), 2);
};
