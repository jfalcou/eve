//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
  TTS_EXPR_IS(eve::iround(EVE_TYPE(0)), (eve::detail::as_integer_t<EVE_TYPE>));
}

TTS_CASE("Check eve::iround behavior")
{
  TTS_EQUAL(eve::iround((EVE_TYPE(1.7)), eve::upward_      ), eve::iceil   ((EVE_TYPE(1.7))) );
  TTS_EQUAL(eve::iround((EVE_TYPE(1.7)), eve::downward_    ), eve::ifloor  ((EVE_TYPE(1.7))) );
  TTS_EQUAL(eve::iround((EVE_TYPE(1.7)), eve::toward_zero_ ), eve::itrunc  ((EVE_TYPE(1.7))) );
  TTS_EQUAL(eve::iround((EVE_TYPE(1.7)), eve::to_nearest_  ), eve::inearest((EVE_TYPE(1.7))) );
  TTS_EQUAL(eve::iround((EVE_TYPE(1.7))                    ), eve::inearest((EVE_TYPE(1.7))) );

  TTS_EQUAL(eve::iround((EVE_TYPE(1.3)), eve::upward_      ), eve::iceil   ((EVE_TYPE(1.3))) );
  TTS_EQUAL(eve::iround((EVE_TYPE(1.3)), eve::downward_    ), eve::ifloor  ((EVE_TYPE(1.3))) );
  TTS_EQUAL(eve::iround((EVE_TYPE(1.3)), eve::toward_zero_ ), eve::itrunc  ((EVE_TYPE(1.3))) );
  TTS_EQUAL(eve::iround((EVE_TYPE(1.3)), eve::to_nearest_  ), eve::inearest((EVE_TYPE(1.3))) );
  TTS_EQUAL(eve::iround((EVE_TYPE(1.3))                    ), eve::inearest((EVE_TYPE(1.3))) );
}
