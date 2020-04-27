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
#include <eve/constant/mzero.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::oneminus return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::oneminus[ v_t(0)  ](T(0))              , T);
  TTS_EXPR_IS(eve::oneminus[ (T(0)) ](T(0))              , T);
  TTS_EXPR_IS(eve::oneminus[ (eve::logical<T>(0))](T(0)) , T);
  TTS_EXPR_IS(eve::oneminus[ eve::logical<v_t>(0) ](T(0)) , T);
  TTS_EXPR_IS(eve::oneminus[ true ](T(0))                   , T);
}

TTS_CASE_TPL("Check eve::oneminus behavior", EVE_TYPE)
{
  T tv(2);
  auto t = eve::True<T>();
  auto f = eve::False<T>();

  TTS_EQUAL(eve::oneminus[ 1 ](tv)   , (T(-1)));
  TTS_EQUAL(eve::oneminus[ 1.0 ](tv) , (T(-1)));
  TTS_EQUAL(eve::oneminus[ true ](tv), (T(-1)));
  TTS_EQUAL(eve::oneminus[ t ](tv)   , (T(-1)));

  TTS_EQUAL(eve::oneminus[ 0 ](tv)     , tv);
  TTS_EQUAL(eve::oneminus[ 0.0 ](tv)   , tv);
  TTS_EQUAL(eve::oneminus[ false ](tv) , tv);
  TTS_EQUAL(eve::oneminus[ f ](tv)     , tv);

    // Mixed case
  eve::as_logical_t<T> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::oneminus[ m ](tv), eve::if_else(m, (T(-1)), tv) );
}
