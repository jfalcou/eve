//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check oneminus return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::saturated_(eve::oneminus[ v_t(0)               ])(T(0)), T);
  TTS_EXPR_IS(eve::saturated_(eve::oneminus[ T(0)                 ])(T(0)), T);
  TTS_EXPR_IS(eve::saturated_(eve::oneminus[ eve::logical<T>(0)   ])(T(0)), T);
  TTS_EXPR_IS(eve::saturated_(eve::oneminus[ eve::logical<v_t>(0) ])(T(0)), T);
  TTS_EXPR_IS(eve::saturated_(eve::oneminus[ true                 ])(T(0)), T);
}

TTS_CASE_TPL("Check eve::saturated_(eve::oneminus) behavior", EVE_TYPE)
{
  T tv, res;
  auto t = eve::True<T>();
  auto f = eve::False(eve::as<T>());

  if constexpr(eve::signed_value<T>)
  {
    tv  = eve::Valmin<T>();
    res = eve::Valmax<T>();
  }
  else
  {
    tv  = T{2};
    res = T{0};
  }

  TTS_EQUAL(eve::saturated_(eve::oneminus[ 1    ])(tv), res);
  TTS_EQUAL(eve::saturated_(eve::oneminus[ 1.0  ])(tv), res);
  TTS_EQUAL(eve::saturated_(eve::oneminus[ true ])(tv), res);
  TTS_EQUAL(eve::saturated_(eve::oneminus[ t    ])(tv), res);

  TTS_EQUAL(eve::saturated_(eve::oneminus[ 0 ])(tv)     , tv);
  TTS_EQUAL(eve::saturated_(eve::oneminus[ 0.0 ])(tv)   , tv);
  TTS_EQUAL(eve::saturated_(eve::oneminus[ false ])(tv) , tv);
  TTS_EQUAL(eve::saturated_(eve::oneminus[ f ])(tv)     , tv);

    // Mixed case
  eve::as_logical_t<T> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::saturated_(eve::oneminus[ m ])(tv), eve::if_else(m, res, tv) );
}
