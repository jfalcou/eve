//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ACOSPI_HPP
#define ACOSPI_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/acospi.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check acospi behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using eve::logical;

  wide<Type, T>  lhs([](auto i, auto) { return (i%2 ? 1 : -1)*Type(1)/(i+1); }), 
  ref([](auto i, auto) { return eve::acospi( (i%2 ? 1 : -1)*Type(1)/(i+1)); }),  
  refp([](auto i, auto) { return eve::pedantic_(eve::acospi)((i%2 ? 1 : -1)*Type(1)/(i+1)); });  
  TTS_ULP_EQUAL(refp, eve::pedantic_(eve::acospi)(lhs), 24);
  TTS_ULP_EQUAL(ref, eve::acospi(lhs), 24); 
}


#endif
