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
EVE_TEST_TYPES( "Check return types of atan2"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::atan2(T(), T())  , T);
  TTS_EXPR_IS( eve::atan2(v_t(), v_t()), v_t);
  TTS_EXPR_IS( eve::atan2(T(), v_t()), T);
  TTS_EXPR_IS( eve::atan2(v_t(), T()), T);
};

//==================================================================================================
// atan2  tests
//==================================================================================================
auto mini = [](auto tgt) { return eve::next(eve::mindenormal(tgt)); };
auto maxi = [](auto tgt) { return eve::valmax(tgt)/2; };

EVE_TEST( "Check behavior of atan2 on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(mini, maxi)
                             , eve::test::randoms(mini, maxi)
                             , eve::test::randoms(-1.0, 1.0)
                             , eve::test::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::atan2(a0, a1)      , map([](auto e, auto f) -> v_t { return std::atan2(e, f); }, a0, a1), 2);
  TTS_ULP_EQUAL(eve::atan2(a2, a3)      , map([](auto e, auto f) -> v_t { return std::atan2(e, f); }, a2, a3), 2);
  
  
  
  
};

EVE_TEST_TYPES( "Check behavior of pedantic(atan2)"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using eve::is_negative;
  using eve::is_positive;
  using eve::pedantic;
  using eve::all;

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::inf(eve::as<T>())         , T(1.)   ), eve::pio_2(eve::as<T>()) , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::inf(eve::as<T>())         , T(-1.)  ), eve::pio_2(eve::as<T>()) , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::minf(eve::as<T>())        , T(1.)   ), -eve::pio_2(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::minf(eve::as<T>())        , T(-1.)  ), -eve::pio_2(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)((T( 1.)) , eve::minf(eve::as<T>())       ), eve::pi(eve::as<T>())    , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)((T(-1.)) , eve::minf(eve::as<T>())       ), -eve::pi(eve::as<T>())   , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)((T( 1.)) , eve::inf(eve::as<T>())        ), T(0.)         , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)((T(-1.)) , eve::inf(eve::as<T>())        ), T(-0.)          , 0.5);

    TTS_EXPECT( eve::all(is_negative(pedantic(eve::atan2)((T(-1.)), eve::inf(eve::as<T>())))) );
    TTS_EXPECT( eve::all(is_positive(pedantic(eve::atan2)((T(1.)) , eve::inf(eve::as<T>())))) );

    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::minf(eve::as<T>()), eve::minf(eve::as<T>())), -3*eve::pio_4(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::inf(eve::as<T>()) , eve::minf(eve::as<T>())),  3*eve::pio_4(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::minf(eve::as<T>()), eve::inf(eve::as<T>()) ), -eve::pio_4(eve::as<T>())  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::inf(eve::as<T>()) , eve::inf(eve::as<T>()) ),  eve::pio_4(eve::as<T>())  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::inf(eve::as<T>()) , T(1.)),  eve::pio_2(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::minf(eve::as<T>()), T(1.)), -eve::pio_2(eve::as<T>()), 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::nan(eve::as<T>()), eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::nan(eve::as<T>()), (T(0.)))       , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)((T(0.))      , eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5);
  }

  TTS_ULP_EQUAL(pedantic(eve::atan2)(T( 0.5), T( 0.5)) ,  eve::pio_4(eve::as<T>())   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T(-0.5), T(-0.5)) , -3*eve::pio_4(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T(-1. ), T(-1. )) , -3*eve::pio_4(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T( 1. ), T( 1. )) ,  eve::pio_4(eve::as<T>())   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T( 0. ), T( 0. )) ,  (T(0.))           , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T(-0. ), T( 0. )) ,  T(-0.)            , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T(-0. ), T(-0. )) , -eve::pi(eve::as<T>())      , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T(-0. ), T(-1. )) , -eve::pi(eve::as<T>())      , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T( 0. ), T(-0. )) ,  eve::pi(eve::as<T>())      , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T( 0. ), T(-1. )) ,  eve::pi(eve::as<T>())      , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T(-1. ), T(-0. )) , -eve::pio_2(eve::as<T>())   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T(-1. ), T( 0. )) , -eve::pio_2(eve::as<T>())   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T( 1. ), T(-0. )) ,  eve::pio_2(eve::as<T>())   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T( 1. ), T( 0. )) ,  eve::pio_2(eve::as<T>())   , 0.5);
};
