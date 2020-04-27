//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_less.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::is_less return type", EVE_TYPE)
{
  using eve::logical;

  TTS_EXPR_IS(eve::is_less(T() , T()  ), (logical<T>));
  TTS_EXPR_IS(eve::is_less(T() , v_t() ), (logical<T>));
  TTS_EXPR_IS(eve::is_less(v_t(), T()  ), (logical<T>));
}

#if defined(EVE_SIMD_TESTS)
TTS_CASE_TPL("Check eve::operator< return type", EVE_TYPE)
{
  using eve::logical;

  TTS_EXPR_IS((T()   < T() ), (logical<T>));
  TTS_EXPR_IS((T()   < v_t()), (logical<T>));
  TTS_EXPR_IS((v_t()  < T() ), (logical<T>));
}
#endif

TTS_CASE_TPL("Check eve::is_less behavior", EVE_TYPE)
{
  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_less(T(1), eve::Nan<T>()), eve::False<T>());
    TTS_EQUAL(eve::is_less(eve::Nan<T>(), T(1)), eve::False<T>());
  }

  TTS_EQUAL(eve::is_less(T(1) , T(1) ), eve::False<T>());
  TTS_EQUAL(eve::is_less(T(1) , v_t(1)), eve::False<T>());
  TTS_EQUAL(eve::is_less(v_t(1), T(1) ), eve::False<T>());
  TTS_EQUAL(eve::is_less(T(3) , T(1) ), eve::False<T>());
  TTS_EQUAL(eve::is_less(T(3) , v_t(1)), eve::False<T>());
  TTS_EQUAL(eve::is_less(v_t(3), T(1) ), eve::False<T>());
  TTS_EQUAL(eve::is_less(T(1) , T(3) ), eve::True<T>() );
  TTS_EQUAL(eve::is_less(T(1) , v_t(3)), eve::True<T>() );
  TTS_EQUAL(eve::is_less(v_t(1), T(3) ), eve::True<T>() );
}

TTS_CASE_TPL("Check eve::operator< behavior", EVE_TYPE)
{
  using eve::logical;

  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL((eve::Nan<T>() < eve::Nan<T>()) , eve::False<T>());
    TTS_EQUAL((eve::Nan<T>() < T(4))          , eve::False<T>());
  }

  TTS_EQUAL( (T(1)   < T(1) ) , eve::False<T>());
  TTS_EQUAL( (v_t(1)  < T(1) ) , eve::False<T>());
  TTS_EQUAL( (T(1)   < v_t(1)) , eve::False<T>());
  TTS_EQUAL( (T(3)   < T(1) ) , eve::False<T>());
  TTS_EQUAL( (v_t(3)  < T(1) ) , eve::False<T>());
  TTS_EQUAL( (T(3)   < v_t(1)) , eve::False<T>());
  TTS_EQUAL( (T(1)   < T(3) ) , eve::True<T>() );
  TTS_EQUAL( (v_t(1)  < T(3) ) , eve::True<T>() );
  TTS_EQUAL( (T(1)   < v_t(3)) , eve::True<T>() );
}
