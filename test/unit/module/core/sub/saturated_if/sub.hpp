//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sub.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check sub return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::saturated_(eve::sub[ T()              ])(T(), T())), T);
  TTS_EXPR_IS( (eve::saturated_(eve::sub[ eve::logical<T>()])(T(), T())), T);
  TTS_EXPR_IS( (eve::saturated_(eve::sub[ true             ])(T(), T())), T);
}

TTS_CASE_TPL("Check saturated conditional sub behavior", EVE_TYPE)
{
  T tv{eve::Valmax<T>()};
  T fv{3};
  auto t = eve::True<T>();
  auto f = eve::False<T>();

  TTS_EQUAL(eve::saturated_(eve::sub[ 1     ])(tv, fv), eve::saturated_(eve::sub)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::sub[ 1.0   ])(tv, fv), eve::saturated_(eve::sub)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::sub[ true  ])(tv, fv), eve::saturated_(eve::sub)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::sub[ t     ])(tv, fv), eve::saturated_(eve::sub)(tv,fv));

  TTS_EQUAL(eve::saturated_(eve::sub[ 0     ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated_(eve::sub[ 0.0   ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated_(eve::sub[ false ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated_(eve::sub[ f     ])(tv, fv), tv);

  // Mixed case
  eve::as_logical_t<T> m{};
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL ( eve::saturated_(eve::sub[ m ])(tv, fv)
            , eve::if_else(m, eve::saturated_(eve::sub)(tv,fv), tv)
            );
}
