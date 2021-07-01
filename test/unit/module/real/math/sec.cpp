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
#include <eve/function/sec.hpp>
#include <eve/function/tan.hpp>
#include <eve/function/diff/sec.hpp>
#include <cmath>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of sec"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sec(T())  , T);
  TTS_EXPR_IS( eve::sec(v_t()), v_t);
};

//==================================================================================================
// sec  tests
//==================================================================================================
auto mrest  = []<typename T>(eve::as_<T> const & tgt){  return -eve::pio_4(tgt); };
auto rest   = []<typename T>(eve::as_<T> const & tgt){  return  eve::pio_4(tgt); };
auto msmall = []<typename T>(eve::as_<T> const & tgt){  return -eve::pio_2(tgt); };
auto small  = []<typename T>(eve::as_<T> const & tgt){  return  eve::pio_2(tgt); };
auto mmed   = []<typename T>(eve::as_<T> const & tgt){  return -eve::detail::Rempio2_limit(eve::medium_type(), tgt); };
auto med    = []<typename T>(eve::as_<T> const & tgt){  return  eve::detail::Rempio2_limit(eve::medium_type(), tgt); };

EVE_TEST( "Check behavior of sec on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mrest, rest)
                             , eve::test::randoms(msmall, small)
                             , eve::test::randoms(mmed, med)
                             , eve::test::randoms(eve::valmin, eve::valmax))
                             )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using eve::sec;
  using eve::diff;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { return 1/std::cos(e); };
  TTS_ULP_EQUAL(eve::restricted(sec)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::small(sec)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::small(sec)(a1)           , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::medium(sec)(a0)          , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::medium(sec)(a1)          , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::medium(sec)(a2)          , map(ref, a2), 2);
  TTS_ULP_EQUAL(eve::big(sec)(a0)             , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::big(sec)(a1)             , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::big(sec)(a2)             , map(ref, a2), 2);
  TTS_ULP_EQUAL(eve::big(sec)(a3)             , map(ref, a3), 2);
  TTS_ULP_EQUAL(sec(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(sec(a1)                       , map(ref, a1), 2);
  TTS_ULP_EQUAL(sec(a2)                       , map(ref, a2), 2);
  TTS_ULP_EQUAL(sec(a3)                       , map(ref, a3), 2);
  TTS_ULP_EQUAL(diff(sec)(a0), map([](auto e) -> v_t { return   eve::sec(e)*tan(e); }, a0), 2);
};
