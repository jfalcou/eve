//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/maximum.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/platform.hpp>
#include <eve/logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::maximum return type", EVE_TYPE)
{
  using elt_t =  eve::element_type_t<T>;
  TTS_EXPR_IS( (eve::maximum(T()))               , elt_t);
}

TTS_CASE_TPL("Check eve::maximum behavior on arithmetic", EVE_TYPE)
{
  using elt_t =  eve::element_type_t<T>;
  eve::wide<elt_t, eve::fixed<4>> w{3, 2, 6, 1};
  TTS_EQUAL(eve::maximum(w), elt_t(6));
}
