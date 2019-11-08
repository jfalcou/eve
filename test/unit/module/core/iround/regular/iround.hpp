//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/iround.hpp>
#include <eve/function/inearest.hpp>
#include <eve/function/ifloor.hpp>
#include <eve/function/itrunc.hpp>
#include <eve/function/iceil.hpp>
#include <eve/tags.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::iround return type")
{
  TTS_EXPR_IS(eve::iround(Type(0)), (eve::detail::as_integer_t<Type>));
}

TTS_CASE("Check eve::iround behavior")
{
  TTS_EQUAL(eve::iround((Type(1.7)), eve::upward_      ), eve::iceil   ((Type(1.7))) );
  TTS_EQUAL(eve::iround((Type(1.7)), eve::downward_    ), eve::ifloor  ((Type(1.7))) );
  TTS_EQUAL(eve::iround((Type(1.7)), eve::toward_zero_ ), eve::itrunc  ((Type(1.7))) );
  TTS_EQUAL(eve::iround((Type(1.7)), eve::to_nearest_  ), eve::inearest((Type(1.7))) );
  TTS_EQUAL(eve::iround((Type(1.7))                    ), eve::inearest((Type(1.7))) );

  TTS_EQUAL(eve::iround((Type(1.3)), eve::upward_      ), eve::iceil   ((Type(1.3))) );
  TTS_EQUAL(eve::iround((Type(1.3)), eve::downward_    ), eve::ifloor  ((Type(1.3))) );
  TTS_EQUAL(eve::iround((Type(1.3)), eve::toward_zero_ ), eve::itrunc  ((Type(1.3))) );
  TTS_EQUAL(eve::iround((Type(1.3)), eve::to_nearest_  ), eve::inearest((Type(1.3))) );
  TTS_EQUAL(eve::iround((Type(1.3))                    ), eve::inearest((Type(1.3))) );
}
