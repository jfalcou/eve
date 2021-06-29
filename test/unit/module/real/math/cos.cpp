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

  TTS_EXPR_IS( eve::cos(T())  , T);
  TTS_EXPR_IS( eve::cos(v_t()), v_t);
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
  using eve::cos;
  using eve::diff;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { return std::cos(e); };
  TTS_ULP_EQUAL(eve::restricted(cos)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::small(cos)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::small(cos)(a1)           , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::medium(cos)(a0)          , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::medium(cos)(a1)          , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::medium(cos)(a2)          , map(ref, a2), 2);
  TTS_ULP_EQUAL(eve::big(cos)(a0)             , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::big(cos)(a1)             , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::big(cos)(a2)             , map(ref, a2), 2);
  TTS_ULP_EQUAL(eve::big(cos)(a3)             , map(ref, a3), 2);
  TTS_ULP_EQUAL(cos(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(cos(a1)                       , map(ref, a1), 2);
  TTS_ULP_EQUAL(cos(a2)                       , map(ref, a2), 2);
  TTS_ULP_EQUAL(cos(a3)                       , map(ref, a3), 2);
  TTS_ULP_EQUAL(diff(cos)(a0), map([](auto e) -> v_t { return  -std::sin(e); }, a0), 2);
};
