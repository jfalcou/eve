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

TTS_CASE("Check eve::exponent return type")
{
  using r_t = eve::detail::as_integer_t<EVE_TYPE>; 
  TTS_EXPR_IS((eve::exponent(EVE_TYPE(0))), (r_t));
}

TTS_CASE("Check eve::exponent  behavior")
{
  using eve::exponent; 
  TTS_EXPR_IS( exponent(EVE_TYPE()), (eve::detail::as_integer_t<EVE_TYPE>));
  using r_t = eve::detail::as_integer_t<EVE_TYPE>; 
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_EQUAL(exponent(eve::Inf<EVE_TYPE>()), eve::Zero<r_t>());
    TTS_EQUAL(exponent(eve::Minf<EVE_TYPE>()), eve::Zero<r_t>());
    TTS_EQUAL(exponent(eve::Nan<EVE_TYPE>()), eve::Zero<r_t>());
  }
  
  TTS_EQUAL( (exponent(EVE_TYPE(0))), r_t(0));
  TTS_EQUAL( (exponent(EVE_TYPE(2))), r_t(1));
  TTS_EQUAL( (exponent(EVE_TYPE(1.5))), r_t(0));
  TTS_EQUAL( (exponent(eve::One<EVE_TYPE>())), r_t(0));
  TTS_EQUAL( (exponent(EVE_TYPE(2.5))), r_t(1));
  TTS_EQUAL( (exponent(EVE_TYPE(4.5))), r_t(2)); 
}

