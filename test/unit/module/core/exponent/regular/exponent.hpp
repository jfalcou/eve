//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/mzero.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/minus.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::exponent return type", EVE_TYPE)
{
  using r_t = eve::detail::as_integer_t<T>;
  TTS_EXPR_IS((eve::exponent(T(0))), (r_t));
}

TTS_CASE_TPL("Check eve::exponent  behavior", EVE_TYPE)
{
  using eve::exponent;
  TTS_EXPR_IS( exponent(T()), (eve::detail::as_integer_t<T>));
  using r_t = eve::detail::as_integer_t<T>;
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_EQUAL(exponent(eve::Inf<T>()), eve::Zero<r_t>());
    TTS_EQUAL(exponent(eve::Minf<T>()), eve::Zero<r_t>());
    TTS_EQUAL(exponent(eve::Nan<T>()), eve::Zero<r_t>());
  }

  TTS_EQUAL( (exponent(T(0))), r_t(0));
  TTS_EQUAL( (exponent(T(2))), r_t(1));
  TTS_EQUAL( (exponent(T(1.5))), r_t(0));
  TTS_EQUAL( (exponent(eve::One<T>())), r_t(0));
  TTS_EQUAL( (exponent(T(2.5))), r_t(1));
  TTS_EQUAL( (exponent(T(4.5))), r_t(2));
}

