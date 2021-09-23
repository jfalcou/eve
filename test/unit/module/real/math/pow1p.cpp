//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/pow1p.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/diff/pow1p.hpp>
#include <eve/function/log1p.hpp>
#include <cmath>

//==================================================================================================
//=== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of pow1p"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::pow1p(T(), T())  , T);
  TTS_EXPR_IS( eve::pow1p(v_t(), v_t()), v_t);
  TTS_EXPR_IS( eve::pow1p(T(), v_t()), T);
 TTS_EXPR_IS( eve::pow1p(v_t(), T()), T);
};

//==================================================================================================
//=== pow1p  tests
//==================================================================================================
EVE_TEST( "Check behavior of pow1p on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate( eve::test::randoms(0, eve::valmax)
                             , eve::test::randoms(eve::valmin, eve::valmax)
                             , eve::test::randoms(0.0, 1.0)
                             , eve::test::randoms(-1.0, 1.0))
        )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::pow1p(a0, a1)      , map([](auto e, auto f) -> v_t { return std::pow(double(e+1), double(f)); }, a0, a1), 64);
  TTS_ULP_EQUAL(eve::pow1p(a2, a3)      , map([](auto e, auto f) -> v_t { return std::pow(double(e+1), double(f)); }, a2, a3), 64);
  TTS_ULP_EQUAL(eve::diff(eve::pow1p)(a0, a1), eve::pow1p(a0, eve::dec(a1))*a1, 2);
  TTS_ULP_EQUAL(eve::diff(eve::pow1p)(a2, a3), eve::pow1p(a2, eve::dec(a3))*a3, 2);
  TTS_ULP_EQUAL(eve::diff_2nd(eve::pow1p)(a0, a1), eve::pow1p(a0, a1)*eve::log1p(a0), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(eve::pow1p)(a2, a3), eve::pow1p(a2, a3)*eve::log1p(a2), 2);
};


EVE_TEST_TYPES( "Check  pow1p"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using eve::dec;
  TTS_IEEE_EQUAL(eve::pow1p( T(-1)          ,  T(-1)          )          , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pow1p( T(-1)          ,  T(-2)          )          , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pow1p( T(-1)          ,  T(-2)          )          , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pow1p( T(-0.5)        ,  eve::inf(eve::as<T>())  ) , T(0 )        );
  TTS_IEEE_EQUAL(eve::pow1p( T(1)           ,  eve::inf(eve::as<T>())  ) , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pow1p( T(-0.5)        ,  eve::minf(eve::as<T>()) ) , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pow1p( T(1)           ,  eve::minf(eve::as<T>()) ) , T(0 )        );
  TTS_IEEE_EQUAL(eve::pow1p( T(0.5)         ,  eve::inf(eve::as<T>())  ) , eve::inf(eve::as<T>())  );
  TTS_IEEE_EQUAL(eve::pow1p( T(-3)          ,  eve::inf(eve::as<T>())  ) , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pow1p( T(0.5)         ,  eve::minf(eve::as<T>()) ) , T(0));
  TTS_IEEE_EQUAL(eve::pow1p( T(-1)          ,  eve::minf(eve::as<T>()) ) , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pow1p( eve::minf(eve::as<T>()), -T(3)           ) , T(0)        );
  TTS_IEEE_EQUAL(eve::pow1p( eve::minf(eve::as<T>()), -T(4)           ) , T(0)        );
  TTS_IEEE_EQUAL(eve::pow1p( eve::inf(eve::as<T>()) ,  T(4)           ) , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pow1p( eve::inf(eve::as<T>()) , -T(4)           ) , T( 0)        );
  TTS_IEEE_EQUAL(eve::pow1p( eve::eps(eve::as<T>()) , T(4)            ) , 1+4*eve::eps(eve::as<T>())       );


  using v_t =  eve::element_type_t<T>;
  using w8_t =  eve::wide<v_t, eve::fixed<8>>;
  auto Inf =  eve::inf(eve::as<v_t>());
  {
    w8_t a(-1.0, -1.0,-1.0,-1.0,-2.0,-2.0, -Inf, -Inf);
    w8_t b(-Inf, -3.0,-4.0,-4.5,-Inf, Inf, -3.0, -4.0);
    w8_t r( Inf, Inf, Inf, Inf, 1.0, 1.0, -0.0,  0.0);
    w8_t c = (eve::pow1p)(a, b);
    TTS_ULP_EQUAL(c , r, 2);
  }
  {
    using w4_t =  eve::wide<v_t, eve::fixed<4>>;
    w4_t a(-Inf, -Inf, -Inf, -1.0);
    w4_t b(-4.5,  4.0,  4.5, 0.0);
    w4_t r( 0.0,  Inf,  Inf, 1.0);
    w4_t c = (eve::pow1p)(a, b);
    TTS_ULP_EQUAL(c ,r,2);
  }
};
