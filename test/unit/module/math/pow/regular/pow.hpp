//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/basic.hpp>
#include <cmath>

TTS_CASE_TPL("Check pow_abs return type", EVE_TYPE)
{
  if (eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::pow(T(0), T(0)), T);
  }

  TTS_EXPR_IS(eve::pow(T(0), int(0)), T);
}

TTS_CASE_TPL("pow conformity", EVE_TYPE)
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
}
