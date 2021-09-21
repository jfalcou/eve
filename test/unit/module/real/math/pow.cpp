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
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/log.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/pow.hpp>
#include <eve/function/diff/pow.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of pow"
            , eve::test::simd::all_types
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::pow(T(), T())  , T);
  TTS_EXPR_IS( eve::pow(v_t(), v_t()), v_t);
  TTS_EXPR_IS( eve::pow(T(), v_t()), T);
//  TTS_EXPR_IS( eve::pow(v_t(), T()), T);
};

//==================================================================================================
// pow  tests
//==================================================================================================
EVE_TEST( "Check behavior of pow on wide"
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

  TTS_ULP_EQUAL(eve::pow(a0, a1)      , map([](auto e, auto f) -> v_t { return std::pow(std::abs(e), f); }, a0, a1), 2);
  TTS_ULP_EQUAL(eve::pow(a2, a3)      , map([](auto e, auto f) -> v_t { return std::pow(std::abs(e), f); }, a2, a3), 2);
  TTS_ULP_EQUAL(eve::diff_1st(eve::pow)(a0, a1), eve::pow(a0, eve::dec(a1))*a1, 2);
  TTS_ULP_EQUAL(eve::diff_1st(eve::pow)(a2, a3), eve::pow(a2, eve::dec(a3))*a3, 2);
  TTS_ULP_EQUAL(eve::diff_2nd(eve::pow)(a0, a1), eve::pow(a0, a1)*eve::log(a0), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(eve::pow)(a2, a3), eve::pow(a2, a3)*eve::log(a2), 2);
};


EVE_TEST_TYPES( "Check  pow"
            , eve::test::simd::all_types
            )
<typename T>(eve::as<T>)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPECT(eve::all(eve::is_positive(eve::pow(eve::minf(eve::as<T>()), T(-4) ))));
    TTS_EXPECT(eve::all(eve::is_negative(eve::pow(eve::minf(eve::as<T>()), T(-3) ))));

    TTS_IEEE_EQUAL(eve::pow( T(0)          ,  T(-1)          ) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pow(-T(0)          ,  T(-1)          ) , eve::minf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pow(-T(0)          ,  T(-2)          ) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pow( T(0)          ,  T(-2)          ) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pow( T(0)          ,  eve::minf(eve::as<T>()) ) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pow(-T(0)          ,  eve::minf(eve::as<T>()) ) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pow(-T(1)          ,  eve::minf(eve::as<T>()) ) , T(1)          );
    TTS_IEEE_EQUAL(eve::pow(-T(1)          ,  eve::inf(eve::as<T>())  ) , T(1)          );
    TTS_IEEE_EQUAL(eve::pow( T(1)          ,  eve::nan(eve::as<T>())  ) , T(1)          );
    TTS_IEEE_EQUAL(eve::pow( eve::nan(eve::as<T>()) ,  T(0)           ) , T(1)          );
    TTS_IEEE_EQUAL(eve::pow( eve::nan(eve::as<T>()) , -T(0)           ) , T(1)          );
    TTS_IEEE_EQUAL(eve::pow( T(0.5)        ,  eve::inf(eve::as<T>())  ) , T( 0 )        );
    TTS_IEEE_EQUAL(eve::pow( T(2)          ,  eve::inf(eve::as<T>())  ) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pow( T(0.5)        ,  eve::minf(eve::as<T>()) ) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pow( T(2)          ,  eve::minf(eve::as<T>()) ) , T( 0 )        );
    TTS_IEEE_EQUAL(eve::pow(-T(0.5)        ,  eve::inf(eve::as<T>())  ) , T( 0 )        );
    TTS_IEEE_EQUAL(eve::pow(-T(2)          ,  eve::inf(eve::as<T>())  ) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pow(-T(0.5)        ,  eve::minf(eve::as<T>()) ) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pow(-T(2)          ,  eve::minf(eve::as<T>()) ) , T( 0 )        );
    TTS_IEEE_EQUAL(eve::pow( eve::minf(eve::as<T>()), -T(3)           ) , T(-0.)        );
    TTS_IEEE_EQUAL(eve::pow( eve::minf(eve::as<T>()), -T(4)           ) , T( 0 )        );
    TTS_IEEE_EQUAL(eve::pow( eve::inf(eve::as<T>()) ,  T(4)           ) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pow( eve::inf(eve::as<T>()) , -T(4)           ) , T( 0 )        );
  }

  TTS_EQUAL(eve::pow(T(2),-3), T(1/8.0));
  TTS_EQUAL(eve::pow(T(2),3) , T(8)    );
  TTS_EQUAL(eve::pow(T(2),3u), T(8)    );

  if constexpr(!eve::real_scalar_value<T>)
  {
    using v_t = eve::element_type_t<T>;
    if constexpr(std::is_floating_point_v < v_t > )
    {
      using w8_t =  eve::wide<v_t, eve::fixed<8>>;
      auto Inf =  eve::inf(eve::as<v_t>());
      {
        w8_t a(-0.0, -0.0,-0.0,-0.0,-1.0,-1.0, -Inf, -Inf);
        w8_t b(-Inf, -3.0,-4.0,-4.5,-Inf, Inf, -3.0, -4.0);
        w8_t r( Inf, -Inf, Inf, Inf, 1.0, 1.0, -0.0,  0.0);
        w8_t c = (eve::pow)(a, b);
        TTS_ULP_EQUAL(c ,r,2);
      }
      {
        using w4_t =  eve::wide<v_t, eve::fixed<4>>;
        w4_t a(-Inf, -Inf, -Inf, 0.0);
        w4_t b(-4.5,  4.0,  4.5, 0.0);
        w4_t r( 0.0,  Inf,  Inf, 1.0);
        w4_t c = (eve::pow)(a, b);
        TTS_ULP_EQUAL(c ,r,2);
      }
    }
  }
};
