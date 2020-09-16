//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/minus.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check conditional eve::minus return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::minus[ v_t(0)  ](T(0))             , T);
  TTS_EXPR_IS(eve::minus[ T(0)    ](T(0))             , T);
  TTS_EXPR_IS(eve::minus[ eve::logical<T>(0)  ](T(0)) , T);
  TTS_EXPR_IS(eve::minus[ eve::logical<v_t>(0)](T(0)) , T);
  TTS_EXPR_IS(eve::minus[ true ](T(0))                , T);
}

TTS_CASE_TPL("Check conditional eve::minus behavior", EVE_TYPE)
{
  T tv(2);
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  TTS_EQUAL(eve::minus[ 1     ](tv) , T(-tv) );
  TTS_EQUAL(eve::minus[ 1.0   ](tv) , T(-tv) );
  TTS_EQUAL(eve::minus[ true  ](tv) , T(-tv) );
  TTS_EQUAL(eve::minus[ t     ](tv) , T(-tv) );

  TTS_EQUAL(eve::minus[ 0     ](tv) , tv);
  TTS_EQUAL(eve::minus[ 0.0   ](tv) , tv);
  TTS_EQUAL(eve::minus[ false ](tv) , tv);
  TTS_EQUAL(eve::minus[ f     ](tv) , tv);

  // Mixed case
  eve::as_logical_t<T> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::minus[ m ](tv), eve::if_else(m,  (T(-tv)), tv) );
}
