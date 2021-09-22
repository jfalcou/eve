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
#include <eve/function/fracscale.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/round.hpp>
#include <type_traits>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of fracscale"
            , eve::test::simd::restricted::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::fracscale(T(), int())  , T);
  TTS_EXPR_IS( eve::fracscale(v_t(), int()), v_t);
};

//==================================================================================================
//== fracscale simd tests
//==================================================================================================
EVE_TEST( "Check behavior of fracscale(wide) and diff on  floating types"
            , eve::test::simd::restricted::ieee_reals
            , eve::test::generate ( eve::test::randoms(-100.0, 100.0))
            )
<typename T>(T const& a0 )
{
  using eve::detail::map;
  using eve::diff;
  using eve::sqr;
  using eve::rec;
  TTS_ULP_EQUAL( eve::fracscale(a0, 4),  map([&](auto e) { return e-eve::ldexp(eve::nearest(eve::ldexp(e, 4)), -4); }, a0), 2);
  TTS_ULP_EQUAL( eve::fracscale(a0, 10), map([&](auto e) { return e-eve::ldexp(eve::nearest(eve::ldexp(e,10)), -10); }, a0), 2);

};

//==================================================================================================
// fracscale[cond](simd) tests
//==================================================================================================
EVE_TEST( "Check behavior of fracscale[cond](wide) on  floating types"
        , eve::test::simd::restricted::ieee_reals
        , eve::test::generate ( eve::test::randoms(0.0, 100.0)
                              , eve::test::logicals(0, 3))
        )
  <typename T, typename M>(T const& a0, M const & t)
{
  using eve::fracscale;

  TTS_EQUAL( fracscale(a0, 4), a0-eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4));
  std::integral_constant<int, 4> four;
  TTS_EQUAL( eve::to_nearest(fracscale)(a0, 4), a0-eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4));
  TTS_EQUAL( eve::upward(fracscale)(a0, 4),     a0-eve::ldexp(eve::ceil(   eve::ldexp(a0, 4)), -4));
  TTS_EQUAL( eve::downward(fracscale)(a0, 4),   a0-eve::ldexp(eve::floor(  eve::ldexp(a0, 4)), -4));
  TTS_EQUAL( eve::toward_zero(fracscale)(a0, 4),a0-eve::ldexp(eve::trunc(  eve::ldexp(a0, 4)), -4));

  TTS_EQUAL( fracscale(a0, four), a0-eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4));
  TTS_EQUAL( eve::to_nearest(fracscale)(a0, four), a0-eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4));
  TTS_EQUAL( eve::upward(fracscale)(a0, four),     a0-eve::ldexp(eve::ceil(   eve::ldexp(a0, 4)), -4));
  TTS_EQUAL( eve::downward(fracscale)(a0, four),   a0-eve::ldexp(eve::floor(  eve::ldexp(a0, 4)), -4));
  TTS_EQUAL( eve::toward_zero(fracscale)(a0, four),a0-eve::ldexp(eve::trunc(  eve::ldexp(a0, 4)), -4));

  TTS_EQUAL( fracscale[t](a0, four),                  eve::if_else(t, a0-eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL( eve::to_nearest(fracscale[t])(a0, four), eve::if_else(t, a0-eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL( eve::upward(fracscale[t])(a0, four),     eve::if_else(t, a0-eve::ldexp(eve::ceil(   eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL( eve::downward(fracscale[t])(a0, four),   eve::if_else(t, a0-eve::ldexp(eve::floor(  eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL( eve::toward_zero(fracscale[t])(a0, four),eve::if_else(t, a0-eve::ldexp(eve::trunc(  eve::ldexp(a0, 4)), -4), a0));

  TTS_EQUAL( fracscale[t](a0, 4),                  eve::if_else(t, a0-eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL( eve::to_nearest(fracscale[t])(a0, 4), eve::if_else(t, a0-eve::ldexp(eve::nearest(eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL( eve::upward(fracscale[t])(a0, 4),     eve::if_else(t, a0-eve::ldexp(eve::ceil(   eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL( eve::downward(fracscale[t])(a0, 4),   eve::if_else(t, a0-eve::ldexp(eve::floor(  eve::ldexp(a0, 4)), -4), a0));
  TTS_EQUAL( eve::toward_zero(fracscale[t])(a0, 4),eve::if_else(t, a0-eve::ldexp(eve::trunc(  eve::ldexp(a0, 4)), -4), a0));
                                                                      
};
