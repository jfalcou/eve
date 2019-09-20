//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BINARIZE_HPP
#define BINARIZE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <tts/tests/precision.hpp>
#include <eve/function/simd/binarize.hpp>
#include <eve/logical.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/mone.hpp>
#include <eve/wide.hpp>
#include <eve/logical.hpp>

using eve::fixed;

TTS_CASE_TPL("Check binarize behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::logical;
  using eve::wide;
  {
    logical<wide<Type, T>> lhs([](auto i, auto) { return i%2; }); 
    wide<Type, T>  ref([](auto i, auto) { return eve::binarize(logical<Type>(i %2)); });
    TTS_EQUAL(ref, eve::binarize(lhs));
  }
  {
    logical<wide<Type, T>> lhs([](auto i, auto) { return i%2; }); 
    wide<Type, T>  ref([](auto i, auto) { return Type(eve::binarize(logical<Type>(i %2), 14)); });
    wide<Type, T>  val(eve::binarize(lhs, 14));
    TTS_EQUAL(ref, val);
  }
  if constexpr(std::is_signed_v<Type>)
  {
    logical<wide<Type, T>> lhs([](auto i, auto) { return i%2; }); 
    wide<Type, T>  ref([](auto i, auto) { return eve::binarize(logical<Type>(i %2), eve::mone_); });
    TTS_EQUAL(ref, eve::binarize(lhs, eve::mone_));
  }
  { 
    logical<wide<Type, T>> lhs([](auto i, auto) { return i%2; }); 
    wide<Type, T>  ref([](auto i, auto) { return eve::binarize(logical<Type>(i %2), eve::allbits_); });
    TTS_IEEE_EQUAL(ref, eve::binarize(lhs, eve::allbits_));
  }

  
}

#endif
