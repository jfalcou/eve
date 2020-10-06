//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/binarize.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/is_not_equal.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/mone.hpp>
#include <eve/logical.hpp>
#include <type_traits>

TTS_CASE("Check binarize return type")
{
  using eve::binarize;
  TTS_EXPR_IS(binarize(eve::logical<EVE_TYPE>()), EVE_TYPE);
  TTS_EXPR_IS(binarize(eve::logical<EVE_TYPE>(), int()), EVE_TYPE);
}

TTS_CASE("Check eve::binarize on logicals behavior")
{
  using eve::binarize;
  using eve::is_equal;

  TTS_EQUAL(binarize(is_equal(EVE_TYPE(1) , EVE_TYPE(2))), EVE_TYPE(0));
  TTS_EQUAL(binarize(is_equal(EVE_TYPE(2) , EVE_TYPE(2))), EVE_TYPE(1));

  if constexpr(eve::signed_value<EVE_TYPE>)
  {
    TTS_EQUAL(binarize(is_equal(EVE_TYPE(1), EVE_TYPE(1)), EVE_VALUE(-2))   , EVE_TYPE(-2));
    TTS_EQUAL(binarize(is_equal(EVE_TYPE(0), EVE_TYPE(1)), EVE_VALUE(-2))   , EVE_TYPE( 0));

    TTS_EQUAL(binarize(is_equal(EVE_TYPE(2), EVE_TYPE(2)), eve::mone), EVE_TYPE(-1));
    TTS_EQUAL(binarize(is_equal(EVE_TYPE(1), EVE_TYPE(2)), eve::mone), EVE_TYPE( 0));
  }

  TTS_EQUAL(binarize(is_equal(EVE_TYPE(1), EVE_TYPE(1)), EVE_VALUE(2))        , EVE_TYPE(2));
  TTS_EQUAL(binarize(is_equal(EVE_TYPE(0), EVE_TYPE(1)), EVE_VALUE(2))        , EVE_TYPE(0));

  TTS_EQUAL(binarize(is_equal(EVE_TYPE(0), EVE_TYPE(1)), eve::allbits)     , EVE_TYPE(0)              );
  TTS_IEEE_EQUAL(binarize(is_equal(EVE_TYPE(2), EVE_TYPE(2)), eve::allbits), eve::allbits(eve::as<EVE_TYPE>()) );
}
