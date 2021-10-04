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
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/function/cscpi.hpp>
#include <eve/function/diff/cscpi.hpp>
#include <eve/function/cotpi.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/function/deginrad.hpp>
#include <cmath>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>

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
auto mrest  = []<typename T>(eve::as<T> const & ){  return T(-0.25); };
auto rest   = []<typename T>(eve::as<T> const & ){  return T( 0.25); };
auto msmall = []<typename T>(eve::as<T> const & ){  return T(-0.5 ); };
auto small  = []<typename T>(eve::as<T> const & ){  return T( 0.5 ); };
auto mmed   = []<typename T>(eve::as<T> const & tgt){  return -eve::detail::Rempio2_limit(eve::medium_type(), tgt)*eve::invpi(tgt); };
auto med    = []<typename T>(eve::as<T> const & tgt){  return  eve::detail::Rempio2_limit(eve::medium_type(), tgt)*eve::invpi(tgt); };

EVE_TEST( "Check behavior of cscpi on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mrest, rest)
                             , eve::test::randoms(msmall, small)
                             , eve::test::randoms(mmed, med)
                             , eve::test::randoms(eve::valmin, eve::valmax))
                             )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using eve::cscpi;
  using eve::diff;
  using eve::deginrad;
  using eve::pi;
  using v_t = eve::element_type_t<T>;
  long double ldpi = 3.1415926535897932384626433832795028841971693993751;
  auto ref = [](auto e) -> v_t {auto d = eve::sinpi(double(e));  return d ? 1.0/d :eve::nan(eve::as(e)); };
  TTS_ULP_EQUAL(eve::quarter_circle(cscpi)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::small(cscpi)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::small(cscpi)(a1)           , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::medium(cscpi)(a0)          , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::medium(cscpi)(a1)          , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::medium(cscpi)(a2)          , map(ref, a2), 2);
  TTS_ULP_EQUAL(eve::big(cscpi)(a0)             , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::big(cscpi)(a1)             , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::big(cscpi)(a2)             , map(ref, a2), 2);
  TTS_ULP_EQUAL(eve::big(cscpi)(a3)             , map(ref, a3), 2);
  TTS_ULP_EQUAL(cscpi(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(cscpi(a1)                       , map(ref, a1), 2);
  TTS_ULP_EQUAL(cscpi(a2)                       , map(ref, a2), 2);
  TTS_ULP_EQUAL(cscpi(a3)                       , map(ref, a3), 2);
  TTS_ULP_EQUAL(diff(cscpi)(a0), map([ldpi](auto e) -> v_t { return  -ldpi*cscpi(e)*eve::cotpi(e); }, a0), 2);
  TTS_ULP_EQUAL(diff(cscpi)(a1), map([ldpi](auto e) -> v_t { return  -ldpi*cscpi(e)*eve::cotpi(e); }, a1), 2);
  TTS_ULP_EQUAL(diff(cscpi)(a2), map([ldpi](auto e) -> v_t { return  -ldpi*cscpi(e)*eve::cotpi(e); }, a2), 2);
  TTS_ULP_EQUAL(diff(cscpi)(a3), map([ldpi](auto e) -> v_t { return  -ldpi*cscpi(e)*eve::cotpi(e); }, a3), 2);
};
