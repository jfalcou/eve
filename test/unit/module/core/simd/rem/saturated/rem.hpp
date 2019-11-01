//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef REM_HPP
#define REM_HPP

#include "test.hpp"
#include <tts/tests/precision.hpp>
#include <eve/function/rem.hpp>
#include <eve/wide.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

using eve::fixed;

TTS_CASE_TPL("Check saturated rem behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using p_t = wide<Type, T>;
  if constexpr(std::is_floating_point_v<Type>)
  {
    wide<Type, T> lhs([](auto i, auto c) { return c; }),
      rhs([](auto i, auto ) { return 1 + i; }),
      ref([](auto i, auto c) { return eve::saturated_(eve::rem)(Type(c), Type(1 + i)); });
    
    TTS_ULP_EQUAL(ref, eve::saturated_(eve::rem)(lhs, rhs),0.5);
  }
  else if constexpr(  std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::rem)(eve::Mone<p_t>(), eve::Mone<p_t>()), eve::One<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(eve::One<p_t>(), eve::One<p_t>()), eve::One<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(eve::Valmax<p_t>(),eve::Mone<p_t>()), eve::Valmin<p_t>()+eve::One<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(eve::Valmax<p_t>(),eve::One<p_t>()), eve::Valmax<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(eve::Valmin<p_t>(),eve::Mone<p_t>()), eve::Valmax<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(eve::Zero<p_t>(), eve::Zero<p_t>()), eve::Zero<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(eve::Mone<p_t>(), eve::Zero<p_t>()), eve::Valmin<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(p_t(-2), eve::Zero<p_t>()), eve::Valmin<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(eve::Valmin<p_t>(), eve::Zero<p_t>()), eve::Valmin<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(eve::One<p_t>(), eve::Zero<p_t>()), eve::Valmax<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(p_t(2), eve::Zero<p_t>()), eve::Valmax<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(eve::Valmax<p_t>(), eve::Zero<p_t>()), eve::Valmax<p_t>());
  } // end of test for signed_int_
  else
  {
    TTS_EQUAL(eve::saturated_(eve::rem)(eve::One<p_t>(), eve::One<p_t>()), eve::One<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(eve::Valmax<p_t>(),eve::One<p_t>()), eve::Valmax<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(eve::Zero<p_t>(), eve::Zero<p_t>()), eve::Zero<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(eve::One<p_t>(), eve::Zero<p_t>()), eve::Valmax<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(p_t(2), eve::Zero<p_t>()), eve::Valmax<p_t>());
    TTS_EQUAL(eve::saturated_(eve::rem)(eve::Valmax<p_t>(), eve::Zero<p_t>()), eve::Valmax<p_t>());
  }
}

TTS_CASE_TPL("Check saturated rem behavior on wide + scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  
  wide<Type, T> lhs([](auto i, auto) { return i+1; }),
    rref([](auto i, auto) { return eve::saturated_(eve::rem)(Type(1+i), Type(4)); }),
    lref([](auto i, auto) { return  eve::saturated_(eve::rem)(Type(4), Type((i+1))); });
  
  TTS_ULP_EQUAL(lref, eve::saturated_(eve::rem)(4, lhs),0.5);
  TTS_ULP_EQUAL(rref, eve::saturated_(eve::rem)(lhs, 4),0.5);
  
}
    
#endif
