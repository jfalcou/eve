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
#include <type_traits>

TTS_CASE_TPL("Check sub return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::saturated(eve::sub[ T()              ])(T(), T())), T);
  TTS_EXPR_IS( (eve::saturated(eve::sub[ eve::logical<T>()])(T(), T())), T);
  TTS_EXPR_IS( (eve::saturated(eve::sub[ true             ])(T(), T())), T);
}

TTS_CASE_TPL("Check saturated conditional sub behavior", EVE_TYPE)
{
  T tv{eve::valmax(eve::as<T>())};
  T fv{3};
  auto t = eve::true_(eve::as<T>());
  auto f = eve::false_(eve::as<T>());

  TTS_EQUAL(eve::saturated(eve::sub[ 1     ])(tv, fv), eve::saturated(eve::sub)(tv,fv));
  TTS_EQUAL(eve::saturated(eve::sub[ 1.0   ])(tv, fv), eve::saturated(eve::sub)(tv,fv));
  TTS_EQUAL(eve::saturated(eve::sub[ true  ])(tv, fv), eve::saturated(eve::sub)(tv,fv));
  TTS_EQUAL(eve::saturated(eve::sub[ t     ])(tv, fv), eve::saturated(eve::sub)(tv,fv));

  TTS_EQUAL(eve::saturated(eve::sub[ 0     ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated(eve::sub[ 0.0   ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated(eve::sub[ false ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated(eve::sub[ f     ])(tv, fv), tv);

  // Mixed case
  eve::as_logical_t<T> m{};
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL ( eve::saturated(eve::sub[ m ])(tv, fv)
            , eve::if_else(m, eve::saturated(eve::sub)(tv,fv), tv)
            );
}
