//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/binarize_not.hpp>
#include <eve/function/is_less.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/mone.hpp>
#include <eve/logical.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check binarize_not return type", EVE_TYPE)
{
  using eve::binarize_not;
  TTS_EXPR_IS(binarize_not(eve::logical<T>()), T);
  TTS_EXPR_IS(binarize_not(eve::logical<T>(), int()), T);
}

TTS_CASE_TPL("Check eve::binarize_not on logicals behavior", EVE_TYPE)
{
  using eve::binarize_not;
  using eve::is_less;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(binarize_not(is_less(T(1) , T(2))), T(0));
  TTS_EQUAL(binarize_not(is_less(T(2) , T(1))), T(1));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(binarize_not(is_less(T(2), T(1)), v_t(-2))    , T(-2));
    TTS_EQUAL(binarize_not(is_less(T(0), T(1)), v_t(-2))    , T( 0));
    TTS_EQUAL(binarize_not(is_less(T(1), T(2)), eve::mone_) , T( 0));
    TTS_EQUAL(binarize_not(is_less(T(2), T(1)), eve::mone_) , T(-1));
  }

  TTS_EQUAL(binarize_not(is_less(T(2), T(1)), v_t(2))             , T(2)              );
  TTS_EQUAL(binarize_not(is_less(T(0), T(1)), v_t(2))             , T(0)              );
  TTS_EQUAL(binarize_not(is_less(T(0), T(1)), eve::allbits_)      , T(0)              );
  TTS_IEEE_EQUAL(binarize_not(is_less(T(2), T(1)), eve::allbits_) , eve::Allbits<T>() );
}
