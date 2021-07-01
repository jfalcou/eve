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
#include <eve/constant/invpi.hpp>
#include <eve/constant/pi.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/function/diff/sinpi.hpp>
#include <eve/function/deginrad.hpp>
#include <cmath>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <eve/detail/function/tmp/boost_math_cospi.hpp>
#include <eve/detail/function/tmp/boost_math_sinpi.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of sinpi"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sinpi(T())  , T);
  TTS_EXPR_IS( eve::sinpi(v_t()), v_t);
};

//==================================================================================================
// sinpi  tests
//==================================================================================================
auto mrest  = []<typename T>(eve::as_<T> const & ){  return T(-0.25); };
auto rest   = []<typename T>(eve::as_<T> const & ){  return T( 0.25); };
auto msmall = []<typename T>(eve::as_<T> const & ){  return T(-0.5 ); };
auto small  = []<typename T>(eve::as_<T> const & ){  return T( 0.5 ); };
auto mmed   = []<typename T>(eve::as_<T> const & tgt){  return -eve::detail::Rempio2_limit(eve::medium_type(), tgt)*eve::invpi(tgt); };
auto med    = []<typename T>(eve::as_<T> const & tgt){  return  eve::detail::Rempio2_limit(eve::medium_type(), tgt)*eve::invpi(tgt); };

EVE_TEST( "Check behavior of sinpi on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mrest, rest)
                             , eve::test::randoms(msmall, small)
                             , eve::test::randoms(mmed, med)
                             , eve::test::randoms(eve::valmin, eve::valmax))
                             )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using eve::sinpi;
  using eve::diff;
  using eve::deginrad;
  using eve::pi;
  using v_t = eve::element_type_t<T>;
  long double ldpi = 3.1415926535897932384626433832795028841971693993751;
  auto ref = [](auto e) -> v_t { return boost::math::sin_pi(e); };
  TTS_ULP_EQUAL(eve::restricted(sinpi)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::small(sinpi)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::small(sinpi)(a1)           , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::medium(sinpi)(a0)          , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::medium(sinpi)(a1)          , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::medium(sinpi)(a2)          , map(ref, a2), 2);
  TTS_ULP_EQUAL(eve::big(sinpi)(a0)             , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::big(sinpi)(a1)             , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::big(sinpi)(a2)             , map(ref, a2), 2);
  TTS_ULP_EQUAL(eve::big(sinpi)(a3)             , map(ref, a3), 2);
  TTS_ULP_EQUAL(sinpi(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(sinpi(a1)                       , map(ref, a1), 2);
  TTS_ULP_EQUAL(sinpi(a2)                       , map(ref, a2), 2);
  TTS_ULP_EQUAL(sinpi(a3)                       , map(ref, a3), 2);
  TTS_ULP_EQUAL(diff(sinpi)(a0), map([ldpi](auto e) -> v_t { return  ldpi*boost::math::cos_pi(e); }, a0), 2);
  TTS_ULP_EQUAL(diff(sinpi)(a1), map([ldpi](auto e) -> v_t { return  ldpi*boost::math::cos_pi(e); }, a1), 2);
  TTS_ULP_EQUAL(diff(sinpi)(a2), map([ldpi](auto e) -> v_t { return  ldpi*boost::math::cos_pi(e); }, a2), 2);
  TTS_ULP_EQUAL(diff(sinpi)(a3), map([ldpi](auto e) -> v_t { return  ldpi*boost::math::cos_pi(e); }, a3), 2);
};
