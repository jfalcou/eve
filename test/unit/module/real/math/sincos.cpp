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
#include <eve/function/cos.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/diff/cos.hpp>
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

  TTS_EXPR_IS( eve::sincos(T())  , (kumi::tuple<T, T>));
  TTS_EXPR_IS( eve::sincos(v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
// cos  tests
//==================================================================================================
auto mrest  = []<typename T>(eve::as_<T> const & tgt){  return -eve::pio_4(tgt); };
auto rest   = []<typename T>(eve::as_<T> const & tgt){  return  eve::pio_4(tgt); };
auto msmall = []<typename T>(eve::as_<T> const & tgt){  return -eve::pio_2(tgt); };
auto small  = []<typename T>(eve::as_<T> const & tgt){  return  eve::pio_2(tgt); };
auto mmed   = []<typename T>(eve::as_<T> const & tgt){  return -eve::detail::Rempio2_limit(eve::medium_type(), tgt); };
auto med    = []<typename T>(eve::as_<T> const & tgt){  return  eve::detail::Rempio2_limit(eve::medium_type(), tgt); };

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
  using eve::sincos;
  using eve::diff;
  using v_t = eve::element_type_t<T>;
  auto refc = [](auto e) -> v_t { return std::cos(e); };
  auto refs = [](auto e) -> v_t { return std::sin(e); };
  {
    auto [s, c] = eve::restricted(sincos)(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
  }
  {
    auto [s, c] = eve::small(sincos)(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
    auto [s1, c1] = eve::small(sincos)(a1);
    TTS_ULP_EQUAL(s1      , map(refs, a1), 2);
    TTS_ULP_EQUAL(c1      , map(refc, a1), 2);
  }
  {
    auto [s, c] = eve::medium(sincos)(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
    auto [s1, c1] = eve::medium(sincos)(a1);
    TTS_ULP_EQUAL(s1      , map(refs, a1), 2);
    TTS_ULP_EQUAL(c1      , map(refc, a1), 2);
    auto [s2, c2] = eve::medium(sincos)(a2);
    TTS_ULP_EQUAL(s2      , map(refs, a2), 2);
    TTS_ULP_EQUAL(c2      , map(refc, a2), 2);
  }
  {
    auto [s, c] = eve::big(sincos)(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
    auto [s1, c1] = eve::big(sincos)(a1);
    TTS_ULP_EQUAL(s1      , map(refs, a1), 2);
    TTS_ULP_EQUAL(c1      , map(refc, a1), 2);
    auto [s2, c2] = eve::big(sincos)(a2);
    TTS_ULP_EQUAL(s2      , map(refs, a2), 2);
    TTS_ULP_EQUAL(c2      , map(refc, a2), 2);
    auto [s3, c3] = eve::big(sincos)(a3);
    TTS_ULP_EQUAL(s3      , map(refs, a3), 2);
    TTS_ULP_EQUAL(c3      , map(refc, a3), 2);
  }
  {
    auto [s, c] = sincos(a0);
    TTS_ULP_EQUAL(s      , map(refs, a0), 2);
    TTS_ULP_EQUAL(c      , map(refc, a0), 2);
    auto [s1, c1] = sincos(a1);
    TTS_ULP_EQUAL(s1      , map(refs, a1), 2);
    TTS_ULP_EQUAL(c1      , map(refc, a1), 2);
    auto [s2, c2] = sincos(a2);
    TTS_ULP_EQUAL(s2      , map(refs, a2), 2);
    TTS_ULP_EQUAL(c2      , map(refc, a2), 2);
    auto [s3, c3] = sincos(a3);
    TTS_ULP_EQUAL(s3      , map(refs, a3), 2);
    TTS_ULP_EQUAL(c3      , map(refc, a3), 2);
  }
};
