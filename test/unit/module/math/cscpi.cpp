//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of cscpi"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::cscpi(T())  , T);
  TTS_EXPR_IS( eve::cscpi(v_t()), v_t);
};

//==================================================================================================
// cscpi  tests
//==================================================================================================
auto mquarter_c  = []<typename T>(eve::as<T> const & ){  return T(-0.25); };
auto quarter_c   = []<typename T>(eve::as<T> const & ){  return T( 0.25); };
auto mhalf_c = []<typename T>(eve::as<T> const & ){  return T(-0.5 ); };
auto half_c  = []<typename T>(eve::as<T> const & ){  return T( 0.5 ); };
auto mmed   = []<typename T>(eve::as<T> const & tgt){  return -eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt)*eve::inv_pi(tgt); };
auto med    = []<typename T>(eve::as<T> const & tgt){  return  eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt)*eve::inv_pi(tgt); };

EVE_TEST( "Check behavior of cscpi on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mquarter_c, quarter_c)
                             , eve::test::randoms(mhalf_c, half_c)
                             , eve::test::randoms(mmed, med)
                             , eve::test::randoms(eve::valmin, eve::valmax))
                             )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using eve::cscpi;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t {auto d = eve::sinpi(double(e));  return d ? 1.0/d :eve::nan(eve::as(e)); };

  using eve::deginrad;
  using eve::pi;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::quarter_circle(cscpi)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cscpi)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(cscpi)(a1)           , map(ref, a1), 2);
  TTS_ULP_EQUAL(cscpi(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(cscpi(a1)                       , map(ref, a1), 2);
  TTS_ULP_EQUAL(cscpi(a2)                       , map(ref, a2), 2);
  TTS_ULP_EQUAL(cscpi(a3)                       , map(ref, a3), 2);




};
