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
#include <eve/function/cospi.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/function/sinpicospi.hpp>
#include <cmath>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of cos"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sinpicospi(T())  , (kumi::tuple<T, T>));
  TTS_EXPR_IS( eve::sinpicospi(v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
// cos  tests
//==================================================================================================
auto mrest  = []<typename T>(eve::as_<T> const & ){  return T(-0.25); };
auto rest   = []<typename T>(eve::as_<T> const & ){  return T( 0.25); };
auto msmall = []<typename T>(eve::as_<T> const & ){  return T(-0.5 ); };
auto small  = []<typename T>(eve::as_<T> const & ){  return T( 0.5 ); };
auto mmed   = []<typename T>(eve::as_<T> const & tgt){  return -eve::detail::Rempio2_limit(eve::medium_type(), tgt)*eve::invpi(tgt); };
auto med    = []<typename T>(eve::as_<T> const & tgt){  return  eve::detail::Rempio2_limit(eve::medium_type(), tgt)*eve::invpi(tgt); };

EVE_TEST( "Check behavior of cos on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mrest, rest)
                             , eve::test::randoms(msmall, small)
                             , eve::test::randoms(mmed, med)
                             , eve::test::randoms(eve::valmin, eve::valmax))
                             )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using eve::sinpicospi;
  using eve::diff;
  using v_t = eve::element_type_t<T>;
  auto refc = [](auto e) -> v_t { return eve::cospi(e); };
  auto refs = [](auto e) -> v_t { return eve::sinpi(e); };
  {
    auto [s, c] = eve::restricted(sinpicospi)(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
  }
  {
    auto [s, c] = eve::small(sinpicospi)(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
    auto [s1, c1] = eve::small(sinpicospi)(a1);
    TTS_ULP_EQUAL(s1      , map(refs, a1), 2);
    TTS_ULP_EQUAL(c1      , map(refc, a1), 2);
  }
  {
    auto [s, c] = eve::medium(sinpicospi)(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
    auto [s1, c1] = eve::medium(sinpicospi)(a1);
    TTS_ULP_EQUAL(s1      , map(refs, a1), 2);
    TTS_ULP_EQUAL(c1      , map(refc, a1), 2);
    auto [s2, c2] = eve::medium(sinpicospi)(a2);
    TTS_ULP_EQUAL(s2      , map(refs, a2), 2);
    TTS_ULP_EQUAL(c2      , map(refc, a2), 2);
  }
  {
    auto [s, c] = eve::big(sinpicospi)(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
    auto [s1, c1] = eve::big(sinpicospi)(a1);
    TTS_ULP_EQUAL(s1      , map(refs, a1), 2);
    TTS_ULP_EQUAL(c1      , map(refc, a1), 2);
    auto [s2, c2] = eve::big(sinpicospi)(a2);
    TTS_ULP_EQUAL(s2      , map(refs, a2), 2);
    TTS_ULP_EQUAL(c2      , map(refc, a2), 2);
    auto [s3, c3] = eve::big(sinpicospi)(a3);
    TTS_ULP_EQUAL(s3      , map(refs, a3), 2);
    TTS_ULP_EQUAL(c3      , map(refc, a3), 2);
  }
  {
    auto [s, c] = sinpicospi(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
    auto [s1, c1] = sinpicospi(a1);
    TTS_ULP_EQUAL(s1      , map(refs, a1), 2);
    TTS_ULP_EQUAL(c1      , map(refc, a1), 2);
    auto [s2, c2] = sinpicospi(a2);
    TTS_ULP_EQUAL(s2      , map(refs, a2), 2);
    TTS_ULP_EQUAL(c2      , map(refc, a2), 2);
    auto [s3, c3] = sinpicospi(a3);
    TTS_ULP_EQUAL(s3      , map(refs, a3), 2);
    TTS_ULP_EQUAL(c3      , map(refc, a3), 2);
  }
};
