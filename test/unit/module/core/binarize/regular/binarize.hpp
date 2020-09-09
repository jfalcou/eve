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
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check binarize return type", EVE_TYPE)
{
  using eve::binarize;
  TTS_EXPR_IS(binarize(eve::logical<T>()), T);
  TTS_EXPR_IS(binarize(eve::logical<T>(), int()), T);
}

TTS_CASE_TPL("Check eve::binarize on logicals behavior", EVE_TYPE)
{
  using eve::binarize;
  using eve::is_equal;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(binarize(is_equal(T(1) , T(2))), T(0));
  TTS_EQUAL(binarize(is_equal(T(2) , T(2))), T(1));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(binarize(is_equal(T(1), T(1)), v_t(-2))   , T(-2));
    TTS_EQUAL(binarize(is_equal(T(0), T(1)), v_t(-2))   , T( 0));

    TTS_EQUAL(binarize(is_equal(T(2), T(2)), eve::mone_), T(-1));
    TTS_EQUAL(binarize(is_equal(T(1), T(2)), eve::mone_), T( 0));
  }

  TTS_EQUAL(binarize(is_equal(T(1), T(1)), v_t(2))        , T(2));
  TTS_EQUAL(binarize(is_equal(T(0), T(1)), v_t(2))        , T(0));

  TTS_EQUAL(binarize(is_equal(T(0), T(1)), eve::allbits)     , T(0)              );
  TTS_IEEE_EQUAL(binarize(is_equal(T(2), T(2)), eve::allbits), eve::Allbits<T>() );
}

