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
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of tanpi"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::tanpi(T())  , T);
  TTS_EXPR_IS( eve::tanpi(v_t()), v_t);
};

//==================================================================================================
// tanpi  tests
//==================================================================================================
auto mquarter_c  = []<typename T>(eve::as<T> const & ){  return T(-0.25); };
auto quarter_c   = []<typename T>(eve::as<T> const & ){  return T( 0.25); };
auto mhalf_c = []<typename T>(eve::as<T> const & ){  return T(-0.5 ); };
auto half_c  = []<typename T>(eve::as<T> const & ){  return T( 0.5 ); };
auto mmed   = []<typename T>(eve::as<T> const & tgt){  return -eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt)*eve::inv_pi(tgt); };
auto med    = []<typename T>(eve::as<T> const & tgt){  return  eve::detail::Rempio2_limit(eve::detail::medium_type(), tgt)*eve::inv_pi(tgt); };

EVE_TEST( "Check behavior of tanpi on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mquarter_c, quarter_c)
                             , eve::test::randoms(mhalf_c, half_c)
                             , eve::test::randoms(mmed, med)
                             , eve::test::randoms(eve::valmin, eve::valmax))
                             )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using eve::tanpi;
  
  using eve::deginrad;
  using eve::pi;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { auto d = boost::math::cos_pi(e); return d ? boost::math::sin_pi(e)/d : eve::nan(eve::as(e)); };
  TTS_ULP_EQUAL(eve::quarter_circle(tanpi)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(tanpi)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(tanpi)(a1)           , map(ref, a1), 2);
  TTS_ULP_EQUAL(tanpi(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(tanpi(a1)                       , map(ref, a1), 2);
  TTS_ULP_EQUAL(tanpi(a2)                       , map(ref, a2), 2);
  TTS_ULP_EQUAL(tanpi(a3)                       , map(ref, a3), 2);
  
  
  
  
};
